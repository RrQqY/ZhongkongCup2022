#include "usart.h"
#include "main.h"
#include <stdarg.h>
#include <string.h>

// �жϿ����� NVIC ����
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
	// ������ư崮���жϳ�ʼ��
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                   // Ƕ�������жϿ�������ѡ��
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;             // ����USARTΪ�ж�Դ
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;         // ��������
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                // �����ȼ�
	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   // ʹ���ж�
  NVIC_Init(&NVIC_InitStructure);                                   // ��ʼ������NVIC
	
	// nanoͨ�Ŵ����жϳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                   // Ƕ�������жϿ�������ѡ��
  NVIC_InitStructure.NVIC_IRQChannel = NANO_USART_IRQ;              // ����USARTΪ�ж�Դ
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;         // ��������
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                // �����ȼ�
	
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   // ʹ���ж�
  NVIC_Init(&NVIC_InitStructure);                                   // ��ʼ������NVIC
	
//	// IMUͨ�Ŵ����жϳ�ʼ��
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                   // Ƕ�������жϿ�������ѡ��
//  NVIC_InitStructure.NVIC_IRQChannel = IMU_USART_IRQ;               // ����USARTΪ�ж�Դ
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;         // ��������
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;                // �����ȼ�
//	
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                   // ʹ���ж�
//  NVIC_Init(&NVIC_InitStructure);                                   // ��ʼ������NVIC
}


// USART ����� GPIO ����
void USART_Config(void)
{
	// ���ô�����ص� GPIO
	GPIO_InitTypeDef  GPIO_InitStructure;
	// ������ư� GPIO ����
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);        // �򿪴���GPIO��ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);                  // �򿪴��������ʱ��

	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                   // ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// nanoͨ�� GPIO ����
	NANO_USART_GPIO_APBxClkCmd(NANO_USART_GPIO_CLK, ENABLE);        // �򿪴���GPIO��ʱ��
	NANO_USART_APBxClkCmd(NANO_USART_CLK, ENABLE);                  // �򿪴��������ʱ��

	GPIO_InitStructure.GPIO_Pin = NANO_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                   // ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(NANO_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = NANO_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_Init(NANO_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
//	// IMUͨ�� GPIO ����
//	IMU_USART_GPIO_APBxClkCmd(IMU_USART_GPIO_CLK, ENABLE);        // �򿪴���GPIO��ʱ��
//	IMU_USART_APBxClkCmd(IMU_USART_CLK, ENABLE);                  // �򿪴��������ʱ��

//	GPIO_InitStructure.GPIO_Pin = IMU_USART_TX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                   // ��USART Tx��GPIO����Ϊ���츴��ģʽ
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(IMU_USART_TX_GPIO_PORT, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = IMU_USART_RX_GPIO_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;             // ��USART Rx��GPIO����Ϊ��������ģʽ
//	GPIO_Init(IMU_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	// ���ô��ڵĹ�������
	USART_InitTypeDef USART_InitStructure;
	// ������ư崮������
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;        // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       // ��������֡�ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1;            // ����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;              // ����У��λ
	USART_InitStructure.USART_HardwareFlowControl =                   // ����Ӳ��������
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   // ���ù���ģʽ���շ�һ��
	
	USART_Init(DEBUG_USARTx, &USART_InitStructure);                   // ��ɴ��ڵĳ�ʼ������
	
	NVIC_Configuration();                                             // �����ж����ȼ�����
	
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	            // ʹ�ܴ��ڽ����ж�
	
	USART_Cmd(DEBUG_USARTx, ENABLE);	                                // ʹ�ܴ���
	
	// nanoͨ�Ŵ�������
	USART_InitStructure.USART_BaudRate = NANO_USART_BAUDRATE;         // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       // ��������֡�ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1;            // ����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;              // ����У��λ
	USART_InitStructure.USART_HardwareFlowControl =                   // ����Ӳ��������
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   // ���ù���ģʽ���շ�һ��
	
	USART_Init(NANO_USARTx, &USART_InitStructure);                    // ��ɴ��ڵĳ�ʼ������
	
	NVIC_Configuration();                                             // �����ж����ȼ�����
	
	USART_ITConfig(NANO_USARTx, USART_IT_RXNE, ENABLE);	              // ʹ�ܴ��ڽ����ж�
	
	USART_Cmd(NANO_USARTx, ENABLE);	                                  // ʹ�ܴ���
	
//	// IMUͨ�Ŵ�������
//	USART_InitStructure.USART_BaudRate = IMU_USART_BAUDRATE;          // ���ò�����
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       // ��������֡�ֳ�
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;            // ����ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No ;              // ����У��λ
//	USART_InitStructure.USART_HardwareFlowControl =                   // ����Ӳ��������
//	USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   // ���ù���ģʽ���շ�һ��
//	
//	USART_Init(IMU_USARTx, &USART_InitStructure);                     // ��ɴ��ڵĳ�ʼ������
//	
//	NVIC_Configuration();                                             // �����ж����ȼ�����
//	
//	USART_ITConfig(IMU_USARTx, USART_IT_RXNE, ENABLE);	              // ʹ�ܴ��ڽ����ж�
//	
//	USART_Cmd(IMU_USARTx, ENABLE);	                                  // ʹ�ܴ���
}


// ����һ���ֽ�
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx,ch);        // ����һ���ֽ����ݵ�USART
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	  // �ȴ��������ݼĴ���Ϊ��
}

// ����8λ������
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++){
	    Usart_SendByte(pUSARTx,array[i]);	    // ����һ���ֽ����ݵ�USART
  
  }
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);         // �ȴ��������
}

// �����ַ���
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET){}        // �ȴ��������
} 

// ����һ��16λ��
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);
	GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
	GPIO_High(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
	
	uint8_t temp_h, temp_l;
	
	temp_h = (ch&0XFF00)>>8;        // ȡ���߰�λ
	temp_l = ch&0XFF;               // ȡ���Ͱ�λ
	
	USART_SendData(pUSARTx,temp_h);	        // ���͸߰�λ
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	USART_SendData(pUSARTx,temp_l);	        // ���͵Ͱ�λ
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}


// �������ư�д��ָ����β�1Ϊָ����飬�β�2Ϊָ�����
void UartWriteBuf(uint8_t *buf, uint8_t len)
{
	while (len--) {
		while ((USART1->SR & 0x40) == 0);
		USART_SendData(USART1,*buf++);
	}
}

// IMUд��ָ��
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


// ����2�жϵ��ú���������ÿ�յ�һ�����ݣ�����һ���������
void CopeSerial2Data(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;	  // ���յ������ݴ��뻺������
	if (ucRxBuffer[0]!=0x55){        // ����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}       // ���ݲ���11�����򷵻�
	else{
		switch(ucRxBuffer[1]){        // �ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
			case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);;break;  // memcpyΪ�������Դ����ڴ濽�������������ջ��������ַ����������ݽṹ�����棬ʵ�����ݵĽ�����
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
		ucRxCnt=0;                    // ��ջ�����
	}
}


/*-------- ������ƺ��� --------*/
uint8_t TxBuf[128];  //���ͻ���

// ���Ƶ������ת�����β�1Ϊת�������ID���β�2Ϊת����ʱ�䣬�β�3ΪҪת������λ��
void MoveServo(uint8_t servoID, uint16_t Time, uint16_t Position)
{
	if (servoID > 31 || !(Time > 0)) {  //���ID���ܴ���31,�ɸ��ݶ�Ӧ���ư��޸�
		return;
	}
	TxBuf[0] = TxBuf[1] = FRAME_HEADER;    //���֡ͷ
	TxBuf[2] = 8;                          //���ݳ��� = Ҫ���ƶ����*3+5���˴� = 1*3+5
	TxBuf[3] = CMD_SERVO_MOVE;             //������ƶ�ָ��
	TxBuf[4] = 1;                          //Ҫ���ƵĶ������
	TxBuf[5] = GET_LOW_BYTE(Time);         //ȡ��ʱ��ĵͰ�λ
	TxBuf[6] = GET_HIGH_BYTE(Time);        //ȡ��ʱ��ĸ߰�λ
	TxBuf[7] = servoID;                    //���ID
	TxBuf[8] = GET_LOW_BYTE(Position);     //ȡ��Ŀ��λ�õĵͰ�λ
	TxBuf[9] = GET_HIGH_BYTE(Position);    //ȡ��Ŀ��λ�õĸ߰�λ

	UartWriteBuf(TxBuf, 10);
}


// ���ƶ�����ת�����β�1Ϊ����������β�2Ϊת����ʱ�䣬...�����ID��ת���Ƕȣ����ID��ת���Ƕ�...
void MoveServos(uint8_t Num, uint16_t Time, ...)
{
	uint8_t index = 7;
	uint8_t i = 0;
	uint16_t temp;
	va_list arg_ptr;

	va_start(arg_ptr, Time);               // ȡ�ÿɱ�����׵�ַ
	
	TxBuf[0] = TxBuf[1] = FRAME_HEADER;    // ���֡ͷ
	TxBuf[2] = Num * 3 + 5;                // ���ݳ��� = Ҫ���ƶ���� * 3 + 5
	TxBuf[3] = CMD_SERVO_MOVE;             // ����ƶ�ָ��
	TxBuf[4] = Num;                        // Ҫ���ƶ����
	TxBuf[5] = GET_LOW_BYTE(Time);         // ȡ��ʱ��ĵͰ�λ
	TxBuf[6] = GET_HIGH_BYTE(Time);        // ȡ��ʱ��ĸ߰�λ

	for (i = 0; i < Num; i++) {                           // �ӿɱ������ȡ�ò�ѭ�������ID�Ͷ�ӦĿ��λ��
		temp = va_arg(arg_ptr, int);                        // �ӿɱ������ȡ�ö��ID
		TxBuf[index++] = GET_LOW_BYTE(((uint16_t)temp));
		temp = va_arg(arg_ptr, int);                        // �ɱ������ȡ�ö�ӦĿ��λ��
		TxBuf[index++] = GET_LOW_BYTE(((uint16_t)temp));    // ���Ŀ��λ�õͰ�λ
		TxBuf[index++] = GET_HIGH_BYTE(temp);               // ���Ŀ��λ�ø߰�λ
	}
	va_end(arg_ptr);                       // �ÿ�arg_ptr

	UartWriteBuf(TxBuf, TxBuf[2] + 2);     // ����
}


/*-------- NANO ����ͨ�ź��� --------*/
// ��nano������ʼ�ź�
void NanoStart()
{
	Usart_SendByte(NANO_USARTx, 1);
}
