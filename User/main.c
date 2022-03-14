/*---------------- 2022��17���пر��������ܳ��� ----------------*/

#include <stdio.h>
#include "stm32f10x.h"

#include "main.h"


__IO float DutyCycle_Left = 0;        // ���������ֵ�ռ�ձȺ�Ƶ�ʵ�ȫ�ֱ���
__IO float Frequency_Left = 0;
__IO float DutyCycle_Right = 0;
__IO float Frequency_Right = 0;

short Accel[3];                       // �����Ǽ��ٶȡ��Ǽ��ٶȡ��¶ȵ�ȫ�ֱ���
short Gyro[3];
float Temp;
float gyroX, gyroY, gyroZ;            // ������ٶȵ�ȫ�ֱ���
short Angle[3];                       // �����ǽǶȵ�ȫ�ֱ���
float integralX = 0.0f, integralY = 0.0f, integralZ = 0.0f;             // �ۼ�ƫ��
int g_GetZeroOffset = 0;

// ��ȡMPU6050���ݱ�־
// �� 1��ʾ��ȡMPU6050������ɣ���Ҫ����ѭ������MPU6050����
// �� 0��ʾδ��ɶ�ȡMPU6050���ݣ���Ҫ���ж��ж�ȡMPU6050����
int task_readdata_finish = 0;


// ׼��
void prepare(void){
	// �����ʼ��
  GPIO_Config();
	ADVANCE_TIM_Init();
	SysTick_Init();
	ILI9341_Init ();                 // LCD ��ʼ��    
  ILI9341_GramScan(6);             // LCD ��ʾģʽ6
	USART_Config();                  // USART ��ʼ��
	i2c_GPIO_Config();               // I2C ��ʼ��
	MPU6050_Init();                  // MPU6050 ��ʼ��
	
	// ��ʼ�ٶ�ȫ������Ϊ0
	Set_Speed(LEFTWHEEL_PWM_OUT, 0);
	Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
	Set_Speed(TRACK_PWM, 0);
	Set_Speed(SLIDE_PWM, 0);
	
	// LCD ��ʼ��������
	LCD_SetBackColor(BLACK);
	LCD_SetFont(&Font8x16);          // ��������
	LCD_SetColors(WHITE,BLACK);      // ������ɫ���β�1Ϊǰ��ɫ��������ɫ�����β�2Ϊ����ɫ
  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
}


// ��ʼ
void start(void){
	// 1�����̵������ Demo
//	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // ���� High ������ Low ��ǰ������ Low ������ High ���
//	GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//	Set_Speed(RIGHTWHEEL_PWM_OUT, 100);
//	Set_Speed(LEFTWHEEL_PWM_OUT, 100);

  // 2������������ Demo
//	GPIO_Low(SLIDE_GPIO_PORT, SLIDE_GPIO_PIN);              // ���� Low ��ǰ��High ���
//	Set_Speed(SLIDE_PWM, 36);
//	SysTick_Delay_ms(500);
//	Set_Speed(SLIDE_PWM, 0);
	
  // 3��LCD ����ʾ Demo
//  uint16_t num = 31;
//  char s[100] = "helloworld";
//  LCD_Printn(num);
//  LCD_Prints(s);
	
	// 4�����ƶ�� Demo
//	MoveSrv1(1);
//	MoveSrv1(0);
	
	// 5��Ѳ��+����ֹͣ+�������+��ת+�ſ�צ��demo
//	Forward(1);                    // ��ǰѲ�߲���һ����
//	Delay(1000);
	
	//Catch();
	
//	Left();                        // ��ת
	
  // 6����������demo
  //Forward(5);

  // 7���Ĵ��˶�demo
//	Set_Speed(TRACK          PWM, 128);

  // 8��MPU6050 ת��demo
//	Left_MPU(90);
//	Delay(1000);
	
	// 9����ʾ����ٶ�+�ĸ���·����ֵdemo
//	while(1){
//		LCD_Prints(1, "PWM DutyCycle of base motor: ");
//	  LCD_Printn(2, INT16_C(DutyCycle_Left));
//		LCD_Printn(3, INT16_C(DutyCycle_Right));
//		
//		LCD_Prints(5, "Signals of seven detector: ");
//		LCD_Printn(6, SevenTotal(Seven_Read(front, 1), 
//		                         Seven_Read(front, 2), 
//		                         Seven_Read(front, 3), 
//	                           Seven_Read(front, 4), 
//	                           Seven_Read(front, 5), 
//	                           Seven_Read(front, 6), 
//		                         Seven_Read(front, 7)));
//		LCD_Printn(7, SevenTotal(Seven_Read(back, 1), 
//		                         Seven_Read(back, 2), 
//		                         Seven_Read(back, 3), 
//	                           Seven_Read(back, 4), 
//	                           Seven_Read(back, 5), 
//	                           Seven_Read(back, 6), 
//		                         Seven_Read(back, 7)));
//		LCD_Printn(8, SevenTotal(Seven_Read(left, 1), 
//		                         Seven_Read(left, 2), 
//		                         Seven_Read(left, 3), 
//	                           Seven_Read(left, 4), 
//	                           Seven_Read(left, 5), 
//	                           Seven_Read(left, 6), 
//		                         Seven_Read(left, 7)));
//		LCD_Printn(9, SevenTotal(Seven_Read(right, 1), 
//		                         Seven_Read(right, 2), 
//		                         Seven_Read(right, 3), 
//	                           Seven_Read(right, 4), 
//	                           Seven_Read(right, 5), 
//	                           Seven_Read(right, 6), 
//		                         Seven_Read(right, 7)));
//	}

	Forward(2);
	Delay(500);
	Right_MPU(90);
	Delay(500);
	Forward_Front(1);
	Delay(500);
	Left_MPU(90);
	Delay(500);
	Catch();
}


// main����
int main(void)
{	
	prepare();                                        // ����׼������
	
	while(1){
	  if(GPIO_Read(START_GPIO_PORT, START_GPIO_PIN) == 1){
	  	GPIO_Low(GREEN_GPIO_PORT, GREEN_GPIO_PIN);    // ���̵�
			GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);
			
			start();                                      // ���п�ʼ����
			break;
	  }
		else if(GPIO_Read(START_GPIO_PORT, START_GPIO_PIN) == 0){
			GPIO_Low(RED_GPIO_PORT, RED_GPIO_PIN);
			GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);   // �򿪺��
	  }
  }
	
	return 0;
}


// LCD ����ʾ���ֺ���
void LCD_Printn(int line, uint32_t num)
{
	char dispBuff[100];
	sprintf(dispBuff, "    %07d ",num);        // ʹ��c��׼��ѱ���ת�����ַ�������ʾ
  LCD_ClearLine(LINE(line));	                          // �����������
	ILI9341_DispStringLine_EN_CH(LINE(line),dispBuff);
	
	Delay(300);
}


// LCD ����ʾ�ַ�������
void LCD_Prints(int line, char dispBuff[])
{
  LCD_ClearLine(LINE(line));	                          // �����������
	ILI9341_DispStringLine_EN_CH(LINE(line),dispBuff);
	
	Delay(300);
}


//// LCD��Ļ���Ժ���
//void LCD_Test(void)
//{
//	LCD_SetFont(&Font8x16);          // ��������
//	LCD_SetColors(WHITE,BLACK);      // ������ɫ���β�1Ϊǰ��ɫ��������ɫ�����β�2Ϊ����ɫ
//	
//	static uint8_t testCNT = 0;	
//	char dispBuff[100];
//	
//	testCNT++;	
//	
//	// ��ʾ�ַ���ʾ��
//  ILI9341_DispStringLine_EN_CH(LINE(0),"This is ZhongKongBei Robot");
//  ILI9341_DispStringLine_EN_CH(LINE(1),"Hello!!!");

//	LCD_SetTextColor(WHITE);        // ��������ǰ��ɫ

//	sprintf(dispBuff,"Display Data: %d ",testCNT);    // ʹ��c��׼��ѱ���ת�����ַ�������ʾ
//  LCD_ClearLine(LINE(5));	                          // �����������
//	ILI9341_DispStringLine_EN_CH(LINE(5),dispBuff);
//	
//	Delay(300);

////	// ��ʾͼ��
////  // ��ֱ��
////  LCD_ClearLine(LINE(7));/* ����������� */
////	LCD_SetTextColor(BLUE);
////  ILI9341_DispStringLine_EN_CH(LINE(7),"��ֱ�ߣ�");
////	LCD_SetTextColor(RED);
////  ILI9341_DrawLine(50,170,210,230);  
////  ILI9341_DrawLine(50,200,210,240);
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawLine(100,170,200,230);  
////  ILI9341_DrawLine(200,200,220,240);
////	LCD_SetTextColor(BLUE);
////  ILI9341_DrawLine(110,170,110,230);  
////  ILI9341_DrawLine(130,200,220,240);
////  ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */

////  
////  // ������
////  LCD_ClearLine(LINE(7));	/* ����������� */
////	LCD_SetTextColor(BLUE);
////  ILI9341_DispStringLine_EN_CH(LINE(7),"�����Σ�");
////	LCD_SetTextColor(RED);
////  ILI9341_DrawRectangle(50,200,100,30,1);
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawRectangle(160,200,20,40,0);
////	LCD_SetTextColor(BLUE);
////  ILI9341_DrawRectangle(170,200,50,20,1);
////	ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */

////  // ��Բ
////  LCD_ClearLine(LINE(7));	/* ����������� */
////	LCD_SetTextColor(BLUE);
////  ILI9341_DispStringLine_EN_CH(LINE(7),"��Բ");
////	LCD_SetTextColor(RED);
////  ILI9341_DrawCircle(100,200,20,0);
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawCircle(100,200,10,1);
////	LCD_SetTextColor(BLUE);
////	ILI9341_DrawCircle(140,200,20,0);
////  ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* ��������ʾȫ�� */
//}

///*"��"�ַ�����ģ16x16 */ 	  
//unsigned char charater_matrix[] =    
//{ /*"��",0*/
//0x01,0x00,0x21,0x08,0x11,0x08,0x09,0x10,0x09,0x20,0x01,0x00,0x7F,0xF8,0x00,	0x08,
//0x00,0x08,0x00,0x08,0x3F,0xF8,0x00,0x08,0x00,0x08,0x00,0x08,0x7F,0xF8,0x00,0x08,

//};   

