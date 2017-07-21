#include "shangweiji.h"
#include "sys.h"
#include "pid.h"
#include "chassis_task.h"


extern uint8_t  shangweiji_buf[SHANGWEIJI_BUFLEN];
int shangweijiNum=0;
Shangweiji_Struct ShangweijiData;
int i=0;
float p1,p2,p3;
float i1,i2,i3;
float d1,d2,d3;
float ref_x,ref_y,ref_w;
char PID1OK[3]={0XBB,01,0XFF};
char PID2OK[3]={0XBB,02,0XFF};
char PID3OK[3]={0XBB,03,0XFF};
char POSREFOK[3]={0XBB,04,0XFF};


extern chassis_t chassis; 
extern k_pid_t pid_positionhold_x;
extern k_pid_t pid_positionhold_y;
extern k_pid_t pid_positionhold_w;


void getparameter(uint8_t ID,float d1,float d2,float d3)
{
switch (ID)
{
	case 0x01:
		pid_positionhold_x.p=d1;
		pid_positionhold_x.i=d2;
		pid_positionhold_x.d=d3;
//    HAL_UART_Transmit_IT(&SWJ_HUART,PID1OK,sizeof(PID1OK));			
		break;
	case 0x02:
		pid_positionhold_y.p=d1;
		pid_positionhold_y.i=d2;
		pid_positionhold_y.d=d3;
//	    HAL_UART_Transmit_IT(&SWJ_HUART,PID2OK,sizeof(PID2OK));			

	break;
		
		case 0x03:
		pid_positionhold_w.p=d1;
		pid_positionhold_w.i=d2;
		pid_positionhold_w.d=d3;
	//	    HAL_UART_Transmit_IT(&SWJ_HUART,PID3OK,sizeof(PID3OK));			

		break;
			case 0x04:
		chassis.positionx_ref=d1;
		chassis.positiony_ref=d2;
		chassis.compass_ref=d3;
//			HAL_UART_Transmit_IT(&SWJ_HUART,POSREFOK,sizeof(POSREFOK));			
					break;

}

}


void SHANGWEIJI_DATAHANDLER()
{
memcpy(&ShangweijiData, shangweiji_buf, sizeof(ShangweijiData));

	shangweijiNum++;
	  if ((ShangweijiData.sof == SHANGWEIJI_HEARDER)&& (1 == Verify_CRC8_Check_Sum(shangweiji_buf, sizeof(ShangweijiData))))
				{
					
					shangweijiNum--;
//					switch(ShangweijiData.ID)
//					{
//						case 0x01:
//					  p1=ShangweijiData.data1;
//						i1=ShangweijiData.data2;		
//						d1=ShangweijiData.data3;			
//            HAL_UART_Transmit_IT(&SWJ_HUART,PID1OK,sizeof(PID1OK));			
//						break;
//				
//						case 0x02:
//						p2=ShangweijiData.data1;
//						i2=ShangweijiData.data2;		
//						d2=ShangweijiData.data3;	
//						HAL_UART_Transmit_IT(&SWJ_HUART,PID2OK,sizeof(PID2OK));			

//						break;
//						
//						case 0x03:
//						p3=ShangweijiData.data1;
//						i3=ShangweijiData.data2;		
//						d3=ShangweijiData.data3;							
//						HAL_UART_Transmit_IT(&SWJ_HUART,PID3OK,sizeof(PID3OK));			

//						break;
//				
//						case 0x04:
//						ref_x=ShangweijiData.data1;
//						ref_y=ShangweijiData.data2;		
//						ref_w=ShangweijiData.data3;	
//						HAL_UART_Transmit_IT(&SWJ_HUART,POSREFOK,sizeof(POSREFOK));			

//						break;				
//					}						
				getparameter(ShangweijiData.ID,ShangweijiData.data1,ShangweijiData.data2,ShangweijiData.data3);
				}    
shangweijiNum--;
}