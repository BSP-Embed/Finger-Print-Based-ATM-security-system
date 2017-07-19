/* uart.c: uart interface program  */
#include"uart.h"
void uartinit(void){	      // INITIALIZE SERIAL PORT
		SCON 		= 0x50;			      		// SERIAL MODE 1, 8-DATA BIT 1-START BIT, 1-STOP BIT, REN ENABLED
		RCAP2H 	= 0xFF;
		RCAP2L 	= 0xFA;
		T2CON 	= 0x34;	/* Enable TCLK, RCLK, start tmr */
}
void putchar(INT8U serialdata){ 
	SBUF = serialdata;			// LOAD DATA TO SERIAL BUFFER REGISTER
	while(TI == 0);				// WAIT UNTIL TRANSMISSION TO COMPLETE
	TI = 0;					// CLEAR TRANSMISSION INTERRUPT FLAG
}
INT8U getchar(void){
	while(RI == 0);				// WAIT UNTIL DATA IS RECEIVED 
	RI = 0;					// CLEAR FLAG
	return SBUF;				// RETURN SERIAL DATA
}
void puts(INT8U *s){
	while(*s) putchar(*s++);
}
