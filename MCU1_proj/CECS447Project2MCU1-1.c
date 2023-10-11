// CECS447Project2MCU1.c
// Runs on TM4C123
// Starter file for CEC447 Project 2 UART MCU1
// Min He
// September 26, 2023

#include "PLL.h"
//#include "UART2.h"
#include "LEDSW.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "UART0.h"
#include "Display.h"
#include "Modes.h"
#include "SystickPWM.h"

#define MAX_STR_LEN 20

extern void EnableInterrupts(void);
extern void WaitForInterrupt(void);
extern void DisableInterrupts(void);


int main(void) {
	DisableInterrupts();
	PLL_Init();
	LEDSW_Init();  // Initialize the onboard three LEDs and two push buttons
	SysTick_Init();
	UART0_Init();  // for PC<->MCU1
	//	UART2_Init();  // for MCU1<->MCU2
	EnableInterrupts();

	while(1) {
		// displays the main menu 
		Display_Menu(); 
		switch(UART0_InChar()) {
			case '1':
				Mode1();
				break;
			case '2':
				Mode2();
				break;
			case '3': 
				Mode3();
				break;
			default:
				break; 
		}
		OutCRLF0();
	}
}
