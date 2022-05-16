#ifndef __ADVANCETIM_H
#define __ADVANCETIM_H

#include "stm32f10x.h"

/*--------GPIO-Defination--------*/
// TIM 输出比较通道
// 底盘左电机
//     PWM输入（调速）
#define LEFTWHEEL_TIM_OUT_GPIO_CLK   RCC_APB2Periph_GPIOC
#define LEFTWHEEL_TIM_OUT_PORT       GPIOC
#define LEFTWHEEL_TIM_OUT_PIN        GPIO_Pin_6
//     PWM输出（反馈）
#define LEFTWHEEL_TIM_IN_GPIO_CLK    RCC_APB2Periph_GPIOC
#define LEFTWHEEL_TIM_IN_PORT        GPIOA
#define LEFTWHEEL_TIM_IN_PIN         GPIO_Pin_6

// 底盘右电机
//     PWM输入
#define RIGHTWHEEL_TIM_OUT_GPIO_CLK  RCC_APB2Periph_GPIOC
#define RIGHTWHEEL_TIM_OUT_PORT      GPIOC
#define RIGHTWHEEL_TIM_OUT_PIN       GPIO_Pin_8
//     PWM输出
#define RIGHTWHEEL_TIM_IN_GPIO_CLK   RCC_APB2Periph_GPIOC
#define RIGHTWHEEL_TIM_IN_PORT       GPIOB
#define RIGHTWHEEL_TIM_IN_PIN        GPIO_Pin_6

// 履带电机
//     PWM输入
#define TRACK_TIM_OUT_GPIO_CLK       RCC_APB2Periph_GPIOA
#define TRACK_TIM_OUT_PORT           GPIOA
#define TRACK_TIM_OUT_PIN            GPIO_Pin_8

// 滑轨电机
//     PWM输入
#define SLIDE_TIM_OUT_GPIO_CLK       RCC_APB2Periph_GPIOA
#define SLIDE_TIM_OUT_PORT           GPIOA
#define SLIDE_TIM_OUT_PIN            GPIO_Pin_11

//#define ADVANCE_TIM_CH1_GPIO_CLK  RCC_APB2Periph_GPIOA
//#define ADVANCE_TIM_CH1_PORT  GPIOA
//#define ADVANCE_TIM_CH1_PIN  GPIO_Pin_8

//// TIM1 输出比较通道的互补通道
//#define ADVANCE_TIM_CH1N_GPIO_CLK  RCC_APB2Periph_GPIOB
//#define ADVANCE_TIM_CH1N_PORT  GPIOB
//#define ADVANCE_TIM_CH1N_PIN  GPIO_Pin_13

//// TIM1 输出比较通道的刹车通道
//#define ADVANCE_TIM_BKIN_GPIO_CLK  RCC_APB2Periph_GPIOB
//#define ADVANCE_TIM_BKIN_PORT  GPIOB
//#define ADVANCE_TIM_BKIN_PIN  GPIO_Pin_12


/*--------Tim-Defination--------*/
// TIM1的时钟宏定义
// 底盘左电机：
//     PWM输入（调速）
#define LEFTWHEEL_TIM_OUT                 TIM8
#define LEFTWHEEL_TIM_OUT_APBxClock_FUN   RCC_APB2PeriphClockCmd
#define LEFTWHEEL_TIM_OUT_CLK             RCC_APB2Periph_TIM8
//     PWM输出（反馈）
#define LEFTWHEEL_TIM_IN                  TIM3
#define LEFTWHEEL_TIM_IN_APBxClock_FUN    RCC_APB1PeriphClockCmd
#define LEFTWHEEL_TIM_IN_CLK              RCC_APB1Periph_TIM3
#define LEFTWHEEL_TIM_IN_PWM_CHANNEL      TIM_Channel_1

// 底盘右电机：
//     PWM输入
#define RIGHTWHEEL_TIM_OUT                TIM8
#define RIGHTWHEEL_TIM_OUT_APBxClock_FUN  RCC_APB2PeriphClockCmd
#define RIGHTWHEEL_TIM_OUT_CLK            RCC_APB2Periph_TIM8
//     PWM输出
#define RIGHTWHEEL_TIM_IN                 TIM4
#define RIGHTWHEEL_TIM_IN_APBxClock_FUN   RCC_APB1PeriphClockCmd
#define RIGHTWHEEL_TIM_IN_CLK             RCC_APB1Periph_TIM4
#define RIGHTWHEEL_TIM_IN_PWM_CHANNEL     TIM_Channel_1

// 履带电机
//     PWM输入
#define TRACK_TIM_OUT                     TIM1
#define TRACK_TIM_OUT_APBxClock_FUN       RCC_APB2PeriphClockCmd
#define TRACK_TIM_OUT_CLK                 RCC_APB2Periph_TIM1

// 滑轨电机
//     PWM输入
#define SLIDE_TIM_OUT                     TIM1
#define SLIDE_TIM_OUT_APBxClock_FUN       RCC_APB2PeriphClockCmd
#define SLIDE_TIM_OUT_CLK                 RCC_APB2Periph_TIM1

//#define ADVANCE_TIM  TIM1
//#define ADVANCE_TIM_APBxClock_FUN  RCC_APB2PeriphClockCmd
//#define ADVANCE_TIM_CLK  RCC_APB2Periph_TIM1


// PWM 信号设置
#define ADVANCE_TIM_PERIOD  (256-1)                   // 周期
#define ADVANCE_TIM_PSC     (1-1)                     // 预分频
#define ADVANCE_TIM_PULSE   100                       // 占空比

// 中断相关宏定义
#define LEFTWHEEL_TIM_IN_IRQ      TIM3_IRQn           // 左轮中断源
#define RIGHTWHEEL_TIM_IN_IRQ     TIM4_IRQn           // 右轮中断源


/*--------Register-Defination--------*/
#define LEFTWHEEL_PWM_OUT    &(LEFTWHEEL_TIM_OUT->CCR1)      // 通道比较寄存器，应与选择的输出通道一致
#define RIGHTWHEEL_PWM_OUT   &(RIGHTWHEEL_TIM_OUT->CCR3)
#define TRACK_PWM            &(TRACK_TIM_OUT->CCR1)
#define SLIDE_PWM            &(SLIDE_TIM_OUT->CCR4)


static void ADVANCE_TIM_GPIO_Config(void);
static void ADVANCE_TIM_Mode_Config(void);
static void ADVANCE_TIM_NVIC_Config(void);
void ADVANCE_TIM_Init();                             // TIM 总初始化

void Set_Speed(__IO uint16_t * ccr, uint32_t speed);            // 修改 PWM 占空比


#endif

