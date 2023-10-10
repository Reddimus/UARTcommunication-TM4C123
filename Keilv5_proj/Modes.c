#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "UART0.h"
#include "Display.h"
#include "LEDSW.h"
#include "SystickPWM.h"


void Mode1(void){
	char choice;
	do{
		Display_Mode1_Menu();
		choice = UART0_InChar(); 
	
		// Echo back the choice to the user
		UART0_OutString((uint8_t *)"You chose: ");
		UART0_OutChar(choice);
		OutCRLF0();  // Move to the next line
		
		switch(choice){

			case '1':
				UART0_OutString((uint8_t *)"Please select LED color: r(red), g(green), b(blue), p(purple), w(white), d(dark), c(cran)\n");
				// Read the character entered by the user
				// Send a confirmation message back to the user based on the selected color
				char color_char = UART0_InChar();
				// Call the function to set the LED color
				Set_LED_Color(color_char);
				Set_LED_Brightness(99);
				switch(color_char){
					case 'r':
						UART0_OutString((uint8_t *)"\r\nRed LED is on\n");
					break;
					
					case 'g':
						UART0_OutString((uint8_t *)"\r\nGreen LED is on\n");
					break;
					
					case 'b':
						UART0_OutString((uint8_t *)"\r\nBlue LED is on\n");
					break;
					
					case 'p':
						UART0_OutString((uint8_t *)"\r\nPurple LED is on\n");
					break;
					
					case 'w':
						UART0_OutString((uint8_t *)"\r\nWhite LED is on\n");
					break;
			
					case 'd':
						UART0_OutString((uint8_t *)"\r\nLED is off\n");
					break;
					
					case 'c':
						UART0_OutString((uint8_t *)"\r\nCranberry LED is on\n");
					break;
					
					default:
						UART0_OutString((uint8_t *)"\r\nInvalid color selection!\n");
					break;
					}
				break;					
					
				case '2':
						// Prompt the user to enter a brightness level
						UART0_OutString((uint8_t *)"Please enter a decimal number from 0 to 100 followed by a return: ");
    
						// Read the user input from UART as a number
						uint32_t brightness = UART0_InUDec();  // Replace with the actual function to read a number from UART
				if (brightness > 0 && brightness <100){
						Set_LED_Brightness(brightness);  // Set the LED brightness
						// Send confirmation message back to the user through UART
						UART0_OutString((uint8_t *)"Brightness set to ");
						UART0_OutUDec(brightness);
						UART0_OutString((uint8_t *)"%\n");
				}
					}
		}	
	while(choice!= '3');
}

void Mode2(void){
}

void Mode3(void){
}