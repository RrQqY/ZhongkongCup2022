#include "AdvanceTim.h"

// GPIO ��ʼ�� 
static void ADVANCE_TIM_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	// ����Ƚ�ͨ�� GPIO ��ʼ��
	// ��������
	//     PWM����
	RCC_APB2PeriphClockCmd(LEFTWHEEL_TIM_OUT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LEFTWHEEL_TIM_OUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LEFTWHEEL_TIM_OUT_PORT, &GPIO_InitStructure);
	//     PWM���
	RCC_APB2PeriphClockCmd(LEFTWHEEL_TIM_IN_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = LEFTWHEEL_TIM_IN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LEFTWHEEL_TIM_IN_PORT, &GPIO_InitStructure);
	
	// �����ҵ��
	//     PWM����
	RCC_APB2PeriphClockCmd(RIGHTWHEEL_TIM_OUT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = RIGHTWHEEL_TIM_OUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RIGHTWHEEL_TIM_OUT_PORT, &GPIO_InitStructure);
	//     PWM���
	RCC_APB2PeriphClockCmd(RIGHTWHEEL_TIM_IN_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = RIGHTWHEEL_TIM_IN_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RIGHTWHEEL_TIM_IN_PORT, &GPIO_InitStructure);
	
	// �Ĵ����
	RCC_APB2PeriphClockCmd(TRACK_TIM_OUT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = TRACK_TIM_OUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TRACK_TIM_OUT_PORT, &GPIO_InitStructure);
	
	// ������
	//     PWM����
	RCC_APB2PeriphClockCmd(SLIDE_TIM_OUT_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SLIDE_TIM_OUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SLIDE_TIM_OUT_PORT, &GPIO_InitStructure);
	

//	// ����Ƚ�ͨ������ͨ�� gpio ��ʼ��
//	rcc_apb2periphclockcmd(advance_tim_ch1n_gpio_clk, enable);
//	gpio_initstructure.gpio_pin = advance_tim_ch1n_pin;
//	gpio_initstructure.gpio_mode = gpio_mode_af_pp;
//	gpio_initstructure.gpio_speed = gpio_speed_50mhz;
//	gpio_init(advance_tim_ch1n_port, &gpio_initstructure);

//	// ����Ƚ�ͨ��ɲ��ͨ�� gpio ��ʼ��
//	rcc_apb2periphclockcmd(advance_tim_bkin_gpio_clk, enable);
//	gpio_initstructure.gpio_pin = advance_tim_bkin_pin;
//	gpio_initstructure.gpio_mode = gpio_mode_af_pp;
//	gpio_initstructure.gpio_speed = gpio_speed_50mhz;
//	gpio_init(advance_tim_bkin_port, &gpio_initstructure);
    
//	// BKIN ����Ĭ��������͵�ƽ
//	GPIO_ResetBits(ADVANCE_TIM_BKIN_PORT,ADVANCE_TIM_BKIN_PIN);
}


// TIM ���Գ�ʼ�� 
static void ADVANCE_TIM_Mode_Config(void)
{ 
	LEFTWHEEL_TIM_OUT_APBxClock_FUN(LEFTWHEEL_TIM_OUT_CLK, ENABLE);    // ������ʱ��ʱ��, ���ڲ�ʱ�� CK_INT=72M
	LEFTWHEEL_TIM_IN_APBxClock_FUN(LEFTWHEEL_TIM_IN_CLK, ENABLE);
	RIGHTWHEEL_TIM_OUT_APBxClock_FUN(RIGHTWHEEL_TIM_OUT_CLK, ENABLE);
	RIGHTWHEEL_TIM_IN_APBxClock_FUN(RIGHTWHEEL_TIM_IN_CLK, ENABLE);
	TRACK_TIM_OUT_APBxClock_FUN(TRACK_TIM_OUT_CLK, ENABLE);
	SLIDE_TIM_OUT_APBxClock_FUN(SLIDE_TIM_OUT_CLK, ENABLE);
	
  /*--------------------ʱ���ṹ���ʼ��-------------------------*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = ADVANCE_TIM_PERIOD;        // �Զ���װ�ؼĴ�����ֵ���ۼ� TIM_Period+1 ��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Prescaler = ADVANCE_TIM_PSC;        // ���� CNT ��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;         // ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;     // ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;                // �ظ���������ֵ��û�õ����ù�
	
	TIM_TimeBaseInit(LEFTWHEEL_TIM_OUT, &TIM_TimeBaseStructure);      // ��ʼ����ʱ��
	TIM_TimeBaseInit(RIGHTWHEEL_TIM_OUT, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TRACK_TIM_OUT, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(SLIDE_TIM_OUT, &TIM_TimeBaseStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler= 72-1;
	
	TIM_TimeBaseInit(LEFTWHEEL_TIM_IN, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(RIGHTWHEEL_TIM_IN, &TIM_TimeBaseStructure);
	
  /*--------------------����ȽϽṹ���ʼ��-------------------*/
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;                 // ����Ϊ PWM ģʽ 1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;     // ���ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;   // �������ʹ��
	TIM_OCInitStructure.TIM_Pulse = ADVANCE_TIM_PULSE;                // ����ռ�ձȴ�С
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;         // ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;       // �������ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;        // ���ͨ�����е�ƽ��������
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;    // �������ͨ�����е�ƽ��������
	
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
	
	/*--------------------���벶��ṹ���ʼ��-------------------*/
	TIM_ICInitTypeDef TIM_ICInitStructure;
	// ���ַ���ͨ������
	// ����ͨ�� IC1 ���� 
  TIM_ICInitStructure.TIM_Channel = LEFTWHEEL_TIM_IN_PWM_CHANNEL;          // ѡ�񲶻�ͨ��
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;              // ���ò���ı���
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;          // ���ò���ͨ�����ź��������ĸ�����ͨ������ֱ���ͷ�ֱ������
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;                    // 1 ��Ƶ���������źŵ�ÿ����Ч���ض�����
  TIM_ICInitStructure.TIM_ICFilter = 0x0;                                  // ���˲�
	
  TIM_PWMIConfig(LEFTWHEEL_TIM_IN, &TIM_ICInitStructure);                  // ��ʼ�� PWM ����ģʽ
  // �������� PWM ����ģʽʱ��ֻ��Ҫ���ô����źŵ���һ·���ɣ����ڲ������ڣ�������һ·�����ڲ���ռ�ձȣ�����Ӳ���Դ����ã�����Ҫ������
  TIM_SelectInputTrigger(LEFTWHEEL_TIM_IN, TIM_TS_TI1FP1);                 // ѡ�����벶��Ĵ����ź�
  TIM_SelectSlaveMode(LEFTWHEEL_TIM_IN, TIM_SlaveMode_Reset);              // ѡ���ģʽ:��λģʽ
  TIM_SelectMasterSlaveMode(LEFTWHEEL_TIM_IN,TIM_MasterSlaveMode_Enable);  // PWM ����ģʽʱ����ģʽ���빤���ڸ�λģʽ��������ʼʱ�������� CNT �ᱻ��λ
  
	TIM_ITConfig(LEFTWHEEL_TIM_IN, TIM_IT_CC1, ENABLE);        // ʹ�ܲ����жϣ�����ж���Ե���������ͨ�������������Ǹ���
  TIM_ClearITPendingBit(LEFTWHEEL_TIM_IN, TIM_IT_CC1);                     // ����жϱ�־λ
  TIM_Cmd(LEFTWHEEL_TIM_IN, ENABLE);                                       // ʹ�ܸ߼����ƶ�ʱ������������ʼ����
	
	// ���ַ���ͨ������
	// ����ͨ�� IC1 ���� 
  TIM_ICInitStructure.TIM_Channel = RIGHTWHEEL_TIM_IN_PWM_CHANNEL;         // ѡ�񲶻�ͨ��
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;              // ���ò���ı���
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;          // ���ò���ͨ�����ź��������ĸ�����ͨ������ֱ���ͷ�ֱ������
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;                    // 1 ��Ƶ���������źŵ�ÿ����Ч���ض�����
  TIM_ICInitStructure.TIM_ICFilter = 0x0;                                  // ���˲�
	
  TIM_PWMIConfig(RIGHTWHEEL_TIM_IN, &TIM_ICInitStructure);                 // ��ʼ�� PWM ����ģʽ
  // �������� PWM ����ģʽʱ��ֻ��Ҫ���ô����źŵ���һ·���ɣ����ڲ������ڣ�������һ·�����ڲ���ռ�ձȣ�����Ӳ���Դ����ã�����Ҫ������
  TIM_SelectInputTrigger(RIGHTWHEEL_TIM_IN, TIM_TS_TI1FP1);             // ѡ�����벶��Ĵ����ź�
  TIM_SelectSlaveMode(RIGHTWHEEL_TIM_IN, TIM_SlaveMode_Reset);          // ѡ���ģʽ:��λģʽ
  TIM_SelectMasterSlaveMode(RIGHTWHEEL_TIM_IN,TIM_MasterSlaveMode_Enable); // PWM ����ģʽʱ����ģʽ���빤���ڸ�λģʽ��������ʼʱ�������� CNT �ᱻ��λ
  
	TIM_ITConfig(RIGHTWHEEL_TIM_IN, TIM_IT_CC1, ENABLE);       // ʹ�ܲ����жϣ�����ж���Ե���������ͨ�������������Ǹ���
  TIM_ClearITPendingBit(RIGHTWHEEL_TIM_IN, TIM_IT_CC1);                    // ����жϱ�־λ
  TIM_Cmd(RIGHTWHEEL_TIM_IN, ENABLE);                                      // ʹ�ܸ߼����ƶ�ʱ������������ʼ����

//	/*-------------------ɲ���������ṹ���ʼ��-------------------*/
//	// �й�ɲ���������ṹ��ĳ�Ա����ɲο� BDTR �Ĵ���������
//	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
//	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
//	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
//	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
//	// ����Ƚ��ź�����ʱ�����ã�������μ���ɲο� BDTR:UTG[7:0] ���������������õ�����ʱ��Ϊ 152ns
//	TIM_BDTRInitStructure.TIM_DeadTime = 11;
//	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
//	// �� BKIN ���ż�⵽�ߵ�ƽ��ʱ������Ƚ��źű���ֹ���ͺ�����ɲ��һ��
//	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
//	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
//	TIM_BDTRConfig(ADVANCE_TIM, &TIM_BDTRInitStructure);

	TIM_Cmd(LEFTWHEEL_TIM_OUT, ENABLE);          // ʹ�ܼ�����
	TIM_Cmd(RIGHTWHEEL_TIM_OUT, ENABLE);
	TIM_Cmd(TRACK_TIM_OUT, ENABLE);
	TIM_Cmd(SLIDE_TIM_OUT, ENABLE);
	
	TIM_CtrlPWMOutputs(LEFTWHEEL_TIM_OUT, ENABLE);     // �����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��ʱ����䲻��Ҫ
	TIM_CtrlPWMOutputs(RIGHTWHEEL_TIM_OUT, ENABLE);
	TIM_CtrlPWMOutputs(TRACK_TIM_OUT, ENABLE);
	TIM_CtrlPWMOutputs(SLIDE_TIM_OUT, ENABLE);
}


// �ж����ȼ�����
static void ADVANCE_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		          // �����ж���Ϊ0
    NVIC_InitStructure.NVIC_IRQChannel = LEFTWHEEL_TIM_IN_IRQ; 	// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  // ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          // ������Ӧ���ȼ�	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	  NVIC_InitStructure.NVIC_IRQChannel = RIGHTWHEEL_TIM_IN_IRQ; // �����ж���Դ  
	  NVIC_Init(&NVIC_InitStructure);
}


// TIM �ܳ�ʼ��
void ADVANCE_TIM_Init() {
	ADVANCE_TIM_GPIO_Config();
	ADVANCE_TIM_NVIC_Config();
  ADVANCE_TIM_Mode_Config();
}


// �޸� PWM ռ�ձ�
void Set_Speed(__IO uint16_t * ccr, uint32_t speed) {    // speedΪ[0,T]��ֵ
	// ���ݲ���ֵ�޸Ķ�ʱ���ıȽϼĴ���ֵ
	*ccr = speed;
}

