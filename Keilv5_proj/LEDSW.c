#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "LEDSW.h"

// Constants
#define NVIC_EN0_PORTF 0x40000000  // enable PORTF edge interrupt
const uint8_t colors[COLORS_SIZE]= {DARK, RED, BLUE, GREEN, PURPLE, WHITE, CRAN};
volatile uint8_t colorsIdx;

void LEDSW_Init(void) {
	if ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0) {
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	// Activate F clocks
		while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0);
	}
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; 	// unlock GPIO Port F
	//LEDS
	GPIO_PORTF_AMSEL_R &= ~0x0E;      // 3) disable analog function
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // 4) GPIO clear bit PCTL  
	GPIO_PORTF_DIR_R |= 0x0E;         // 6) PF1-PF3 output
	GPIO_PORTF_AFSEL_R &= ~0x0E;      // 7) no alternate function     
	GPIO_PORTF_DEN_R |= 0x0E;         // 8) enable digital pins PF3-PF1
	//LED = Dark;                       // Turn off all LEDs.

	//Switches
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	// unlock GPIO Port F
	GPIO_PORTF_CR_R |= 0x1F;			// allow changes to PF4-0
	GPIO_PORTF_AMSEL_R &= ~0x1F;		// disable analog on PF4-0
	GPIO_PORTF_PCTL_R &= ~0x000FFFFF;	// PCTL GPIO on PF4-0
	GPIO_PORTF_DIR_R &= ~0x11;			// PF4,PF0 in, PF3-1 out
	GPIO_PORTF_AFSEL_R &= ~0x1F;		// disable alt funct on PF4-0
	GPIO_PORTF_PUR_R |= 0x11;			// enable pull-up on PF0 and PF4
	GPIO_PORTF_DEN_R |= 0x1F;			// enable digital I/O on PF4-0
	GPIO_PORTF_IS_R &= ~0x11;			// PF4,PF0 is edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x11;			// PF4,PF0 is not both edges
	GPIO_PORTF_IEV_R &= ~0x11;			// PF4,PF0 falling edge event
	GPIO_PORTF_ICR_R = 0x11;			// clear flag0,4
	GPIO_PORTF_IM_R |= 0x11;			// enable interrupt on PF0,PF4
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF1FFFFF)|0x00400000; // (g) bits:23-21 for PORTF, set priority to 2
	NVIC_EN0_R |= 0x40000000;			// (h) enable interrupt 30 in NVIC
}

void Set_LED_Color(char color) {
	switch(color) {
		case 'd':
			colorsIdx = 0;
			break;
		case 'r':
			colorsIdx = 1;
			break;
		case 'b':
			colorsIdx = 2;
			break;
		case 'g':
			colorsIdx = 3;
			break;
		case 'p':
			colorsIdx = 4;
			break;
		case 'w':
			colorsIdx = 5;
			break;
		case 'c':
			colorsIdx = 6;
			break;
		// default:
		// 	// Handle invalid color character if needed
		// 	break;
	}
	GPIO_PORTF_DATA_R = colors[colorsIdx];
}