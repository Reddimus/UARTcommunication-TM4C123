#ifndef LEDSW_H
#define LEDSW_H

// TODO: define bit values for all Colors 
#include <stdint.h>
#define LEDs (*((volatile unsigned long *)0x40025038))  // use onboard three LEDs: PF321
#define RGB     0x0E //all three LEDs

#define SW1 0x10 //left switch
#define SW2 0x01 //right switch

#define COLORS_SIZE 8

#define MAX_ASCII 255

void LEDSW_Init(void);
uint8_t getLEDColorPortF(void);
uint8_t getLEDColorIdx(void);
uint8_t *getLEDColorName(void);
void setLEDColor(char color);

#endif
