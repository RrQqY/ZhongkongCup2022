#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

/*--------GPIO-Defination--------*/
// 底盘左电机转向
#define LEFTWHEEL_GPIO_PIN        GPIO_Pin_10
#define LEFTWHEEL_GPIO_PORT       GPIOC
#define LEFTWHEEL_GPIO_CLK        RCC_APB2Periph_GPIOC

// 底盘右电机转向
#define RIGHTWHEEL_GPIO_PIN       GPIO_Pin_7
#define RIGHTWHEEL_GPIO_PORT      GPIOD
#define RIGHTWHEEL_GPIO_CLK       RCC_APB2Periph_GPIOD

//// 履带电机转向
//#define TRACK_GPIO_PIN            GPIO_Pin_8
//#define TRACK_GPIO_PORT           GPIOA
//#define TRACK_GPIO_CLK            RCC_APB2Periph_GPIOA

// 滑轨电机转向
#define SLIDE_GPIO_PIN            GPIO_Pin_14
#define SLIDE_GPIO_PORT           GPIOG
#define SLIDE_GPIO_CLK            RCC_APB2Periph_GPIOG

// 启动按钮（KEY1）
#define START_GPIO_PIN            GPIO_Pin_0
#define START_GPIO_PORT           GPIOA
#define START_GPIO_CLK            RCC_APB2Periph_GPIOA

// 启动按钮（KEY2）
#define FAKE_GPIO_PIN            GPIO_Pin_13
#define FAKE_GPIO_PORT           GPIOC
#define FAKE_GPIO_CLK            RCC_APB2Periph_GPIOC

// 红灯
#define RED_GPIO_PIN              GPIO_Pin_5
#define RED_GPIO_PORT             GPIOB
#define RED_GPIO_CLK              RCC_APB2Periph_GPIOB

// 绿灯
#define GREEN_GPIO_PIN            GPIO_Pin_0
#define GREEN_GPIO_PORT           GPIOB
#define GREEN_GPIO_CLK            RCC_APB2Periph_GPIOB

// 蓝灯
#define BLUE_GPIO_PIN             GPIO_Pin_1
#define BLUE_GPIO_PORT            GPIOB
#define BLUE_GPIO_CLK             RCC_APB2Periph_GPIOB

// 前七路
//     1
#define FRONTSEVEN1_GPIO_PIN      GPIO_Pin_1
#define FRONTSEVEN1_GPIO_PORT     GPIOE
#define FRONTSEVEN1_GPIO_CLK      RCC_APB2Periph_GPIOE
//     2
#define FRONTSEVEN2_GPIO_PIN      GPIO_Pin_11
#define FRONTSEVEN2_GPIO_PORT     GPIOF
#define FRONTSEVEN2_GPIO_CLK      RCC_APB2Periph_GPIOF
//     3
#define FRONTSEVEN3_GPIO_PIN      GPIO_Pin_10
#define FRONTSEVEN3_GPIO_PORT     GPIOG
#define FRONTSEVEN3_GPIO_CLK      RCC_APB2Periph_GPIOG
//     4
#define FRONTSEVEN4_GPIO_PIN      GPIO_Pin_12
#define FRONTSEVEN4_GPIO_PORT     GPIOA
#define FRONTSEVEN4_GPIO_CLK      RCC_APB2Periph_GPIOA
//     5
#define FRONTSEVEN5_GPIO_PIN      GPIO_Pin_7
#define FRONTSEVEN5_GPIO_PORT     GPIOF
#define FRONTSEVEN5_GPIO_CLK      RCC_APB2Periph_GPIOF
//     6
#define FRONTSEVEN6_GPIO_PIN      GPIO_Pin_6
#define FRONTSEVEN6_GPIO_PORT     GPIOF
#define FRONTSEVEN6_GPIO_CLK      RCC_APB2Periph_GPIOF
//     7
#define FRONTSEVEN7_GPIO_PIN      GPIO_Pin_1
#define FRONTSEVEN7_GPIO_PORT     GPIOC
#define FRONTSEVEN7_GPIO_CLK      RCC_APB2Periph_GPIOC

// 后七路
//     1
#define BACKSEVEN1_GPIO_PIN       GPIO_Pin_0
#define BACKSEVEN1_GPIO_PORT      GPIOF
#define BACKSEVEN1_GPIO_CLK       RCC_APB2Periph_GPIOF
//     2
#define BACKSEVEN2_GPIO_PIN       GPIO_Pin_2
#define BACKSEVEN2_GPIO_PORT      GPIOF
#define BACKSEVEN2_GPIO_CLK       RCC_APB2Periph_GPIOF
//     3
#define BACKSEVEN3_GPIO_PIN       GPIO_Pin_4
#define BACKSEVEN3_GPIO_PORT      GPIOF
#define BACKSEVEN3_GPIO_CLK       RCC_APB2Periph_GPIOF
//     4
#define BACKSEVEN4_GPIO_PIN       GPIO_Pin_12
#define BACKSEVEN4_GPIO_PORT      GPIOF
#define BACKSEVEN4_GPIO_CLK       RCC_APB2Periph_GPIOF
//     5
#define BACKSEVEN5_GPIO_PIN       GPIO_Pin_14
#define BACKSEVEN5_GPIO_PORT      GPIOF
#define BACKSEVEN5_GPIO_CLK       RCC_APB2Periph_GPIOF
//     6
#define BACKSEVEN6_GPIO_PIN       GPIO_Pin_13
#define BACKSEVEN6_GPIO_PORT      GPIOE
#define BACKSEVEN6_GPIO_CLK       RCC_APB2Periph_GPIOG
//     7
#define BACKSEVEN7_GPIO_PIN       GPIO_Pin_2
#define BACKSEVEN7_GPIO_PORT      GPIOG
#define BACKSEVEN7_GPIO_CLK       RCC_APB2Periph_GPIOG

// 左七路
//     1
#define LEFTSEVEN1_GPIO_PIN       GPIO_Pin_13
#define LEFTSEVEN1_GPIO_PORT      GPIOB
#define LEFTSEVEN1_GPIO_CLK       RCC_APB2Periph_GPIOB
//     2
#define LEFTSEVEN2_GPIO_PIN       GPIO_Pin_15
#define LEFTSEVEN2_GPIO_PORT      GPIOB
#define LEFTSEVEN2_GPIO_CLK       RCC_APB2Periph_GPIOB
//     3
#define LEFTSEVEN3_GPIO_PIN       GPIO_Pin_15
#define LEFTSEVEN3_GPIO_PORT      GPIOG
#define LEFTSEVEN3_GPIO_CLK       RCC_APB2Periph_GPIOG
//     4
#define LEFTSEVEN4_GPIO_PIN       GPIO_Pin_9
#define LEFTSEVEN4_GPIO_PORT      GPIOB
#define LEFTSEVEN4_GPIO_CLK       RCC_APB2Periph_GPIOB
//     5
#define LEFTSEVEN5_GPIO_PIN       GPIO_Pin_6
#define LEFTSEVEN5_GPIO_PORT      GPIOD
#define LEFTSEVEN5_GPIO_CLK       RCC_APB2Periph_GPIOD
//     6
#define LEFTSEVEN6_GPIO_PIN       GPIO_Pin_3
#define LEFTSEVEN6_GPIO_PORT      GPIOD
#define LEFTSEVEN6_GPIO_CLK       RCC_APB2Periph_GPIOD
//     7
#define LEFTSEVEN7_GPIO_PIN       GPIO_Pin_8
#define LEFTSEVEN7_GPIO_PORT      GPIOB
#define LEFTSEVEN7_GPIO_CLK       RCC_APB2Periph_GPIOB

// 右七路
//     1
#define RIGHTSEVEN1_GPIO_PIN      GPIO_Pin_9
#define RIGHTSEVEN1_GPIO_PORT     GPIOE
#define RIGHTSEVEN1_GPIO_CLK      RCC_APB2Periph_GPIOE
//     2
#define RIGHTSEVEN2_GPIO_PIN      GPIO_Pin_7
#define RIGHTSEVEN2_GPIO_PORT     GPIOE
#define RIGHTSEVEN2_GPIO_CLK      RCC_APB2Periph_GPIOE
//     3
#define RIGHTSEVEN3_GPIO_PIN      GPIO_Pin_0
#define RIGHTSEVEN3_GPIO_PORT     GPIOD
#define RIGHTSEVEN3_GPIO_CLK      RCC_APB2Periph_GPIOD
//     4
#define RIGHTSEVEN4_GPIO_PIN      GPIO_Pin_14
#define RIGHTSEVEN4_GPIO_PORT     GPIOD
#define RIGHTSEVEN4_GPIO_CLK      RCC_APB2Periph_GPIOD
//     5
#define RIGHTSEVEN5_GPIO_PIN      GPIO_Pin_13
#define RIGHTSEVEN5_GPIO_PORT     GPIOD
#define RIGHTSEVEN5_GPIO_CLK      RCC_APB2Periph_GPIOD
//     6
#define RIGHTSEVEN6_GPIO_PIN      GPIO_Pin_11
#define RIGHTSEVEN6_GPIO_PORT     GPIOD
#define RIGHTSEVEN6_GPIO_CLK      RCC_APB2Periph_GPIOD
//     7
#define RIGHTSEVEN7_GPIO_PIN      GPIO_Pin_4
#define RIGHTSEVEN7_GPIO_PORT     GPIOG
#define RIGHTSEVEN7_GPIO_CLK      RCC_APB2Periph_GPIOG

// 侧三路
//     左
#define GRABTHREE1_GPIO_PIN       GPIO_Pin_9
#define GRABTHREE1_GPIO_PORT      GPIOD
#define GRABTHREE1_GPIO_CLK       RCC_APB2Periph_GPIOD
//     中
#define GRABTHREE2_GPIO_PIN       GPIO_Pin_12
#define GRABTHREE2_GPIO_PORT      GPIOE
#define GRABTHREE2_GPIO_CLK       RCC_APB2Periph_GPIOE
//     右
#define GRABTHREE3_GPIO_PIN       GPIO_Pin_14
#define GRABTHREE3_GPIO_PORT      GPIOE
#define GRABTHREE3_GPIO_CLK       RCC_APB2Periph_GPIOE

// NANO
//     1
#define NANO1_GPIO_PIN            GPIO_Pin_4
#define NANO1_GPIO_PORT           GPIOA
#define NANO1_GPIO_CLK            RCC_APB2Periph_GPIOA
//     2
#define NANO2_GPIO_PIN            GPIO_Pin_5
#define NANO2_GPIO_PORT           GPIOA
#define NANO2_GPIO_CLK            RCC_APB2Periph_GPIOA
//     3
#define NANO3_GPIO_PIN            GPIO_Pin_4
#define NANO3_GPIO_PORT           GPIOC
#define NANO3_GPIO_CLK            RCC_APB2Periph_GPIOC
//     4
#define NANO4_GPIO_PIN            GPIO_Pin_10
#define NANO4_GPIO_PORT           GPIOD
#define NANO4_GPIO_CLK            RCC_APB2Periph_GPIOD
//     5
#define NANO5_GPIO_PIN            GPIO_Pin_8
#define NANO5_GPIO_PORT           GPIOD
#define NANO5_GPIO_CLK            RCC_APB2Periph_GPIOD
//     6
#define NANO6_GPIO_PIN            GPIO_Pin_8
#define NANO6_GPIO_PORT           GPIOF
#define NANO6_GPIO_CLK            RCC_APB2Periph_GPIOF


// 七路信号读取函数宏定义
#define front    1 
#define back     2
#define left     3
#define right    4


/*--------Function--------*/
//// GPIO_High
//#define GPIO_High  GPIO_ResetBits(GPIO_PORT, GPIO_PIN)

//// GPIO_Low
//#define GPIO_Low  GPIO_SetBits(GPIO_PORT, GPIO_PIN)

void GPIO_Config(void);                                // GPIO 引脚初始化
void GPIO_High(GPIO_TypeDef * port, uint16_t pin);     // GPIO 引脚输出高电平
void GPIO_Low(GPIO_TypeDef * port, uint16_t pin);      // GPIO 引脚输出高电平
int  GPIO_Read(GPIO_TypeDef * port, uint16_t pin);     // GPIO 引脚读取
int  Seven_Read(int s, int n);                         // 七路信号读取
int  Nano_Read(int n);                                 // NANO信号读取

#endif
