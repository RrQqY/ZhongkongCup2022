#include "systick.h"

// ����SysTick��ʱ����ɵ�DELAY���ܣ����Ծ�ȷ���Ƶȴ�ʱ�䣬��λΪms

// ΢�뼶��ʱ��
void SysTick_Delay_us(uint32_t us)
{
	SysTick_Config(72);       //����Ϊus�Ļ�����λ72  clk=72Mʱ��1 us=72*(1/72M)
	uint32_t i;
	for(i=0; i<us; i++){      // forѭ��us�Σ�ÿ�ζ��ж�systick��countflag��1����systick�Ѿ��Ƶ�0�Ž�����һ��ѭ��
		while( !((SysTick->CTRL) & (1<<16)) );      // �ȴ�systick��countflag��1����systick�Ѿ��Ƶ�0
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;    // �ر�systickʹ��
}


// ���뼶��ʱ��
void SysTick_Delay_ms(uint32_t ms)
{
	SysTick_Config(72000);    // ����Ϊms�Ļ�����λ72  clk=72Mʱ��1 ms=72000*(1/72M)
	uint32_t i;
	for(i=0; i<ms; i++){      // forѭ��us�Σ�ÿ�ζ��ж�systick��countflag��1����systick�Ѿ��Ƶ�0�Ž�����һ��ѭ��
		while( !((SysTick->CTRL) & (1<<16)) );      // �ȴ�systick��countflag��1����systick�Ѿ��Ƶ�0
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;    // �ر�systickʹ��
}


// ����ϵͳ�δ�ʱ�� SysTick
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0��汾
	if (SysTick_Config(SystemCoreClock/1000))	// ST3.5.0��汾SystemCoreClock/10���ܳ���16777216
	{ 
		/* Capture error */ 
		while (1);
	}
	
	//SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;       // �رյδ�ʱ��  
	
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;          // ʹ�ܵδ�ʱ��  1ms�ж�һ��
}


/*    SysTick���ú�������
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);    //�ж�tick��ֵ�Ƿ����24λ���������򲻷��Ϲ���
                                                               
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;    //��ʼ��reload����װ�ؼĴ�����ֵ
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);    //�����ж����ȼ�������Ϊ15

  SysTick->VAL   = 0;    //�ӳ�ʼ����ǰ��ֵ�Ĵ�����ֵΪ0

  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |     //����systick��ʱ��Ϊ72M
                   SysTick_CTRL_TICKINT_Msk   |     //ʹ���ж�
                   SysTick_CTRL_ENABLE_Msk;         //ʹ��systick
  return (0);
}
*/