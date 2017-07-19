//DEFINE MAIN HEADER FILE
#ifndef MAIN_H
#define MAIN_H

#include <includes.h>

//DEFINE PORTS/PINS

#define RLY_PIN				P0_2
#define GSM_FP_PIN		P3_7
#define FP_SW_PIN			P1_0
#define MOTOR1_PIN		P0_7
#define MOTOR2_PIN		P0_6

//DEFINE CONSTANT
#define DTIME						10
#define PRESSED					0
#define MAX_CNT					3

//APP CONFIGURATION
/* comment below line for release */
//#define TESTING							

//DEFINE MACROS
#define mot1on()			MOTOR1_PIN = LOW
#define mot1off()			MOTOR1_PIN = HIGH

#define mot2on()			MOTOR2_PIN = LOW 
#define mot2off() 		MOTOR2_PIN = HIGH

#define starttmr()		TR0 = HIGH
#define stoptmr()			TR0 = LOW

#define rlyon()				RLY_PIN = LOW
#define rlyoff()			RLY_PIN = HIGH

#define EnGSM()				GSM_FP_PIN = HIGH

#define EnFP()				GSM_FP_PIN = LOW;	\
											T2CON = 0;				\
											uartinit()				

//FUNCTION PROTOTYPES
static 	void 	init				(void);
static 	void 	disptitle		(void);
static	void 	sendloc 		(void);
static 	void	tmrinit			(void);
static 	INT8U	verpass 		(INT8U pmsg[]);
static	void 	disppass		(void);
static	INT8U randgen			(void);
static	void 	checkEEPROM	(void);
static  void 	sendSMS 		(INT8U situ);
static 	void 	fpsett			(void);
static 	bit 	read_pass		(INT8U pass_temp[]);
static 	void	displock		(void);
static 	void	EXTint_int	(void);

#endif