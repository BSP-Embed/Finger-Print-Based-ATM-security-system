/*
*        For sdcc compiler, with features of bus fault
*        detection, no acknowledgement feature,
*        and I2C busy feature.
*
*        Written By: prashanth b.s
*        E-mail:     bsp.embed@gmail.com
*       
*  NOTE: It may or maynot be used with multi-master
*        Multislave confuguration
*        
*        Tested with multi-slave configuration
****************************************************
*       I2C Bus Configuration
*
****************************************************
*/
#ifndef I2C_H
#define I2C_H

#include "includes.h"

//DEFINE PORTS/PINS
sbit SDA = P1^1;
sbit SCL = P1^0;

//DEFINE MACRO
#define HOLD dlyms(1)

//FUNCTION PROTOTYPES
void send_stop(void);
void master(int8u slave_addr);
void send_byte(int8u i2c_data);
void I2CWrite(int8u  slave_add, int8u sub_add, int8u bytes, int8u *data_in);
int8u recv_byte(int8u cnt);
void I2CRead(int8u slave_add, int8u sub_add, int8u byte_cnt, int8u *recv_buf);
bit CheckEEPROM(void);
void I2Cinit(void);

#endif
