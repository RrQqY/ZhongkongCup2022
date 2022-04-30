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

extern unsigned char TxBuffer[256];
extern unsigned char TxCounter;
extern unsigned char imu_count; 
extern void CopeSerial2Data(unsigned char ucData);

extern int IMU_Data;                     // IMU数据
extern short Accel[3];                   // 陀螺仪加速度、角加速度、温度的全局变量
extern short Gyro[3];
extern float Temp;
extern float gyroX, gyroY, gyroZ;        // 三轴角速度的全局变量
extern short Angle[3];                   // 陀螺仪角度的全局变量
extern float integralX, integralY, integralZ;             // 累计偏角
extern int g_GetZeroOffset;              // 零偏
extern int task_readdata_finish;         // 读取MPU6050数据标志
extern int POS[6];                       // 上位机返回抓取位置信息
extern uint8_t Nano_Buff[8];
extern int flag_get;
extern void NanoIOHigh();
static void LCD_Test(void);	
extern void LCD_Printn(int line, uint32_t num);            // LCD 屏显示数字
extern void LCD_Prints(int line, char dispBuff[]);         // LCD 屏显示英文字符串
extern uint16_t lcdid;
extern uint8_t time_now;                                   // 开机到现在的运行时间

extern void Test1();    // 第一次测试


// IMU 宏定义
#define SAVE 			0x00
#define CALSW 		0x01
#define RSW 			0x02
#define RRATE			0x03
#define BAUD 			0x04
#define AXOFFSET	0x05
#define AYOFFSET	0x06
#define AZOFFSET	0x07
#define GXOFFSET	0x08
#define GYOFFSET	0x09
#define GZOFFSET	0x0a
#define HXOFFSET	0x0b
#define HYOFFSET	0x0c
#define HZOFFSET	0x0d
#define D0MODE		0x0e
#define D1MODE		0x0f
#define D2MODE		0x10
#define D3MODE		0x11
#define D0PWMH		0x12
#define D1PWMH		0x13
#define D2PWMH		0x14
#define D3PWMH		0x15
#define D0PWMT		0x16
#define D1PWMT		0x17
#define D2PWMT		0x18
#define D3PWMT		0x19
#define IICADDR		0x1a
#define LEDOFF 		0x1b
#define GPSBAUD		0x1c

#define YYMM				0x30
#define DDHH				0x31
#define MMSS				0x32
#define MS					0x33
#define AX					0x34
#define AY					0x35
#define AZ					0x36
#define GX					0x37
#define GY					0x38
#define GZ					0x39
#define HX					0x3a
#define HY					0x3b
#define HZ					0x3c			
#define Roll				0x3d
#define Pitch				0x3e
#define Yaw					0x3f
#define TEMP				0x40
#define D0Status		0x41
#define D1Status		0x42
#define D2Status		0x43
#define D3Status		0x44
#define PressureL		0x45
#define PressureH		0x46
#define HeightL			0x47
#define HeightH			0x48
#define LonL				0x49
#define LonH				0x4a
#define LatL				0x4b
#define LatH				0x4c
#define GPSHeight   0x4d
#define GPSYAW      0x4e
#define GPSVL				0x4f
#define GPSVH				0x50
#define q0          0x51
#define q1          0x52
#define q2          0x53
#define q3          0x54
      
#define DIO_MODE_AIN 0
#define DIO_MODE_DIN 1
#define DIO_MODE_DOH 2
#define DIO_MODE_DOL 3
#define DIO_MODE_DOPWM 4
#define DIO_MODE_GPS 5		

struct STime
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc
{
	short a[3];
	short T;
};
struct SGyro
{
	short w[3];
	short T;
};
struct SAngle
{
	short Angle[3];
	short T;
};
struct SMag
{
	short h[3];
	short T;
};

struct SDStatus
{
	short sDStatus[4];
};

struct SPress
{
	long lPressure;
	long lAltitude;
};

struct SLonLat
{
	long lLon;
	long lLat;
};

struct SGPSV
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};
struct SQ
{ short q[4];
};

// IMU 信号类型定义
extern struct STime		stcTime;
extern struct SAcc 		stcAcc;
extern struct SGyro 		stcGyro;
extern struct SAngle 	stcAngle;
extern struct SMag 		stcMag;
extern struct SDStatus stcDStatus;
extern struct SPress 	stcPress;
extern struct SLonLat 	stcLonLat;
extern struct SGPSV 		stcGPSV;
extern struct SQ       stcQ;

#endif
