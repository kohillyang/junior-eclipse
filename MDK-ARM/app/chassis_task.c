/**
 ********************************(C) COPYRIGHT 2017 DJI************************
 * @file       chassis_task.c
 * @brief      provide basic chassis control, use chassis follow gimbal model
 * @update
 *	@history
 * Version     Date          Author           Modification
 * V1.0.0      Apr-30-2017   Richard.luo      basic chassis control
 * @verbatim
 *  can use dji remoter or mouse and keyboard control chassis move
 ********************************(C) COPYRIGHT 2017 DJI************************
 */
#include "chassis_task.h"
#include "bsp_can.h"
#include "bsp_uart.h"
#include "can.h"
#include "cmsis_os.h"
#include "error_task.h"
#include "gimbal_task.h"
#include "judge_sys.h"
#include "kb.h"
#include "pid.h"
#include "mpu.h"
#include "sys.h"
#include <math.h>
#define MyAbs(x) ((x > 0) ? (x) : (-x))
#define MAX_WHEEL_SPEED 750
#define MAX_CHASSIS_VX_SPEED 100
#define MAX_CHASSIS_VY_SPEED 100
#define MAX_CHASSIS_VR_SPEED 350
#define MAX_CHASSIS_VW_SPEED 500

chassis_t chassis;
s16 current_3510[4];
#define POINT_NUM 13

/* for debuge */
int wheel_s_f, wheel_s_r;

/**
 * @brief     reset single axis gyroscope
 * @attention gyro reset at least wait 2s
 */
void reset_zgyro(void) {
	while (ZGYRO_CAN.State == HAL_CAN_STATE_BUSY_TX)
		;
	ZGYRO_CAN.pTxMsg->StdId = CAN_ZGYRO_RST_ID;
	ZGYRO_CAN.pTxMsg->IDE = CAN_ID_STD;
	ZGYRO_CAN.pTxMsg->RTR = CAN_RTR_DATA;
	ZGYRO_CAN.pTxMsg->DLC = 0x08;
	ZGYRO_CAN.pTxMsg->Data[0] = 0;
	ZGYRO_CAN.pTxMsg->Data[1] = 1;
	ZGYRO_CAN.pTxMsg->Data[2] = 2;
	ZGYRO_CAN.pTxMsg->Data[3] = 3;
	ZGYRO_CAN.pTxMsg->Data[4] = 4;
	ZGYRO_CAN.pTxMsg->Data[5] = 5;
	ZGYRO_CAN.pTxMsg->Data[6] = 6;
	ZGYRO_CAN.pTxMsg->Data[7] = 7;
	HAL_CAN_Transmit(&ZGYRO_CAN, 1000);

}

/**
 * @brief mecanum calculation function
 * @param input : vx vy vw(+ cw, - ccw)
 *        output: 4 wheel speed
 * @note  1=FR 2=FL 3=BL 4=BR
 * @map 	 2	%++++++%	1
 ++++
 ++++
 3	%++++++%	4    ↑=+Vy  →=+Vx
 */
void mecanum_calc(float vx, float vy, float vw, const int each_max_spd,
		s16 speed[]) {
	s16 buf[4];
	int i;
	float max = 0, rate;

	VAL_LIMIT(vx, -MAX_CHASSIS_VX_SPEED, MAX_CHASSIS_VX_SPEED);
	VAL_LIMIT(vy, -MAX_CHASSIS_VY_SPEED, MAX_CHASSIS_VY_SPEED);
	VAL_LIMIT(vw, -MAX_CHASSIS_VR_SPEED, MAX_CHASSIS_VR_SPEED);

	buf[0] = (+vx - vy + vw);
	buf[1] = (+vx + vy + vw);
	buf[2] = (-vx + vy + vw);
	buf[3] = (-vx - vy + vw);

	//find max item
	for (i = 0; i < 4; i++) {
		if (MyAbs(buf[i]) > max)
			max = MyAbs(buf[i]);
	}
	//equal proportion
	if (max > each_max_spd) {
		rate = each_max_spd / max;
		for (i = 0; i < 4; i++)
			buf[i] *= rate;
	}
	memcpy(speed, buf, sizeof(s16) * 4);
}
/**
 * @brief     send 4 calculated current to motor
 * @param     3510 motor ESC id
 * @retval    none
 */
void set_cm_current(CAN_HandleTypeDef *hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4) {

	hcan->pTxMsg->StdId = 0x200;
	hcan->pTxMsg->IDE = CAN_ID_STD;
	hcan->pTxMsg->RTR = CAN_RTR_DATA;
	hcan->pTxMsg->DLC = 0x08;
	hcan->pTxMsg->Data[0] = iq1 >> 8;
	hcan->pTxMsg->Data[1] = iq1;
	hcan->pTxMsg->Data[2] = iq2 >> 8;
	hcan->pTxMsg->Data[3] = iq2;
	hcan->pTxMsg->Data[4] = iq3 >> 8;
	hcan->pTxMsg->Data[5] = iq3;
	hcan->pTxMsg->Data[6] = iq4 >> 8;
	hcan->pTxMsg->Data[7] = iq4;
	HAL_CAN_Transmit(hcan, 1000);
}

int remember = 0;

void get_chassis_mode_set_ref(RC_Type *rc) {
	chassis.last_mode = chassis.mode;

	switch (rc->sw1) {
	case RC_UP:
		chassis.mode = CHASSIS_AUTO;  //senior students no use
		break;

	case RC_MI:
		//chassis.mode = CHASSIS_CLOSE_GYRO_LOOP;
		chassis.mode = CHASSIS_FOLLOW_GIMBAL; //
		break;

	case RC_DN:
		chassis.mode = CHASSIS_POSITION_HOLD;  //senior students no use
		break;

	default:
		break;
	}

//	switch (rc->sw2)
//  {
//    case RC_DN:
//      remember = 1;  //senior students no use
//    break;

//    case RC_MI:
//			//chassis.mode = CHASSIS_CLOSE_GYRO_LOOP;
//      remember = 0; //
//    break;  
//		
//    default:
//		break;
//  }
	/*
	 switch (chassis.mode)
	 {
	 case CHASSIS_AUTO:
	 {
	 //control coordinate is based on rc, where +y is forward, +x is right, +w is clockwise
	 //auto_vx, auto_vy or auto_wv is measured by mm/s and deg/s
	 }break;

	 case CHASSIS_OPEN_LOOP:
	 {
	 chassis.vy = rc->ch2 * CHASSIS_RC_MOVE_RATIO_Y + km.vy;
	 chassis.vx = rc->ch1 * CHASSIS_RC_MOVE_RATIO_X + km.vx;
	 chassis.vw = rc->ch3 / 2 + rc->mouse.x * 10;
	 }break;

	 case CHASSIS_FOLLOW_GIMBAL:
	 {
	 chassis.vy = rc->ch2 * CHASSIS_RC_MOVE_RATIO_Y + km.vy;
	 chassis.vx = rc->ch1 * CHASSIS_RC_MOVE_RATIO_X + km.vx;
	 }break;

	 case CHASSIS_CLOSE_GYRO_LOOP:
	 {
	 chassis.vy = rc->ch2 * CHASSIS_RC_MOVE_RATIO_Y + km.vy;
	 chassis.vx = rc->ch1 * CHASSIS_RC_MOVE_RATIO_X + km.vx;
	 chassis.target_angle += -rc->ch3 * 0.001f;
	 }break;

	 default :
	 {
	 }break;
	 }
	 */
}

/**
 * @brief     initialize chassis motor pid parameter
 * @usage     before chassis loop use this function
 */
int destination_order = 0;
int go = 1;
int back = 0;
k_pid_t pid_positionhold_x = { 0 };
k_pid_t pid_positionhold_y = { 0 };
k_pid_t pid_positionhold_w = { 0 };
void chassis_pid_param_init(void) {
	for (int k = 0; k < 4; k++) {
		//max current = 20000
		PID_struct_init(&pid_spd[k], POSITION_PID, 10000, 1000, 4, 0.05f, 5.0f);
	}
	PID_struct_init(&pid_chassis_angle, POSITION_PID, 600, 80, 3.0f, 0.001f,
			0.0f);

	PID_struct_init(&pid_positionhold_x, POSITION_PID, MAX_CHASSIS_VX_SPEED,
			200, 50.0f, 0.0f, 0.001f);
	PID_struct_init(&pid_positionhold_y, POSITION_PID, MAX_CHASSIS_VY_SPEED,
			200, 50.0f, 0.0f, 0.005f);
	PID_struct_init(&pid_positionhold_w, POSITION_PID, MAX_CHASSIS_VW_SPEED,
			600, 80.0f, 0.001f, 0.0f);
	pid_positionhold_x.max_err = 15;
	pid_positionhold_y.max_err = 15;
	pid_positionhold_x.deadband = 0.2;
	pid_positionhold_y.deadband = 0.2;
	pid_chassis_angle.max_err = 60 * 22.75f; // err angle > 60 cut the output
	pid_chassis_angle.deadband = 2;
	pid_positionhold_w.max_err = 1000.0f;
	pid_positionhold_w.deadband = 3.0f;
}

//float tempx=0,tempy=0;

float destinationx[POINT_NUM] = { 6.5, 9.4, 11.6, 14.3, 16.0, 17.8, 16.5, 16,
		17.8, 11.8, 10.0, 9.3, 6.1 };
float destinationy[POINT_NUM] = { 4.1, 4.2, 3.50, 3.70, 4.00, 7.60, 11.1, 11,
		10.8, 11.4, 7.30, 4.3, 4.0 };
extern int Receive_uwb;
void Get_RefPosition(chassis_t *chassis) {
	if (ABS(chassis->positionx_fdb-chassis->positionx_ref) < 0.2
			&& ABS(chassis->positiony_fdb-chassis->positiony_ref) < 0.2
			&& Receive_uwb) {
		if (go) {
			destination_order++;
			if (destination_order > POINT_NUM) {
				destination_order = destination_order - 2;
				go = 0;
				back = 1;
			}
		}

		else {
			destination_order--;
			if (destination_order < 0)
				destination_order = 0;
		}

	}

	chassis->positionx_ref = destinationx[destination_order];
	chassis->positiony_ref = destinationy[destination_order];

}

void chassis_task(void const* argu) {
	int i = 0;
	//float destinationx[6];
	//float destinationy[6];

	s16 start_flag = 0;
	chassis_pid_param_init();
	chassis.compass_ref = 265.0f;
	while (!Receive_uwb && start_flag < 10000) {
		start_flag++;
	}
	chassis.compass_ref = 270.0f;
	destination_order = 0;
//	float destinationx[POINT_NUM]={chassis.positionx_fdb,11.5,17.6,17.8,21.5,21.5};
//	float destinationy[POINT_NUM]={chassis.positiony_fdb,4.0,4.5,10.8,11.1,11.1};

//	destinationx[destination_order]=chassis.positionx_fdb;
//	destinationy[destination_order]=chassis.positiony_fdb;	
	chassis.positionx_ref = destinationx[destination_order];
	chassis.positiony_ref = destinationy[destination_order];

	HAL_Delay(1000);

	float compass_ref = 270;

	while (1) {
		pc_kb_hook();

		get_chassis_mode_set_ref(&rc);

//				if(remember==1) 
//				{
//				 	tempy=chassis.positiony_fdb;					
//				}
//		
//			if(remember==1) 
//				{
//						
//					tempx=chassis.positionx_fdb;
//				}					

		switch (chassis.mode) {
		case CHASSIS_FOLLOW_GIMBAL: {
			chassis.vy = rc.ch2 * CHASSIS_RC_MOVE_RATIO_Y
					+ km.vy * CHASSIS_PC_MOVE_RATIO_Y;
			chassis.vx = rc.ch1 * CHASSIS_RC_MOVE_RATIO_X
					+ km.vx * CHASSIS_PC_MOVE_RATIO_X;
			chassis.vw = rc.ch3;
		}
			break;

		case CHASSIS_POSITION_HOLD: {
			if (Receive_uwb) {
				Get_RefPosition(&chassis);
				Receive_uwb = 0;

				chassis.vy = pid_calc(&pid_positionhold_x,
						chassis.positionx_fdb, chassis.positionx_ref);

				chassis.vx = -pid_calc(&pid_positionhold_y,
						chassis.positiony_fdb, chassis.positiony_ref);//		// if( Receive_uwb==1)
				//{
				chassis.vw = -pid_calc(&pid_chassis_angle, chassis.compass_fdb,
						chassis.compass_ref);

				//	Receive_uwb=!Receive_uwb;

				//chassis.vy = 0;
				//chassis.vx = 0;
				//  Receive_uwb=0;
				//}
			}
		}

			break;

		default: {
			chassis.vy = 0;
			chassis.vx = 0;
		}
			break;
		}

		if (gYaw.ctrl_mode == GIMBAL_CLOSE_LOOP_ZGYRO) {
			chassis.vw = pid_calc(&pid_chassis_angle, yaw_relative_pos, 0);
		} else {
			//		chassis.vw = 0;
		}

		mecanum_calc(chassis.vx, chassis.vy, chassis.vw, MAX_WHEEL_SPEED,
				chassis.wheel_speed);
		for (i = 0; i < 4; i++) {
			current_3510[i] = pid_calc(&pid_spd[i], moto_chassis[i].speed_rpm,
					chassis.wheel_speed[i] * 10);
		}

		wheel_s_f = moto_chassis[0].speed_rpm;
		wheel_s_r = chassis.wheel_speed[0] * 10;

		if (chassis.mode == CHASSIS_RELAX
				|| gRxErr.err_list[DbusTOE].err_exist) {
			memset(current_3510, 0, sizeof(current_3510));
			pid_spd[0].iout = 0;
			pid_spd[1].iout = 0;
			pid_spd[2].iout = 0;
			pid_spd[3].iout = 0;
		}

		set_cm_current(&CHASSIS_CAN, current_3510[0], current_3510[1],
				current_3510[2], current_3510[3]);

		osDelay(10);
	}
}
