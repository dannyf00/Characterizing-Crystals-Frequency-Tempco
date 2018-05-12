#include "ccp1.h"							//we use ccp1 / pwm mode

//hardware configuration
//end hardware configuration

//global defines

//global variables

//reset pwm generator
//time base = tmr2
void ccp1_init(char ps) {						//set up the pwm generator
	//set pr2 to the longest
	PR2 = 0xff;								//set pr2
	CCPR1L = PR2 / 2;						//50 percent duty cycle
	
	CCP1M3=1, CCP1M2=1, CCP1M1=0, CCP1M0=1;	//ccp1m3..0=1101, p1a.c=active high, p1b.d=active low
	//DC1B1=0, DC1B0=0;						//dc1b1..0=00, last two LSBs zero -> pwm resolution = 8bits max
	P1M1=0, P1M0=0;							//P1M1..0=00, single output on P1A, P1B..D as gpio
	
	//set up time base
	TMR2IF=0;								//clear tmr2 flag
	//T2CKPS1=0, T2CKPS0=0;					//t2 prescaler: 00=1:1, 01=1:4, 1x=1:16
	T2CONbits.T2CKPS = ps & 0x03;
	TMR2=0;									//strat from 0
	TMR2ON=1;								//timer2 is on
	
	//turn on pwm pin
	IO_OUT(PWM1_DDR, PWM1_CCP1);
}

//set pwm period
//void ccp1_setpr(uint8_t pr) {
//	PR2 = pr;								//set period
//}

//set duty cycle
//8-bit mode (10-bit mode available if DC1B1..0 used)
//void ccp1_setdc(uint8_t dc) {
//	//DC1B1 = (dc & 0x02)?1:0;				//set the least significant two bits
//	//DC1B0 = (dc & 0x01)?1:0;
//	CCPR1L = dc >> 0;						//most significant 8 bits
//}

//get period
//uint8_t ccp1_getpr(void) {
//	return PR2;
//}

//get dc
//uint8_t ccp1_getdc(void) {
//	return CCPR1L;
//}
