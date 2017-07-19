#ifndef KEYBOARD4_4_H
#define KEYBOARD4_4_H

//INCLUDE DEFINITION OF 8051
#include "includes.h"

//#define NON_BLOCK

//DEFINE PORTS/PINS
#define KB_PORT 		P1

//DEFINE CONSTANT
#define MAX_TIME_OUT 	5000
#define KEY_DEBOUNE		40				/* in milliseconds */
#define MASK 			(KB_PORT & 0x0f)

//FUNCTION PROTOTYPES 
INT8U getkey();
INT8U  find_col(INT8U key);
void KBDinit(void);
#endif
