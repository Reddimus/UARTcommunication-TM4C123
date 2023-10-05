// main.c: example program for testing MCU to MCU communication
// Runs on TM4C123GH6PM 

// board to board communitation use UART1
// Ground connected ground in the USB cable
#include "tm4c123gh6pm.h"
#include "UART.h"

// bit address definition for port data registers
#define LED (*((volatile uint32_t *)0x40025038))  // use onboard RED LED: PF3-PF1

////////// Constants //////////  
// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// white    RGB    0x0E
// pink     R-B    0x06
// Cran     -GB    0x0C

#define RGB		0x0E

#define DARK	0x00
#define RED		0x02
#define BLUE	0x04
#define GREEN	0x08

#define SW1		0x10
#define SW2		0x01

#define NVIC_EN0_PORTF	0x40000000

#define COLORS_SIZE 4

extern void DisableInterrupts(void);
extern void EnableInterrupts(void);  
extern void WaitForInterrupt(void);

void GPIO_PortF_Init(void);

static const uint8_t colors[COLORS_SIZE] = {DARK, RED, BLUE, GREEN};
volatile uint8_t colorsIdx;

int main(void) {	
	DisableInterrupts();	
	UART1_Init(true,false);	// initialize UART with RX interrupt
	GPIO_PortF_Init();		// initialize port F
	EnableInterrupts();		// needed for TExaS
	LED = DARK;
	colorsIdx = 0;
	
	while(1) {
		WaitForInterrupt();
	}
}

void GPIO_PortF_Init(void) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;				// (a) activate clock for port F
	while ((SYSCTL_RCGC2_R &= SYSCTL_RCGC2_GPIOF)==0);

	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;					// 2) unlock PortF PF0  
	GPIO_PORTF_CR_R |= 0x1F;							// allow changes to PF4-0       
	GPIO_PORTF_DIR_R |= 0x0E;							//		PF3,2,1 output
	GPIO_PORTF_DIR_R &= ~0x11;							//		PF4,0 input
	GPIO_PORTF_AFSEL_R &= ~0x1F;						//		disable alt funct on PF4-0
	GPIO_PORTF_DEN_R |= 0x1F;							//		enable digital I/O on PF4-0
	GPIO_PORTF_PCTL_R &= ~0x000FFFFF;					// 		configure PF4-0 as GPIO
	GPIO_PORTF_AMSEL_R &= ~0x1F;						//		disable analog functionality on PF4-0
	GPIO_PORTF_PUR_R |= 0x11;							//		enable weak pull-up on PF0,4

	GPIO_PORTF_IS_R &= ~0x11;							// (d) PF0,4 is edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x11;							//		PF0,4 is not both edges
	GPIO_PORTF_IEV_R |= 0x11;							//		PF4 rising edge event
	GPIO_PORTF_ICR_R = 0x11;							// (e) clear flag4
	GPIO_PORTF_IM_R |= 0x11;							// (f) arm interrupt on PF4
	NVIC_PRI7_R = (NVIC_PRI7_R&~0x00E00000)|0x00C00000;	// (g) priority 6
	NVIC_EN0_R |= NVIC_EN0_PORTF;						// (h) enable interrupt 30 in NVIC
}

void GPIOPortF_Handler(void) {		
	// simple debouncing code: generate 20ms to 30ms delay
	for (uint32_t time=0;time<80000;time++);
	
	if(GPIO_PORTF_RIS_R & SW2) {
		GPIO_PORTF_ICR_R = SW2;
		colorsIdx = (colorsIdx+1) % COLORS_SIZE;
		LED = colors[colorsIdx];
	}
	
	if(GPIO_PORTF_RIS_R & SW1) {
		GPIO_PORTF_ICR_R = SW1;
		UART1_OutChar(colorsIdx);
	}
}

// Take care of Rx interrupt and ignore Tx interrupt
void UART1_Handler(void) {
	if(UART1_RIS_R&UART_RIS_RXRIS) {		// received one item
		if ((UART1_FR_R&UART_FR_RXFE) == 0) {
			colorsIdx = UART1_DR_R & (COLORS_SIZE - 1);		//	read transmitted state/colors index
			LED = colors[colorsIdx];						// using current state/index change LED
		}
		UART1_ICR_R = UART_ICR_RXIC;		// acknowledge RX FIFO
	}
}
