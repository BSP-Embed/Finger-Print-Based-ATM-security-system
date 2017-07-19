#ifndef _BUZ_H
#define _BUZ_H

//INCLUDES
#include "includes.h"



// define constants
#define OFF_TIME	100

// DEFINE PORTS
#define BUZ_PIN		P0_1


//DEFINE MACRO
#define buzon()		BUZ_PIN = LOW
#define buzoff()	BUZ_PIN = HIGH

//FUNCTION PROTOTYPES
void beep(INT8U nbeep, INT8U ontime);

#endif

