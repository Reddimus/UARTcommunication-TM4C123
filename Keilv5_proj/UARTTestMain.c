
// UARTTestMain.c
// Runs on LM4F120/TM4C123
// Used to test the UART.c driver
// Daniel Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// Modified by Dr. Min He on 9/23/2023

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

#include "PLL.h"
#include "UART.h"
#include <stdint.h>
#include <stdbool.h>  // for C boolean data type
#include "tm4c123gh6pm.h"
#define MAX_STR_LEN 20

void PortF_Init(void);

int main(void){
  uint8_t i;
  uint8_t string[MAX_STR_LEN];  // global to assist in debugging
  uint32_t n;

  PLL_Init();
  UART_Init(false,false);              // initialize UART
  PortF_Init(); // Initialize Port F
  OutCRLF();
  for(i='A'; i<='Z'; i=i+1){// print the uppercase alphabet
    UART_OutChar(i);
  }
  OutCRLF();
  UART_OutChar(' ');
  for(i='a'; i<='z'; i=i+1){// print the lowercase alphabet
    UART_OutChar(i);
  }
  OutCRLF();
  UART_OutChar('-');
  UART_OutChar('-');
  UART_OutChar('>');
  OutCRLF();
  while(1)
	{
    UART_OutString((uint8_t *)"Choose a color (r)ed, (b)lue, (g)reen: ");
    char color = UART_InChar(); // Assume this function reads a single character
    UART_OutChar(color);
    OutCRLF();
    
    // Turn off all LEDs
    GPIO_PORTF_DATA_R &= ~0x0E;
    
    switch(color)
		{
        case 'r':
            GPIO_PORTF_DATA_R |= 0x02; // Turn on red LED (PF1)
            break;
        case 'b':
            GPIO_PORTF_DATA_R |= 0x04; // Turn on blue LED (PF2)
            break;
        case 'g':
            GPIO_PORTF_DATA_R |= 0x08; // Turn on green LED (PF3)
            break;
        default:
            UART_OutString((uint8_t *)"Invalid color selected!");
            OutCRLF();
            break;
    }
  }
}

void PortF_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20;            // Activate clock for Port F
    while((SYSCTL_PRGPIO_R&0x20) == 0){}; // Wait for Port F to be ready
    GPIO_PORTF_DIR_R |= 0x0E;             // Set PF1, PF2, PF3 as output
    GPIO_PORTF_DEN_R |= 0x0E;             // Enable digital functionality on PF1, PF2, PF3
}


