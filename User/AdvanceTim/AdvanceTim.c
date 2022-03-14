#include "AdvanceTim.h"

// GPIO 初始化 
static void ADVANCE_TIM_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	// 输出比较通道 GPIO 初始化
	// 底盘左电机
	//     PWM输入
	RCC_APB2PeriphClockCmd(LEFTWHEEL_TIM_OUT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LEFTWHEEL_TIM_OUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LEFTWHEEL_TIM_OUT_PORT, &GPIO_InitStructure);
	//     PWM输出
	RCC_APB2PeriphClockCmd(LEFTWHEEL_TIM_IN_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LEFTWHEEL_TIM_IN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LEFTWHEEL_TIM_IN_PORT, &GPIO_InitStructure);
	
	// 底盘右电机
	//     PWM输入
	RCC_APB2PeriphClockCmd(RIGHTWHEEL_TIM_OUT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = RIGHTWHEEL_TIM_OUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RIGHTWHEEL_TIM_OUT_PORT, &GPIO_InitStructure);
	//     PWM输出
	RCC_APB2PeriphClockCmd(RIGHTWHEEL_TIM_IN_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = RIGHTWHEEL_TIM_IN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RIGHTWHEEL_TIM_IN_PORT, &GPIO_InitStructure);
	
	// 履带电机
	RCC_APB2PeriphClockCmd(TRACK_TIM_OUT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TRACK_TIM_OUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TRACK_TIM_OUT_PORT, &GPIO_InitStructure);
	
	// 滑轨电机
	//     PWM输入
	RCC_APB2PeriphClockCmd(SLIDE_TIM_OUT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SLIDE_TIM_OUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SLIDE_TIM_OUT_PORT, &GPIO_InitStructure);
	

//	// 输出比较通道互补通道 gpio 初始化
//	rcc_apb2periphclockcmd(advance_tim_ch1n_gpio_clk, enable);
//	gpio_initstructure.gpio_pin = advance_tim_ch1n_pin;
//	gpio_initstructure.gpio_mode = gpio_mode_af_pp;
//	gpio_initstructure.gpio_speed = gpio_speed_50mhz;
//	gpio_init(advance_tim_ch1n_port, &gpio_initstructure);

//	// 输出比较通道刹车通道 gpio 初始化
//	rcc_apb2periphclockcmd(advance_tim_bkin_gpio_clk, enable);
//	gpio_initstructure.gpio_pin = advance_tim_bkin_pin;
//	gpio_initstructure.gpio_mode = gpio_mode_af_pp;
//	gpio_initstructure.gpio_speed = gpio_speed_50mhz;
//	gpio_init(advance_tim_bkin_port, &gpio_initstructure);
    
//	// BKIN 引脚默认先输出低电平
//	GPIO_ResetBits(ADVANCE_TIM_BKIN_PORT,ADVANCE_TIM_BKIN_PIN);
}


// TIM 属性初始化 
static void ADVANCE_TIM_Mode_Config(void)
{ 
	LEFTWHEEL_TIM_OUT_APBxClock_FUN(LEFTWHEEL_TIM_OUT_CLK, ENABLE);    // 开启定时器时钟, 即内部时钟 CK_INT=72M
	LEFTWHEEL_TIM_IN_APBxClock_FUN(LEFTWHEEL_TIM_IN_CLK, ENABLE);
	RIGHTWHEEL_TIM_OUT_APBxClock_FUN(RIGHTWHEEL_TIM_OUT_CLK, ENABLE);
	RIGHTWHEEL_TIM_IN_APBxClock_FUN(RIGHTWHEEL_TIM_IN_CLK, ENABLE);
	TRACK_TIM_OUT_APBxClock_FUN(TRACK_TIM_OUT_CLK, ENABLE);
	SLIDE_TIM_OUT_APBxClock_FUN(SLIDE_TIM_OUT_CLK, ENABLE);
	
  /*--------------------时基结构体初始化-------------------------*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = ADVANCE_TIM_PERIOD;        // 自动重装载寄存器的值，累计 TIM_Period+1 个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Prescaler = ADVANCE_TIM_PSC;        // 驱动 CNT 计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;         // 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;     // 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;                // 重复计数器的值，没用到不用管
	
	TIM_TimeBaseInit(LEFTWHEEL_TIM_OUT, &TIM_TimeBaseStructure);      // 初始化定时器
	TIM_TimeBaseInit(RIGHTWHEEL_TIM_OUT, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TRACK_TIM_OUT, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(SLIDE_TIM_OUT, &TIM_TimeBaseStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler= 72-1;
	
	TIM_TimeBaseInit(LEFTWHEEL_TIM_IN, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(RIGHTWHEEL_TIM_IN, &TIM_TimeBaseStructure);
	
  /*--------------------输出比较结构体初始化-------------------*/
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                 // 配置为 PWM 模式 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;     // 输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;   // 互补输出使能
	TIM_OCInitStructure.TIM_Pulse = ADVANCE_TIM_PULSE;                // 设置占空比大小
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;         // 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;       // 互补输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;        // 输出通道空闲电平极性配置
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;    // 互补输出通道空闲电平极性配置
	
	TIM_OC1Init(LEFTWHEEL_TIM_OUT, &TIM_OCInitStructure);
	TIM_OC2Init(LEFTWHEEL_TIM_IN, &TIM_OCInitStructure);
	TIM_OC3Init(RIGHTWHEEL_TIM_OUT, &TIM_OCInitStructure);
	TIM_OC4Init(RIGHTWHEEL_TIM_IN, &TIM_OCInitStructure);
	TIM_OC1Init(TRACK_TIM_OUT, &TIM_OCInitStructure);
	TIM_OC4Init(SLIDE_TIM_OUT, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(LEFTWHEEL_TIM_OUT, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(LEFTWHEEL_TIM_IN, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(RIGHTWHEEL_TIM_OUT, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(RIGHTWHEEL_TIM_IN, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TRACK_TIM_OUT, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(SLIDE_TIM_OUT, TIM_OCPreload_Enable);
	
	/*--------------------输入捕获结构体初始化-------------------*/
	TIM_ICInitTypeDef TIM_ICInitStructure;
	// 左轮反馈通道配置
	// 捕获通道 IC1 配置 
  TIM_ICInitStructure.TIM_Channel = LEFTWHEEL_TIM_IN_PWM_CHANNEL;          // 选择捕获通道
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;              // 设置捕获的边沿
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;          // 设置捕获通道的信号来自于哪个输入通道，有直连和非直连两种
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;                    // 1 分频，即捕获信号的每个有效边沿都捕获
  TIM_ICInitStructure.TIM_ICFilter = 0x0;                                  // 不滤波
	
  TIM_PWMIConfig(LEFTWHEEL_TIM_IN, &TIM_ICInitStructure);                  // 初始化 PWM 输入模式
  // 当工作做 PWM 输入模式时，只需要设置触发信号的那一路即可（用于测量周期）。另外一路（用于测量占空比）会由硬件自带设置，不需要再配置
  TIM_SelectInputTrigger(LEFTWHEEL_TIM_IN, TIM_TS_TI1FP1);                 // 选择输入捕获的触发信号
  TIM_SelectSlaveMode(LEFTWHEEL_TIM_IN, TIM_SlaveMode_Reset);              // 选择从模式:复位模式
  TIM_SelectMasterSlaveMode(LEFTWHEEL_TIM_IN,TIM_MasterSlaveMode_Enable);  // PWM 输入模式时，从模式必须工作在复位模式，当捕获开始时，计数器 CNT 会被复位
  
	TIM_ITConfig(LEFTWHEEL_TIM_IN, TIM_IT_CC1, ENABLE);        // 使能捕获中断，这个中断针对的是主捕获通道（测量周期那个）
  TIM_ClearITPendingBit(LEFTWHEEL_TIM_IN, TIM_IT_CC1);                     // 清除中断标志位
  TIM_Cmd(LEFTWHEEL_TIM_IN, ENABLE);                                       // 使能高级控制定时器，计数器开始计数
	
	// 右轮反馈通道配置
	// 捕获通道 IC1 配置 
  TIM_ICInitStructure.TIM_Channel = RIGHTWHEEL_TIM_IN_PWM_CHANNEL;         // 选择捕获通道
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;              // 设置捕获的边沿
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;          // 设置捕获通道的信号来自于哪个输入通道，有直连和非直连两种
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;                    // 1 分频，即捕获信号的每个有效边沿都捕获
  TIM_ICInitStructure.TIM_ICFilter = 0x0;                                  // 不滤波
	
  TIM_PWMIConfig(RIGHTWHEEL_TIM_IN, &TIM_ICInitStructure);                 // 初始化 PWM 输入模式
  // 当工作做 PWM 输入模式时，只需要设置触发信号的那一路即可（用于测量周期）。另外一路（用于测量占空比）会由硬件自带设置，不需要再配置
  TIM_SelectInputTrigger(RIGHTWHEEL_TIM_IN, TIM_TS_TI1FP1);             // 选择输入捕获的触发信号
  TIM_SelectSlaveMode(RIGHTWHEEL_TIM_IN, TIM_SlaveMode_Reset);          // 选择从模式:复位模式
  TIM_SelectMasterSlaveMode(RIGHTWHEEL_TIM_IN,TIM_MasterSlaveMode_Enable); // PWM 输入模式时，从模式必须工作在复位模式，当捕获开始时，计数器 CNT 会被复位
  
	TIM_ITConfig(RIGHTWHEEL_TIM_IN, TIM_IT_CC1, ENABLE);       // 使能捕获中断，这个中断针对的是主捕获通道（测量周期那个）
  TIM_ClearITPendingBit(RIGHTWHEEL_TIM_IN, TIM_IT_CC1);                    // 清除中断标志位
  TIM_Cmd(RIGHTWHEEL_TIM_IN, ENABLE);                                      // 使能高级控制定时器，计数器开始计数

//	/*-------------------刹车和死区结构体初始化-------------------*/
//	// 有关刹车和死区结构体的成员具体可参考 BDTR 寄存器的描述
//	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
//	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
//	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
//	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
//	// 输出比较信号死区时间配置，具体如何计算可参考 BDTR:UTG[7:0] 的描述，这里配置的死区时间为 152ns
//	TIM_BDTRInitStructure.TIM_DeadTime = 11;
//	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
//	// 当 BKIN 引脚检测到高电平的时候，输出比较信号被禁止，就好像是刹车一样
//	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
//	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
//	TIM_BDTRConfig(ADVANCE_TIM, &TIM_BDTRInitStructure);

	TIM_Cmd(LEFTWHEEL_TIM_OUT, ENABLE);          // 使能计数器
	TIM_Cmd(RIGHTWHEEL_TIM_OUT, ENABLE);
	TIM_Cmd(TRACK_TIM_OUT, ENABLE);
	TIM_Cmd(SLIDE_TIM_OUT, ENABLE);
	
	TIM_CtrlPWMOutputs(LEFTWHEEL_TIM_OUT, ENABLE);     // 主输出使能，当使用的是通用定时器时，这句不需要
	TIM_CtrlPWMOutputs(RIGHTWHEEL_TIM_OUT, ENABLE);
	TIM_CtrlPWMOutputs(TRACK_TIM_OUT, ENABLE);
	TIM_CtrlPWMOutputs(SLIDE_TIM_OUT, ENABLE);
}


// 中断优先级配置
static void ADVANCE_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		          // 设置中断组为0
    NVIC_InitStructure.NVIC_IRQChannel = LEFTWHEEL_TIM_IN_IRQ; 	// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  // 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // 设置响应优先级	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	  NVIC_InitStructure.NVIC_IRQChannel = RIGHTWHEEL_TIM_IN_IRQ; // 设置中断来源  
	  NVIC_Init(&NVIC_InitStructure);
}


// TIM 总初始化
void ADVANCE_TIM_Init() {
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_NVIC_Config();
  ADVANCE_TIM_Mode_Config();
}


// 修改 PWM 占空比
void Set_Speed(__IO uint16_t * ccr, uint32_t speed) {    // speed为[0,T]的值
	// 根据参数值修改定时器的比较寄存器值
	*ccr = speed;
}

