#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "LEDSW.h"
#include "SystickPWM.h"

#define PERIOD	 					50000 					// num of machine cycles for 10ms, value is based on 50MHz system clock
#define HALF_DUTY   			PERIOD/2 			// 50% duty cycle

// Global variables: 
// H: number of clocks cycles for duty cycle
// L: number of clock cycles for non-duty cycle

uint32_t brightness;
volatile uint32_t high;
volatile uint32_t low;

void SysTick_Init(void){
	colorsIdx = 0;
  NVIC_ST_CTRL_R = 0;           			// disable SysTick during setup
  NVIC_ST_RELOAD_R = HALF_DUTY - 1;     // reload value for 50% duty cycle
  NVIC_ST_CURRENT_R = 0;        			// any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x1FFFFFFF)|0x40000000; // bit 31-29 for SysTick, set priority to 2
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC + NVIC_ST_CTRL_INTEN + NVIC_ST_CTRL_ENABLE;  // enable with core clock and interrupts, start systick timer
	//NVIC_ST_CTRL_R |= 0x00000007;  // enable with core clock and interrupts, start systick timer
}

void SysTick_Handler(void){
	
	//NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE; //clear systick	
	if(GPIO_PORTF_DATA_R & 0x0E){
		GPIO_PORTF_DATA_R &= ~0x0E; //controls the brightness
		NVIC_ST_RELOAD_R = low - 1;  // Number of counts to wait pf3 pf2 pf1 pf0 = 1110
	} 
	else {
		GPIO_PORTF_DATA_R |= colors[colorsIdx];
		NVIC_ST_RELOAD_R = high - 1;
	}
	NVIC_ST_CURRENT_R = 0;  // Any value written to CURRENT clears
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}

void Set_LED_Brightness(uint32_t brightness_level) {
	// Validate the input and call Set_LED_Brightness with the user-input brightness level 
		high = (PERIOD * brightness_level) / 100; // Calculate ON time
    low = PERIOD - high; // Calculate OFF time
}