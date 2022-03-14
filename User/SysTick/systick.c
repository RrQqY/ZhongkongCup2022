#include "systick.h"

// 利用SysTick计时器完成的DELAY功能，可以精确控制等待时间，单位为ms

// 微秒级别定时器
void SysTick_Delay_us(uint32_t us)
{
	SysTick_Config(72);       //配置为us的基本单位72  clk=72M时，1 us=72*(1/72M)
	uint32_t i;
	for(i=0; i<us; i++){      // for循环us次，每次都判断systick的countflag置1，即systick已经计到0才进行下一次循环
		while( !((SysTick->CTRL) & (1<<16)) );      // 等待systick的countflag置1，即systick已经计到0
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;    // 关闭systick使能
}


// 毫秒级别定时器
void SysTick_Delay_ms(uint32_t ms)
{
	SysTick_Config(72000);    // 配置为ms的基本单位72  clk=72M时，1 ms=72000*(1/72M)
	uint32_t i;
	for(i=0; i<ms; i++){      // for循环us次，每次都判断systick的countflag置1，即systick已经计到0才进行下一次循环
		while( !((SysTick->CTRL) & (1<<16)) );      // 等待systick的countflag置1，即systick已经计到0
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;    // 关闭systick使能
}


// 启动系统滴答定时器 SysTick
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0库版本
	if (SysTick_Config(SystemCoreClock/1000))	// ST3.5.0库版本SystemCoreClock/10不能超过16777216
	{ 
		/* Capture error */ 
		while (1);
	}
	
	//SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;       // 关闭滴答定时器  
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;          // 使能滴答定时器  1ms中断一次
}


/*    SysTick配置函数定义
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);    //判断tick的值是否大于24位，若大于则不符合规则
                                                               
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;    //初始化reload重新装载寄存器的值
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);    //配置中断优先级，配置为15

  SysTick->VAL   = 0;    //从初始化当前数值寄存器的值为0

  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |     //配置systick的时钟为72M
                   SysTick_CTRL_TICKINT_Msk   |     //使能中断
                   SysTick_CTRL_ENABLE_Msk;         //使能systick
  return (0);
}
*/