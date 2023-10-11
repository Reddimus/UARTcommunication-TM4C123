#ifndef SYSTICKPWM_H
#define SYSTICKPWM_H

#include <stdint.h>

void SysTick_Init(void);
void SysTick_Handler(void);
void Set_LED_Brightness(uint32_t brightness_level);

#endif
