#ifndef __MOVE_H
#define __MOVE_H

#include "stm32f10x.h"

#include "main.h"

#define SevenTotal(a, b, c, d, e, f, g)   a*1000000 + b*100000 + c*10000 + d*1000 + e*100 + f*10 + g    // 将七路信息一起输出的宏定义函数


// 高低电平宏定义
#define high  0      // 黑线1，白线0
#define low   1

// 电机转速宏定义
#define LeftTruningSpeed    70            // 左轮转向速度
#define RightTruningSpeed   70            // 右轮转向速度
#define MPUTurningSpeed     65            // MPU转向速度
#define FowardSpeed         78            // 直行速度
#define FowardSpeed_Right   78            // 右轮直行速度
#define FowardSpeed_Left    85            // 左轮直行速度
#define PreSlow             40            // 数到线前提前减速

// PID参数宏定义                      
#define KP    10
#define KI    1
#define KD    0

// 侧面三灰度PID参数宏定义
#define KP_grab   10
#define KI_grab   1
#define KD_grab   0


static int correct_count;            // 校准次数


void PID(void);                      // PID 巡线
void Forward(int Line_Count);        // 巡线直行 n 根线
void Forward_Front(int Line_Count);  // 巡线直行 n 根线（前七路数线）
void Right(void);                    // 右转
void Left(void);                     // 左转
//void Stop(void);                   // 停止
void Stop_Forward(void);
void Stop_Back(void);
void Stop_Left(void);
void Stop_Right(void);
void Right_MPU(int angle);           // 利用MPU6050右转
void Left_MPU(int angle);            // 利用MPU6050左转
void TrunTo_MPU(int angle);          // 利用MPU6050转到特定角度
void SlideOut(void);                 // 伸出滑轨
void SlideIn(void);                  // 收回滑轨
void TrackMove(void);                // 履带转动
void TrackStop(void);                // 履带停止
void Catch(void);                    // 完成一次抓取
void Back(int Line_Count);           // 后退巡线直行 n 根线
void PIDBack(void);                  // 后退PID 巡线


#endif
