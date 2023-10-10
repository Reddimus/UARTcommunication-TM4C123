#include "tm4c123gh6pm.h"
#include "UART0.h"

void Display_Menu(void) 
{
	UART0_OutString((uint8_t *)"Welcome to CECS 447 Project 2  UART \r\n");
  UART0_OutString((uint8_t *)"MCU1 \r\n");
  UART0_OutString((uint8_t *)"Main Menu \r\n");
  UART0_OutString((uint8_t *)"1. PC to MCU1 LED Control \r\n");
  UART0_OutString((uint8_t *)"2. MCU1 to MCU2 Color Wheel (Not Available Yet)\r\n");
  UART0_OutString((uint8_t *)"3. PC to MCU1 to MCU2 to PC Chat Room (Not Available Yet)\r\n");
  UART0_OutString((uint8_t *)"Please choose a communication mode (enter 1 or 2 or 3): \r\n");
	
}

void Display_Mode1_Menu(void) {
    UART0_OutString((uint8_t *)"\r\nMode 1 Menu \r\n");
    UART0_OutString((uint8_t *)"Please select an option from the following list (enter 1 or 2 or 3): \r\n");
    UART0_OutString((uint8_t *)"1. Choose an LED color.\r\n");
    UART0_OutString((uint8_t *)"2. Change the brightness of current LED(s).\r\n");
    UART0_OutString((uint8_t *)"3. Exit \r\n");
}