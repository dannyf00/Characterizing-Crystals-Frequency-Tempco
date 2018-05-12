#ifndef _PWM_H

#include "gpio.h"                           //we use gpio functions

//hardware configuration
#define PWM1_PORT			PORTC
#define PWM1_DDR			TRISC
#define PWM1_CCP1			(1<<5)			//ccp1 on rc5
#define PWM1_P1A			(1<<5)			//p1a on rc5
#define PWM1_P1B			(1<<4)			//p1b on rc5
#define PWM1_P1C			(1<<3)			//p1b on rc5
#define PWM1_P1D			(1<<2)			//p1c on rc5
//end hardware configuration

//global defines
#define TMR2_PS1x			0x00
#define TMR2_PS4x			0x01
#define TMR2_PS16x			0x03

//global variables

//reset pwm generator
//time base = tmr2
void ccp1_init(char ps);

//set pwm period
#define ccp1_setpr(pr)	PR2 = (pr)

//set duty cycle
//8-bit mode (10-bit mode available if DC1B1..0 used)
#define ccp1_setdc(dc)	CCPR1L = (dc)
//10-bit mode available if DC1B1..0 used
#define ccp1_setdc10(dc)	do {CCPR1L = (dc) >> 2; DC1B1 = ((dc) & (1<<1))?1:0; DC1B0 = (dc) & (1<<0);} while (0)

//get period
#define ccp1_getpr()	PR2

//get dc
#define  ccp1_getdc()	CCPR1L

#endif
