//Using PIC16F684 to generate PWM in steps
//
//
//
//connection:
//
//
//
//                 |----------------------|
//                 |                      |
//      |--------->| BTN_PIN              |
//      |          |                      |
//      |          |                      |                    20v
//      / Button   |                      |                     V
//     /           |                      |                     |
//      |          |                      |                     |
//      |          |                      |                     |
//      |          |                      |                     -
//     ---GND      |      PIC16F684       |                    | | Heater
//      -          |                      |                    | | (100R) ------thermally coupled------- [Crystal/NTC/DUT]
//                 |                      |                     -
//                 |                      |                     |
//                 |                      |                     |
//                 |                      |                  |--|  Switch (FQP1N60C)
//                 |             CCP1/P1A |------------>---| |
//                 |                      |                  |--|
//                 |                      |                     |
//                 |                      |                    ---GND
//                 |                      |                     -
//                 |                      |
//                 |                      |
//                 |                      |
//                 |                      |
//                 |                      |
//                 |----------------------|
//
//
//1) short BTN_PIN to ground to increment PWM duty cycle

#include "config.h"							//configuration words - use external crystal: HS/XT
#include "gpio.h"                           //we use gpio functions
#include "delay.h"                          //we use software delays
#include "ccp1.h"							//we use ccp1 for 10-bit pwm

//hardware configuration
#define BTN_PORT		PORTA
#define BTN_DDR			TRISA
#define BTN_PIN			(1<<0)				//Button pin, has to be on PORTA as IOCA is used
#define BTN_DLY			1000				//delay, in ms @1Mhz

#define DC_INC			(DC_TOP/20)			//duty cycle increments, 1/20=5%
#define DC_TOP			200					//top of the duty cycle
//end hardware configuration

//global defines

//global variables
char dc=0;									//duty cycle

int main(void) {
	
	mcu_init();							    //initialize the mcu
	ccp1_init(TMR2_PS16x);							//reset the ccp1
	ccp1_setpr(DC_TOP);						//set the top
	ccp1_setdc(0);							//set duty cycle
	//ccp1_setdc10(3);						//10-bit duty cycle

	//set up the button pin
	dc = 0;									//starts with 0% dc
	IO_IN(BTN_DDR, BTN_PIN);				//btn as input
	nRAPU = 0; IO_SET(WPUA, BTN_PIN);		//0->enable weak pull-up
	IO_SET(IOCA, BTN_PIN);					//1->enable ioca
	BTN_PORT; RAIF = 0;						//0->clear porta interrupt flag
	RAIE = 0;								//0->disable porta interrupt
	di();
	while (1) {
		if (RAIF) {
			delay_ms(BTN_DLY);				//waste sometime, wait for the button to settle
			BTN_PORT; RAIF = 0;				//0->clear porta interrupt flag
			dc = (dc+DC_INC > DC_TOP)?0:(dc+DC_INC);					//increment DC
			ccp1_setdc(dc);					//set the duty cycle
		}
	}
}

