#ifndef SERIALCOMMUNICATION_H
#define SERILACOMMUNCATION_H
/*  ------------------------------------ 
    	  89C51 serial communication
    ------------------------------------
	     
   Demonstration of serial communication - ECHO program
   -----------------------------------------------------

   Designed for 89c51 running at 11.0592Mhz

   communication between PC and microcontroller. 
  
   RS232 serial specification
   9600 baud rate
   8-bit
   1- start bit	
   1-stop bit
   parity none 

   Hardware Connection
   -------------------
   compile with Keil Compiler.

   Note: Hyper Terminal / Terminal v1.9b software for communication
   
   operation: receives data from PC (or any serial device) and transmitt
		same data back to PC- A ECHO program
   -----------------------------------------------------------

   feedback appriciated: Prashanthbs_08@yahoo.co.in
 
----------------------------------------------------------------
----------------------------------------------------------------
*/ 

//INCLUDES 

#include "includes.h"

//DEFINE CONSTANT
#define Baud_rate 0xFD  // BAUD RATE 9600                     

//DEFINE PROTOTYPES
        
void 		uartinit	(void);
void 		putchar		(INT8U ascii);
INT8U 	getchar		(void);
void 		puts			(INT8U *s);

#endif

