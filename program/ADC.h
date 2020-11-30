#ifndef ADC_H
#define ADC_H

//INCLUDES
#include "includes.h"

//DEFINE PORTS/PINS
#define SOC_PIN 	P3_7
#define EOC_PIN 	P3_5
#define RD_PIN     	P3_6

#define ADC_DP		 P1


//DEFINE CONSTANT
#define AVG_SAMPLES	16

// FUCTION PROTOTYPES
void	adc_init(void);
int8u 	adc_read(void);

#endif



