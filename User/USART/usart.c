#include "usart.h"
#include "main.h"
#include <stdarg.h>
#include <string.h>

// 中断控制器 NVIC 配置
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
	// 舵机控制板串口中断初始化
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                   // 嵌套向量中断控制器组选择
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;             // 配置USART为中断源
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;         // 抢断优先
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                // 子优先级
	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   // 使能中断
  NVIC_Init(&NVIC_InitStructure);                                   // 初始化配置NVIC
	
	// nano通信串口中断初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                   // 嵌套向量中断控制器组选择
  NVIC_InitStructure.NVIC_IRQChannel = NANO_USART_IRQ;              // 配置USART为中断源
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;         // 抢断优先
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                // 子优先级
	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   // 使能中断
  NVIC_Init(&NVIC_InitStructure);                                   // 初始化配置NVIC
	
//	// IMU通信串口中断初始化
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                   // 嵌套向量中断控制器组选择
//  NVIC_InitStructure.NVIC_IRQChannel = IMU_USART_IRQ;               // 配置USART为中断源
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;         // 抢断优先
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;                // 子优先级
//	
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   // 使能中断
//  NVIC_Init(&NVIC_InitStructure);                                   // 初始化配置NVIC
}


// USART 及相关 GPIO 配置
void USART_Config(void)
{
	// 配置串口相关的 GPIO
	GPIO_InitTypeDef  GPIO_InitStructure;
	// 舵机控制板 GPIO 配置
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);        // 打开串口GPIO的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);                  // 打开串口外设的时钟

	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                   // 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// nano通信 GPIO 配置
	NANO_USART_GPIO_APBxClkCmd(NANO_USART_GPIO_CLK, ENABLE);        // 打开串口GPIO的时钟
	NANO_USART_APBxClkCmd(NANO_USART_CLK, ENABLE);                  // 打开串口外设的时钟

	GPIO_InitStructure.GPIO_Pin = NANO_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                   // 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(NANO_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = NANO_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_Init(NANO_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
//	// IMU通信 GPIO 配置
//	IMU_USART_GPIO_APBxClkCmd(IMU_USART_GPIO_CLK, ENABLE);        // 打开串口GPIO的时钟
//	IMU_USART_APBxClkCmd(IMU_USART_CLK, ENABLE);                  // 打开串口外设的时钟

//	GPIO_InitStructure.GPIO_Pin = IMU_USART_TX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                   // 将USART Tx的GPIO配置为推挽复用模式
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(IMU_USART_TX_GPIO_PORT, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = IMU_USART_RX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             // 将USART Rx的GPIO配置为浮空输入模式
//	GPIO_Init(IMU_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	// 配置串口的工作参数
	USART_InitTypeDef USART_InitStructure;
	// 舵机控制板串口配置
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;        // 配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       // 配置数据帧字长
	USART_InitStructure.USART_StopBits = USART_StopBits_1;            // 配置停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;              // 配置校验位
	USART_InitStructure.USART_HardwareFlowControl =                   // 配置硬件流控制
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   // 配置工作模式，收发一起
	
	USART_Init(DEBUG_USARTx, &USART_InitStructure);                   // 完成串口的初始化配置
	
	NVIC_Configuration();                                             // 串口中断优先级配置
	
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	            // 使能串口接收中断
	
	USART_Cmd(DEBUG_USARTx, ENABLE);	                                // 使能串口
	
	// nano通信串口配置
	USART_InitStructure.USART_BaudRate = NANO_USART_BAUDRATE;         // 配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       // 配置数据帧字长
	USART_InitStructure.USART_StopBits = USART_StopBits_1;            // 配置停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;              // 配置校验位
	USART_InitStructure.USART_HardwareFlowControl =                   // 配置硬件流控制
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   // 配置工作模式，收发一起
	
	USART_Init(NANO_USARTx, &USART_InitStructure);                    // 完成串口的初始化配置
	
	NVIC_Configuration();                                             // 串口中断优先级配置
	
	USART_ITConfig(NANO_USARTx, USART_IT_RXNE, ENABLE);	              // 使能串口接收中断
	
	USART_Cmd(NANO_USARTx, ENABLE);	                                  // 使能串口
	
//	// IMU通信串口配置
//	USART_InitStructure.USART_BaudRate = IMU_USART_BAUDRATE;          // 配置波特率
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       // 配置数据帧字长
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;            // 配置停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No ;              // 配置校验位
//	USART_InitStructure.USART_HardwareFlowControl =                   // 配置硬件流控制
//	USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   // 配置工作模式，收发一起
//	
//	USART_Init(IMU_USARTx, &USART_InitStructure);                     // 完成串口的初始化配置
//	
//	NVIC_Configuration();                                             // 串口中断优先级配置
//	
//	USART_ITConfig(IMU_USARTx, USART_IT_RXNE, ENABLE);	              // 使能串口接收中断
//	
//	USART_Cmd(IMU_USARTx, ENABLE);	                                  // 使能串口
}


// 发送一个字节
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx,ch);        // 发送一个字节数据到USART
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	  // 等待发送数据寄存器为空
}

// 发送8位的数组
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++){
	    Usart_SendByte(pUSARTx,array[i]);	    // 发送一个字节数据到USART
  
  }
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);         // 等待发送完成
}

// 发送字符串
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET){}        // 等待发送完成
} 

// 发送一个16位数
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);
	GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
	GPIO_High(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
	
	uint8_t temp_h, temp_l;
	
	temp_h = (ch&0XFF00)>>8;        // 取出高八位
	temp_l = ch&0XFF;               // 取出低八位
	
	USART_SendData(pUSARTx,temp_h);	        // 发送高八位
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	USART_SendData(pUSARTx,temp_l);	        // 发送低八位
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


// 向舵机控制板写入指令集。形参1为指令集数组，形参2为指令个数
void UartWriteBuf(uint8_t *buf, uint8_t len)
{
	while (len--) {
		while ((USART1->SR & 0x40) == 0);
		USART_SendData(USART1,*buf++);
	}
}

// IMU写入指令
void IMU_sendcmd(char cmd[])
{
	char i;
	for(i=0; i<5; i++)
		IMU_Put_Char(cmd[i]);
}

void IMU_Put_Char(unsigned char DataToSend)
{
	TxBuffer[imu_count++] = DataToSend;  
  USART_ITConfig(IMU_USARTx, USART_IT_TXE, ENABLE);  
}

void IMU_Put_String(unsigned char *Str)
{
	while(*Str)
	{
		if(*Str=='\r')IMU_Put_Char(0x0d);
			else if(*Str=='\n')IMU_Put_Char(0x0a);
				else IMU_Put_Char(*Str);
		Str++;
	}
}


// 串口2中断调用函数，串口每收到一个数据，调用一次这个函数
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;	  // 将收到的数据存入缓冲区中
	if (ucRxBuffer[0]!=0x55){        // 数据头不对，则重新开始寻找0x55数据头
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}       // 数据不满11个，则返回
	else{
		switch(ucRxBuffer[1]){        // 判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);;break;  // memcpy为编译器自带的内存拷贝函数，将接收缓冲区的字符拷贝到数据结构体里面，实现数据的解析。
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
			case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
			case 0x55:	memcpy(&stcDStatus,&ucRxBuffer[2],8);break;
			case 0x56:	memcpy(&stcPress,&ucRxBuffer[2],8);break;
			case 0x57:	memcpy(&stcLonLat,&ucRxBuffer[2],8);break;
			case 0x58:	memcpy(&stcGPSV,&ucRxBuffer[2],8);break;
			case 0x59:	memcpy(&stcQ,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;                    // 清空缓存区
	}
}


/*-------- 舵机控制函数 --------*/
uint8_t TxBuf[128];  //发送缓存

// 控制单个舵机转动。形参1为转动舵机的ID，形参2为转动的时间，形参3为要转动到的位置
void MoveServo(uint8_t servoID, uint16_t Time, uint16_t Position)
{
	if (servoID > 31 || !(Time > 0)) {  //舵机ID不能打于31,可根据对应控制板修改
		return;
	}
	TxBuf[0] = TxBuf[1] = FRAME_HEADER;    //填充帧头
	TxBuf[2] = 8;                          //数据长度 = 要控制舵机数*3+5，此处 = 1*3+5
	TxBuf[3] = CMD_SERVO_MOVE;             //填充舵机移动指令
	TxBuf[4] = 1;                          //要控制的舵机个数
	TxBuf[5] = GET_LOW_BYTE(Time);         //取得时间的低八位
	TxBuf[6] = GET_HIGH_BYTE(Time);        //取得时间的高八位
	TxBuf[7] = servoID;                    //舵机ID
	TxBuf[8] = GET_LOW_BYTE(Position);     //取得目标位置的低八位
	TxBuf[9] = GET_HIGH_BYTE(Position);    //取得目标位置的高八位

	UartWriteBuf(TxBuf, 10);
}


// 控制多个舵机转动。形参1为舵机个数，形参2为转动的时间，...：舵机ID，转动角度；舵机ID，转动角度...
void MoveServos(uint8_t Num, uint16_t Time, ...)
{
	uint8_t index = 7;
	uint8_t i = 0;
	uint16_t temp;
	va_list arg_ptr;

	va_start(arg_ptr, Time);               // 取得可变参数首地址
	
	TxBuf[0] = TxBuf[1] = FRAME_HEADER;    // 填充帧头
	TxBuf[2] = Num * 3 + 5;                // 数据长度 = 要控制舵机数 * 3 + 5
	TxBuf[3] = CMD_SERVO_MOVE;             // 舵机移动指令
	TxBuf[4] = Num;                        // 要控制舵机数
	TxBuf[5] = GET_LOW_BYTE(Time);         // 取得时间的低八位
	TxBuf[6] = GET_HIGH_BYTE(Time);        // 取得时间的高八位

	for (i = 0; i < Num; i++) {                           // 从可变参数中取得并循环填充舵机ID和对应目标位置
		temp = va_arg(arg_ptr, int);                        // 从可变参数中取得舵机ID
		TxBuf[index++] = GET_LOW_BYTE(((uint16_t)temp));
		temp = va_arg(arg_ptr, int);                        // 可变参数中取得对应目标位置
		TxBuf[index++] = GET_LOW_BYTE(((uint16_t)temp));    // 填充目标位置低八位
		TxBuf[index++] = GET_HIGH_BYTE(temp);               // 填充目标位置高八位
	}
	va_end(arg_ptr);                       // 置空arg_ptr

	UartWriteBuf(TxBuf, TxBuf[2] + 2);     // 发送
}


/*-------- NANO 串口通信函数 --------*/
// 向nano发送起始信号
void NanoStart()
{
	Usart_SendByte(NANO_USARTx, 1);
}
