#include "delay.h"
#include <intrins.h>

void dlyms(unsigned int time)
{
	unsigned char pause;		//  Declare variable pause as unsigned char
	while (time--) {			//  loop until value becomes zero	
		pause = 114;	 		//  Initialize pause to 114 (decimal value)
		while (pause--);	 	//  Decrement pause until it becomes zero	
	}				 			
}								 
void dly50us()
{
	unsigned char i;
   	for (i = 0; i < 10; i++)
			_nop_();
}


