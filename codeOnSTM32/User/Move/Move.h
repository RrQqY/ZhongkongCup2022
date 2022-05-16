#ifndef __MOVE_H
#define __MOVE_H

#include "stm32f10x.h"

#include "main.h"

#define SevenTotal(a, b, c, d, e, f, g)   a*1000000 + b*100000 + c*10000 + d*1000 + e*100 + f*10 + g    // ����·��Ϣһ������ĺ궨�庯��


// �ߵ͵�ƽ�궨��
#define high  0      // ����1������0
#define low   1

// ���ת�ٺ궨��
#define LeftTruningSpeed    70            // ����ת���ٶ�
#define RightTruningSpeed   70            // ����ת���ٶ�
#define MPUTurningSpeed     65            // MPUת���ٶ�
#define FowardSpeed         78            // ֱ���ٶ�
#define FowardSpeed_Right   78            // ����ֱ���ٶ�
#define FowardSpeed_Left    85            // ����ֱ���ٶ�
#define PreSlow             40            // ������ǰ��ǰ����

// PID�����궨��                      
#define KP    10
#define KI    1
#define KD    0

// �������Ҷ�PID�����궨��
#define KP_grab   10
#define KI_grab   1
#define KD_grab   0


static int correct_count;            // У׼����


void PID(void);                      // PID Ѳ��
void Forward(int Line_Count);        // Ѳ��ֱ�� n ����
void Forward_Front(int Line_Count);  // Ѳ��ֱ�� n ���ߣ�ǰ��·���ߣ�
void Right(void);                    // ��ת
void Left(void);                     // ��ת
//void Stop(void);                   // ֹͣ
void Stop_Forward(void);
void Stop_Back(void);
void Stop_Left(void);
void Stop_Right(void);
void Right_MPU(int angle);           // ����MPU6050��ת
void Left_MPU(int angle);            // ����MPU6050��ת
void TrunTo_MPU(int angle);          // ����MPU6050ת���ض��Ƕ�
void SlideOut(void);                 // �������
void SlideIn(void);                  // �ջػ���
void TrackMove(void);                // �Ĵ�ת��
void TrackStop(void);                // �Ĵ�ֹͣ
void Catch(void);                    // ���һ��ץȡ
void Back(int Line_Count);           // ����Ѳ��ֱ�� n ����
void PIDBack(void);                  // ����PID Ѳ��


#endif
