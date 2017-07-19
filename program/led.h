#ifndef _LED_H
#define _LED_H

#include"includes.h"


//DEFINE LED PORT
#define LED		P0_0


//DEFINE MACRO
#define ledon()		LED = LOW
#define ledoff()	LED = HIGH


//FUNCTION PROTOTYPES
void blink(INT8U nblink, INT8U ontime);

#endif
