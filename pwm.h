#ifndef _PWM_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
#define PWM_PORT		PORTC
#define PWM_DDR			TRISC
#define PWM_P1A			(1<<5)			//p1a on rc5
#define PWM_P1B			(1<<4)			//p1b on rc5
#define PWM_P1C			(1<<3)			//p1b on rc5
#define PWM_P1D			(1<<2)			//p1c on rc5
//end hardware configuration

//global defines

//global variables

//reset pwm generator
//time base = tmr2
void pwm_init(void);

//set pwm period
#define pwm_setpr(pr)	PR2 = (pr)

//set duty cycle
//8-bit mode (10-bit mode available if DC1B1..0 used)
#define pwm_setdc(dc)	CCPR1L = (dc)
//10-bit mode available if DC1B1..0 used
#define pwm_setdc10(dc)	do {CCPR1L = (dc) >> 2; DC1B1 = (dc) & (1<<1); DC1B0 = (dc) & (1<<0);} while (0)

//get period
#define pwm_getpr()	PR2

//get dc
#define pwm_getdc()	CCPR1L

#endif
