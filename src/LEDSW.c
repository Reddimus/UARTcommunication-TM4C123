#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "LEDSW.h"
#include "UART0.h"

// Constants
#define NVIC_EN0_PORTF 0x40000000  // enable PORTF edge interrupt

typedef struct {
	uint8_t portf;
	uint8_t *name;
} colors_properties;

colors_properties colors[COLORS_SIZE] = {
	{0x00, (uint8_t *) "Off"},
	{0x02, (uint8_t *) "Red"},
	{0x04, (uint8_t *) "Blue"},
	{0x08, (uint8_t *) "Green"},
	{0x06, (uint8_t *) "Purple"},
	{0x0E, (uint8_t *) "White"},
	{0x0C, (uint8_t *) "Cran"}
};

char colorsChoice[MAX_ASCII];
volatile uint8_t colorsIdx;

void Colors_Init(void) {
	colorsIdx = 0;

	for (uint8_t asciiChar = 0; asciiChar < MAX_ASCII; asciiChar++) {
		colorsChoice[asciiChar] = -1;
	}
	colorsChoice['d'] = 0;
	colorsChoice['r'] = 1;
	colorsChoice['b'] = 2;
	colorsChoice['g'] = 3;
	colorsChoice['p'] = 4;
	colorsChoice['w'] = 5;
	colorsChoice['c'] = 6;
}

void LEDSW_Init(void) {
	if ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0) {
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;	// Activate F clocks
		while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)==0);
	}
	//LEDS
	GPIO_PORTF_AMSEL_R &= ~RGB;      // 3) disable analog function
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0; // 4) GPIO clear bit PCTL  
	GPIO_PORTF_DIR_R |= RGB;         // 6) PF1-PF3 output
	GPIO_PORTF_AFSEL_R &= ~RGB;      // 7) no alternate function     
	GPIO_PORTF_DEN_R |= RGB;         // 8) enable digital pins PF3-PF1
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

	Colors_Init();
}

uint8_t getLEDColorPortF(void) {
	return colors[colorsIdx].portf;
}

uint8_t getLEDColorIdx(void) {
	return colorsIdx;
}

uint8_t *getLEDColorName(void) {
	return colors[colorsIdx].name;
}

void setLEDColor(char color) {
	// If color is a valid choice, set the color
	if (colorsChoice[color] != -1) {
		colorsIdx = colorsChoice[color];
		GPIO_PORTF_DATA_R &= ~RGB;
		GPIO_PORTF_DATA_R |= getLEDColorPortF();
		UART0_OutString((uint8_t *)"\r\nLED = ");
		UART0_OutString(getLEDColorName());
		UART0_OutString((uint8_t *)"\n");
	}
	else {
		UART0_OutString((uint8_t *)"\r\nInvalid color choice\n");
	}
}
