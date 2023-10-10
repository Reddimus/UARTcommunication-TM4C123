// TODO: define bit values for all Colors 
#include <stdint.h>
#define LEDs (*((volatile unsigned long *)0x40025038))  // use onboard three LEDs: PF321
#define RED 		(0x02)
#define BLUE 		(0x04)
#define GREEN 	(0x08)
#define PURPLE 	(0x06)
#define WHITE 	(0x0E)
#define DARK 		(0x00)
#define CRAN 		(0x0C)

#define SW1 0x10 //left switch
#define SW2 0x01 //right switch

#define COLORS_SIZE 7

extern const uint8_t colors[COLORS_SIZE];
extern volatile uint8_t colorsIdx;

void LEDSW_Init(void);
void Set_LED_Color(char color);
