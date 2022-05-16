#ifndef _I2C_H
#define _I2C_H

#include <inttypes.h>
#include "main.h"

// 定义I2C总线连接的GPIO端口
#define GPIO_PORT_I2C	GPIOB			              // GPIO端口
#define RCC_I2C_PORT 	RCC_APB2Periph_GPIOB		// GPIO端口时钟
#define I2C_SCL_PIN		GPIO_Pin_6			        // 连接到SCL时钟线的GPIO
#define I2C_SDA_PIN		GPIO_Pin_7			        // 连接到SDA数据线的GPIO

#define I2C_WR	0		   // 写控制bit
#define I2C_RD	1		   // 读控制bit

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
