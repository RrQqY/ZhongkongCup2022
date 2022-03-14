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

#define Delay(time)   SysTick_Delay_ms(time);    // �ȴ�����
#define SevenTotal(a, b, c, d, e, f, g)   a*1000000 + b*100000 + c*10000 + d*1000 + e*100 + f*10 + g    // ����·��Ϣһ������ĺ궨�庯��


extern __IO float DutyCycle_Left;        // ���������ֵ�ռ�ձȺ�Ƶ�ʵ�ȫ�ֱ���
extern __IO float Frequency_Left;
extern __IO float DutyCycle_Right;
extern __IO float Frequency_Right;

extern short Accel[3];                   // �����Ǽ��ٶȡ��Ǽ��ٶȡ��¶ȵ�ȫ�ֱ���
extern short Gyro[3];
extern float Temp;
extern float gyroX, gyroY, gyroZ;        // ������ٶȵ�ȫ�ֱ���
extern short Angle[3];                   // �����ǽǶȵ�ȫ�ֱ���
extern float integralX, integralY, integralZ;             // �ۼ�ƫ��
extern int g_GetZeroOffset;              // ��ƫ
extern int task_readdata_finish;         // ��ȡMPU6050���ݱ�־

static void LCD_Test(void);	
extern void LCD_Printn(int line, uint32_t num);            // LCD ����ʾ����
extern void LCD_Prints(int line, char dispBuff[]);         // LCD ����ʾӢ���ַ���
extern uint16_t lcdid;

#endif
