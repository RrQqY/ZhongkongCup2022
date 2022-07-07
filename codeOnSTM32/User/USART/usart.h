#ifndef __USART_H
#define	__USART_H

#include <string.h>
#include "stm32f10x.h"
#include "GPIO.h"

// 串口宏定义（注意：不同的串口挂载的总线和IO不一样）
// 串口1-USART1，舵机控制
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           9600

// USART1 GPIO 引脚宏定义
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

// USART1 中断宏定义
#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


// 串口3-USART3，NANO串口通信
#define  NANO_USARTx                   USART3
#define  NANO_USART_CLK                RCC_APB1Periph_USART3
#define  NANO_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  NANO_USART_BAUDRATE           115200

//// USART3 GPIO 引脚宏定义
#define  NANO_USART_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  NANO_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  NANO_USART_TX_GPIO_PORT       GPIOB   
#define  NANO_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  NANO_USART_RX_GPIO_PORT       GPIOB
#define  NANO_USART_RX_GPIO_PIN        GPIO_Pin_11

// USART3 中断宏定义
#define  NANO_USART_IRQ                USART3_IRQn
#define  NANO_USART_IRQHandler         USART3_IRQHandler


// 串口5-USART2，IMU通信
#define  IMU_USARTx                   UART5
#define  IMU_USART_CLK                RCC_APB1Periph_UART5
#define  IMU_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  IMU_USART_BAUDRATE           9600

// USART5 GPIO 引脚宏定义
#define  IMU_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
#define  IMU_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  IMU_USART_TX_GPIO_PORT       GPIOC   
#define  IMU_USART_TX_GPIO_PIN        GPIO_Pin_12
#define  IMU_USART_RX_GPIO_PORT       GPIOD
#define  IMU_USART_RX_GPIO_PIN        GPIO_Pin_2

// USART5 中断宏定义
#define  IMU_USART_IRQ                UART5_IRQn
#define  IMU_USART_IRQHandler         UART5_IRQHandler


// 串口4-UART4
//#define  DEBUG_USARTx                   UART4
//#define  DEBUG_USART_CLK                RCC_APB1Periph_UART4
//#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
//#define  DEBUG_USART_BAUDRATE           115200

//// USART4 GPIO 引脚宏定义
//#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC)
//#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART_TX_GPIO_PORT       GPIOC   
//#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_10
//#define  DEBUG_USART_RX_GPIO_PORT       GPIOC
//#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

// USART4 中断宏定义
//#define  DEBUG_USART_IRQ                UART4_IRQn
//#define  DEBUG_USART_IRQHandler         UART4_IRQHandler


// 串口5-UART5
//#define  DEBUG_USARTx                   UART5
//#define  DEBUG_USART_CLK                RCC_APB1Periph_UART5
//#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
//#define  DEBUG_USART_BAUDRATE           115200

//// USART5 GPIO 引脚宏定义
//#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
//#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART_TX_GPIO_PORT       GPIOC   
//#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_12
//#define  DEBUG_USART_RX_GPIO_PORT       GPIOD
//#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_2

// USART5 中断宏定义
//#define  DEBUG_USART_IRQ                UART5_IRQn
//#define  DEBUG_USART_IRQHandler         UART5_IRQHandler


// 舵机控制指令宏定义
#define FRAME_HEADER             0x55     //帧头
#define CMD_SERVO_MOVE           0x03     //舵机移动指令
#define CMD_ACTION_GROUP_RUN     0x06     //运行动作组指令
#define CMD_ACTION_GROUP_STOP    0x07     //停止动作组指令
#define CMD_ACTION_GROUP_SPEED   0x0B     //设置动作组运行速度
#define CMD_GET_BATTERY_VOLTAGE  0x0F     //获取电池电压指令


#define GET_LOW_BYTE(A) ((uint8_t)(A))            //宏函数 获得A的低八位
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))    //宏函数 获得A的高八位



// 舵机驱动函数封装
/* 1、2、3：上层臂右左中      1：展开750，折叠2500，2：展开800， 折叠：2600，4：展开650， 折叠：2600
	 4、5、6：下层臂右左中      3：展开2200，折叠：450，5：展开2400，折叠：600，6：展开2350，折叠：400
	 7：上层臂大舵机            7： 抬起1150，放下1550
	 13、14：装夹臂左右         13：上翻1550，下翻550；
															14：上翻650， 下翻1650；
	 15：翻斗大舵机             15：上翻1450，下翻：600
	*/
#define MoveSrv1(up) up>0 ? MoveServo(1, 500, 750)  : MoveServo(1, 500, 2500)     // 上层臂右左中
#define MoveSrv2(up) up>0 ? MoveServo(2, 500, 800)  : MoveServo(2, 500, 2600)
#define MoveSrv3(up) up>0 ? MoveServo(3, 500, 2200) : MoveServo(3, 500, 450)
#define MoveSrv4(up) up>0 ? MoveServo(4, 500, 650)  : MoveServo(4, 500, 2600)     // 下层臂右左中
#define MoveSrv5(up) up>0 ? MoveServo(5, 500, 600) : MoveServo(5, 500, 2400)
#define MoveSrv6(up) up>0 ? MoveServo(6, 500, 2350) : MoveServo(6, 500, 400)

#define MoveSrv7(up) up>0  ? MoveServo(7, 500, 950) : MoveServo(7, 500, 1550)    // 上层臂大舵机
#define MoveSrv15(up) up>0 ? MoveServo(15, 500, 1200) : MoveServo(15, 500, 500)   // 翻斗大舵机

#define MoveSrv13(up) up>0 ? MoveServo(13, 500, 1550) : MoveServo(13, 500, 550)   // 左装夹臂
#define MoveSrv14(up) up>0 ? MoveServo(14, 500, 650)  : MoveServo(14, 500, 1650)  // 右装夹臂


void USART_Config(void);                                                      // USART 及相关 GPIO 配置
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);                    // 发送一个字节
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num); // 发送8位的数组
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);                   // 发送字符串
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);               // 发送一个16进制数

void UartWriteBuf(uint8_t *buf, uint8_t len);                                 // 向舵机控制板写入指令集
void MoveServo(uint8_t servoID, uint16_t Time, uint16_t Position);            // 控制单个舵机转动
void MoveServos(uint8_t Num, uint16_t Time, ...);                             // 控制多个舵机转动
void NanoStart();                                                             // 向nano发送起始信号
void IMU_Put_Char(unsigned char DataToSend);
void IMU_sendcmd(char cmd[]);
void IMU_Put_String(unsigned char *Str);
void CopeSerial2Data(unsigned char ucData);
void *memcpy(void *str1, const void *str2, size_t n);
void NanoCatch();

#endif
