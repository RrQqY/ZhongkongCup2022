#ifndef _I2C_H
#define _I2C_H

#include <inttypes.h>
#include "main.h"

// ����I2C�������ӵ�GPIO�˿�
#define GPIO_PORT_I2C	GPIOB			              // GPIO�˿�
#define RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		// GPIO�˿�ʱ��
#define I2C_SCL_PIN		GPIO_Pin_6			        // ���ӵ�SCLʱ���ߵ�GPIO
#define I2C_SDA_PIN		GPIO_Pin_7			        // ���ӵ�SDA�����ߵ�GPIO

#define I2C_WR	0		   // д����bit
#define I2C_RD	1		   // ������bit

void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(uint8_t ack);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);
void i2c_GPIO_Config(void);

#endif
