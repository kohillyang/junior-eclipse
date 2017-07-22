/**
  ********************************(C) COPYRIGHT 2017 DJI************************
  * @file       pid.h
	* @brief      pid parameter initialization, position and delta pid calculate
	* @update	  
	*	@history
	* Version     Date          Author           Modification
  * V1.0.0      Apr-30-2017   Richard.luo        
  * @verbatim
	********************************(C) COPYRIGHT 2017 DJI************************
	*/
	
#ifndef __pid_H__
#define __pid_H__

#include "stm32f4xx_hal.h"
#define ABS(x) ((x > 0) ? x : (-x))

enum
{
    LLAST = 0,
    LAST  = 1,
    NOW   = 2,
    POSITION_PID,
    DELTA_PID,
};
typedef struct _k_pid_t
{
    float p;
    float i;
    float d;

    float set[3]; //target NOW/LAST/LLAST
    float get[3]; //measure
    float err[3]; //error

    float pout; 
    float iout; 
    float dout; 

	  //position pid related
    float pos_out; //this time position output
    float last_pos_out; 
	
	  //delta pid related
    float delta_u; //this time delta value
    float delta_out; //this time delta output = last_delta_out + delta_u
    float last_delta_out;

	  ////deadband < err < max_err
    float    max_err;
    float    deadband; 
		
    uint32_t pid_mode;
    uint32_t MaxOutput;
    uint32_t IntegralLimit;

    void (*f_param_init)(struct _k_pid_t* pid, 
                         uint32_t        pid_mode,
                         uint32_t        maxOutput,
                         uint32_t        integralLimit,
                         float           p,
                         float           i,
                         float           d);
    void (*f_pid_reset)(struct _k_pid_t* pid, float p, float i, float d);
 
} k_pid_t;

void PID_struct_init(
	  k_pid_t*   pid,
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,

    float kp,
    float ki,
    float kd);

float pid_calc(k_pid_t* pid, float fdb, float ref);

extern k_pid_t pid_rol;
extern k_pid_t pid_pit;
extern k_pid_t pid_yaw;
extern k_pid_t pid_pit_speed;
extern k_pid_t pid_yaw_speed;
extern k_pid_t pid_spd[4];

extern k_pid_t pid_chassis_angle;
extern k_pid_t pid_trigger;
extern k_pid_t pid_trigger_speed;
extern k_pid_t pid_imu_tmp; //imu_temperature

#endif
