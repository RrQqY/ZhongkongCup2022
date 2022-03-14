#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include "stm32f10x.h"

#include "GPIO.h"
#include "systick.h"
#include "AdvanceTim.h"
#include "usart.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./flash/bsp_spi_flash.h"
#include "Move.h"
#include "I2C.h"
#include "mpu6050.h"

#define Delay(time)   SysTick_Delay_ms(time);    // 等待毫秒
#define SevenTotal(a, b, c, d, e, f, g)   a*1000000 + b*100000 + c*10000 + d*1000 + e*100 + f*10 + g    // 将七路信息一起输出的宏定义函数


extern __IO float DutyCycle_Left;        // 底盘左右轮的占空比和频率的全局变量
extern __IO float Frequency_Left;
extern __IO float DutyCycle_Right;
extern __IO float Frequency_Right;

extern short Accel[3];                   // 陀螺仪加速度、角加速度、温度的全局变量
extern short Gyro[3];
extern float Temp;
extern float gyroX, gyroY, gyroZ;        // 三轴角速度的全局变量
extern short Angle[3];                   // 陀螺仪角度的全局变量
extern float integralX, integralY, integralZ;             // 累计偏角
extern int g_GetZeroOffset;              // 零偏
extern int task_readdata_finish;         // 读取MPU6050数据标志

static void LCD_Test(void);	
extern void LCD_Printn(int line, uint32_t num);            // LCD 屏显示数字
extern void LCD_Prints(int line, char dispBuff[]);         // LCD 屏显示英文字符串
extern uint16_t lcdid;

#endif
