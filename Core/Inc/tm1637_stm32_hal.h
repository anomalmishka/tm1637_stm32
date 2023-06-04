#ifndef TM1637_STM32_HAL_H
#define TM1637_STM32_HAL_H

#include "stm32f1xx_hal.h"

void tm1637Init(void);
void tm1637Display_4_Symbols(uint8_t data[], uint8_t dot);
void tm1637Display_String(char string[]);
void tm1637SetBrightness(uint8_t brightness);

#endif
