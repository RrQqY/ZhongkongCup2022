#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include "stm32f10x.h" 
#include "core_cm3.h"    //内核里的外设定义都在core_cm3.h中

void SysTick_Delay_us(uint32_t us);
void SysTick_Delay_ms(uint32_t ms);
void SysTick_Init(void);

#endif
