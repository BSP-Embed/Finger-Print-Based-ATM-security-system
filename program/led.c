/* led.c : LED interface programs */
#include "led.h"
void blink(INT8U nblink, INT8U ontime){
	while(nblink--){
		ledon();
		dlyms(ontime);
		ledoff();
		dlyms(100);
	}
}

	
