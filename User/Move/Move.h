#ifndef __MOVE_H
#define __MOVE_H

#include "stm32f10x.h"

#include "main.h"

#define SevenTotal(a, b, c, d, e, f, g)   a*1000000 + b*100000 + c*10000 + d*1000 + e*100 + f*10 + g    // ����·��Ϣһ������ĺ궨�庯��


// �ߵ͵�ƽ�궨��
#define high  0      // ����1������0
#define low   1

// ���ת�ٺ궨��
#define LeftTruningSpeed   70             // ����ת���ٶ�
#define RightTruningSpeed  70             // ����ת���ٶ�
#define MPUTurningSpeed    65             // MPUת���ٶ�
#define FowardSpeed   78                  // ֱ���ٶ�
#define PreSlow       48                  // ������ǰ��ǰ����

// PID�����궨                              
#define KP  10
#define KI  2
#define KD  0


void PID(void);                      // PID Ѳ��
void Forward(int Line_Count);        // Ѳ��ֱ�� n ����
void Forward_Front(int Line_Count);
void Right(void);                    // ��ת
void Left(void);                     // ��ת
void Stop(void);                     // ֹͣ
void Right_MPU(int angle);           // ����MPU6050��ת
void Left_MPU(int angle);            // ����MPU6050��ת
void TrunTo_MPU(int angle);          // ����MPU6050ת���ض��Ƕ�
void SlideOut(void);                 // �������
void SlideIn(void);                  // �ջػ���
void TrackMove(void);                // �Ĵ�ת��
void TrackStop(void);                // �Ĵ�ֹͣ
void Catch(void);                    // ���һ��ץȡ
void Back(int Line_Count);
void PIDBack(void);


#endif
