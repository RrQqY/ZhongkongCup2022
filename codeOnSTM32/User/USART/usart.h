#ifndef __USART_H
#define	__USART_H

#include <string.h>
#include "stm32f10x.h"
#include "GPIO.h"

// ���ں궨�壨ע�⣺��ͬ�Ĵ��ڹ��ص����ߺ�IO��һ����
// ����1-USART1���������
#define  DEBUG_USARTx                   USART1
#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
#define  DEBUG_USART_BAUDRATE           9600

// USART1 GPIO ���ź궨��
#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

// USART1 �жϺ궨��
#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


// ����3-USART3��NANO����ͨ��
#define  NANO_USARTx                   USART3
#define  NANO_USART_CLK                RCC_APB1Periph_USART3
#define  NANO_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  NANO_USART_BAUDRATE           115200

//// USART3 GPIO ���ź궨��
#define  NANO_USART_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  NANO_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  NANO_USART_TX_GPIO_PORT       GPIOB   
#define  NANO_USART_TX_GPIO_PIN        GPIO_Pin_10
#define  NANO_USART_RX_GPIO_PORT       GPIOB
#define  NANO_USART_RX_GPIO_PIN        GPIO_Pin_11

// USART3 �жϺ궨��
#define  NANO_USART_IRQ                USART3_IRQn
#define  NANO_USART_IRQHandler         USART3_IRQHandler


// ����5-USART2��IMUͨ��
#define  IMU_USARTx                   UART5
#define  IMU_USART_CLK                RCC_APB1Periph_UART5
#define  IMU_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  IMU_USART_BAUDRATE           9600

// USART5 GPIO ���ź궨��
#define  IMU_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
#define  IMU_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  IMU_USART_TX_GPIO_PORT       GPIOC   
#define  IMU_USART_TX_GPIO_PIN        GPIO_Pin_12
#define  IMU_USART_RX_GPIO_PORT       GPIOD
#define  IMU_USART_RX_GPIO_PIN        GPIO_Pin_2

// USART5 �жϺ궨��
#define  IMU_USART_IRQ                UART5_IRQn
#define  IMU_USART_IRQHandler         UART5_IRQHandler


// ����4-UART4
//#define  DEBUG_USARTx                   UART4
//#define  DEBUG_USART_CLK                RCC_APB1Periph_UART4
//#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
//#define  DEBUG_USART_BAUDRATE           115200

//// USART4 GPIO ���ź궨��
//#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC)
//#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART_TX_GPIO_PORT       GPIOC   
//#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_10
//#define  DEBUG_USART_RX_GPIO_PORT       GPIOC
//#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

// USART4 �жϺ궨��
//#define  DEBUG_USART_IRQ                UART4_IRQn
//#define  DEBUG_USART_IRQHandler         UART4_IRQHandler


// ����5-UART5
//#define  DEBUG_USARTx                   UART5
//#define  DEBUG_USART_CLK                RCC_APB1Periph_UART5
//#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
//#define  DEBUG_USART_BAUDRATE           115200

//// USART5 GPIO ���ź궨��
//#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
//#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART_TX_GPIO_PORT       GPIOC   
//#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_12
//#define  DEBUG_USART_RX_GPIO_PORT       GPIOD
//#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_2

// USART5 �жϺ궨��
//#define  DEBUG_USART_IRQ                UART5_IRQn
//#define  DEBUG_USART_IRQHandler         UART5_IRQHandler


// �������ָ��궨��
#define FRAME_HEADER             0x55     //֡ͷ
#define CMD_SERVO_MOVE           0x03     //����ƶ�ָ��
#define CMD_ACTION_GROUP_RUN     0x06     //���ж�����ָ��
#define CMD_ACTION_GROUP_STOP    0x07     //ֹͣ������ָ��
#define CMD_ACTION_GROUP_SPEED   0x0B     //���ö����������ٶ�
#define CMD_GET_BATTERY_VOLTAGE  0x0F     //��ȡ��ص�ѹָ��


#define GET_LOW_BYTE(A) ((uint8_t)(A))            //�꺯�� ���A�ĵͰ�λ
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))    //�꺯�� ���A�ĸ߰�λ



// �������������װ
/* 1��2��3���ϲ��������      1��չ��750���۵�2500��2��չ��800�� �۵���2600��4��չ��650�� �۵���2600
	 4��5��6���²��������      3��չ��2200���۵���450��5��չ��2400���۵���600��6��չ��2350���۵���400
	 7���ϲ�۴���            7�� ̧��1150������1550
	 13��14��װ�б�����         13���Ϸ�1550���·�550��
															14���Ϸ�650�� �·�1650��
	 15����������             15���Ϸ�1450���·���600
	*/
#define MoveSrv1(up) up>0 ? MoveServo(1, 500, 750)  : MoveServo(1, 500, 2500)     // �ϲ��������
#define MoveSrv2(up) up>0 ? MoveServo(2, 500, 800)  : MoveServo(2, 500, 2600)
#define MoveSrv3(up) up>0 ? MoveServo(3, 500, 2200) : MoveServo(3, 500, 450)
#define MoveSrv4(up) up>0 ? MoveServo(4, 500, 650)  : MoveServo(4, 500, 2600)     // �²��������
#define MoveSrv5(up) up>0 ? MoveServo(5, 500, 600) : MoveServo(5, 500, 2400)
#define MoveSrv6(up) up>0 ? MoveServo(6, 500, 2350) : MoveServo(6, 500, 400)

#define MoveSrv7(up) up>0  ? MoveServo(7, 500, 950) : MoveServo(7, 500, 1550)    // �ϲ�۴���
#define MoveSrv15(up) up>0 ? MoveServo(15, 500, 1200) : MoveServo(15, 500, 500)   // ��������

#define MoveSrv13(up) up>0 ? MoveServo(13, 500, 1550) : MoveServo(13, 500, 550)   // ��װ�б�
#define MoveSrv14(up) up>0 ? MoveServo(14, 500, 650)  : MoveServo(14, 500, 1650)  // ��װ�б�


void USART_Config(void);                                                      // USART ����� GPIO ����
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);                    // ����һ���ֽ�
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num); // ����8λ������
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);                   // �����ַ���
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);               // ����һ��16������

void UartWriteBuf(uint8_t *buf, uint8_t len);                                 // �������ư�д��ָ�
void MoveServo(uint8_t servoID, uint16_t Time, uint16_t Position);            // ���Ƶ������ת��
void MoveServos(uint8_t Num, uint16_t Time, ...);                             // ���ƶ�����ת��
void NanoStart();                                                             // ��nano������ʼ�ź�
void IMU_Put_Char(unsigned char DataToSend);
void IMU_sendcmd(char cmd[]);
void IMU_Put_String(unsigned char *Str);
void CopeSerial2Data(unsigned char ucData);
void *memcpy(void *str1, const void *str2, size_t n);
void NanoCatch();

#endif
