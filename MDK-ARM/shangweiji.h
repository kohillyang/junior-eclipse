#ifndef __SHANGWEIJI_H__
#define __SHANGWEIJI_H__
#include "stm32f4xx_hal.h"
#define SHANGWEIJI_BUFLEN 32
#define SHANGWEIJI_HEARDER 0xA1
//#define PID1_ID 0x01
//#define PID2_ID 0x02
//#define PID3_ID 0x03
//#define REFPOSITION_ID 0x04

typedef __packed struct
{
    uint8_t  sof;
    uint8_t  ID;
	  float data1;
	  float data2;
	  float data3;	
		uint8_t nonuse[32-15];
    uint8_t  crc8;
} Shangweiji_Struct;


void SHANGWEIJI_DATAHANDLER(void);


#endif


;