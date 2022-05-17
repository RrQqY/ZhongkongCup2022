/*---------------- 2022��17���пر��������ܳ��� ----------------*/

#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"

#include "main.h"


__IO float DutyCycle_Left = 0;        // ���������ֵ�ռ�ձȺ�Ƶ�ʵ�ȫ�ֱ���
__IO float Frequency_Left = 0;
__IO float DutyCycle_Right = 0;
__IO float Frequency_Right = 0;

unsigned char TxBuffer[256];
unsigned char TxCounter=0;
unsigned char imu_count=0; 
void CopeSerial2Data(unsigned char ucData);

int IMU_Data;                         // IMU����
short Accel[3];                       // �����Ǽ��ٶȡ��Ǽ��ٶȡ��¶ȵ�ȫ�ֱ���
short Gyro[3];
float Temp;
float gyroX, gyroY, gyroZ;            // ������ٶȵ�ȫ�ֱ���
short Angle[3];                       // �����ǽǶȵ�ȫ�ֱ���
float integralX = 0.0f, integralY = 0.0f, integralZ = 0.0f;             // �ۼ�ƫ��
int g_GetZeroOffset = 0;

char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};  // ������ٶ�У׼ģʽ
char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};  // ���浱ǰ����
int POS[6] = {0,0,0,0,0,0};                     // ��λ������ץȡλ����Ϣ
uint8_t Nano_Buff[8] = {0};
int flag_get = 0;
uint8_t time_now = 0;                           // ���������ڵ�����ʱ��

// IMU �ź����Ͷ���
struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;


// ��ȡMPU6050���ݱ�־
// �� 1 ��ʾ��ȡMPU6050������ɣ���Ҫ����ѭ������MPU6050����
// �� 0 ��ʾδ��ɶ�ȡMPU6050���ݣ���Ҫ���ж��ж�ȡMPU6050����
int task_readdata_finish = 0;


// ��һ�β���
void Test1()
{
//	Forward(1);        // Ѳ������
//  Delay(500);
//	TrunTo_MPU(-180);
//	Delay(1000);
	
	NanoIOHigh();      // ��һ�θ�Nano���źţ�����Ƭ
	Delay(1500);
	Right_MPU(92);     // ��ת
	Delay(500); 
	Forward_Front(1);  // Ѳ��һ��ǰ�Ҷ����ߣ�
	Delay(500);
	Left_MPU(90);      // ��ת
	Delay(1000);
	// �����Ѿ�ͣ��������ǰ��
	MoveSrv7(1);       // �ϲ��̧��
	MoveSrv15(0);      // ��������
	Delay(500);
	NanoIOHigh();      // �ڶ��θ�Nano���źţ�צ���ſ�
	Delay(500);
	SlideOut();        // ������ǰ�ƶ�
	Delay(500);
	NanoIOHigh();      // �����θ�Nano���źţ�ץȡ
	Delay(1000);
	// ��������Ѿ�����������
	TrackMove();       // �Ĵ����ת��
	Delay(800);
	SlideIn();         // ��������ƶ��ջ�
	Delay(500);
	MoveSrv15(1);      // ����̧��
	Delay(1500);
	TrackStop();       // �Ĵ�ֹͣת��
	Delay(500);
	MoveSrv7(0);       // �ϲ�۷���
	Delay(500);
	// ������Կ�ʼ������
	Right_MPU(89);     // ��ת
	Delay(500);
	Back(1);        // Ѳ��һ��
	Delay(500);
	Left_MPU(89);     // ��ת
	Delay(500);
	
  // ��תһ�Σ��������
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼֱ��
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
	Delay(400);
}


// �ڶ��β���
void Test2()
{
//	Forward(1);        // Ѳ������
//  Delay(500);
//	TrunTo_MPU(-180);
//	Delay(1000);
	
	NanoIOHigh();      // ��һ�θ�Nano���źţ�����Ƭ
	Delay(1500);
	Right_MPU(92);     // ��ת
	Delay(500); 
	Forward_Front(1);  // Ѳ��һ��ǰ�Ҷ����ߣ�
	Delay(500);
	Left_MPU(90);      // ��ת
	Delay(1000);
	// �����Ѿ�ͣ��������ǰ��
	MoveSrv7(1);       // �ϲ��̧��
	MoveSrv15(0);      // ��������
	Delay(500);
	NanoIOHigh();      // �ڶ��θ�Nano���źţ�צ���ſ�
	Delay(500);
	SlideOut();        // ������ǰ�ƶ�
	Delay(500);
	NanoIOHigh();      // �����θ�Nano���źţ�ץȡ
	Delay(1000);
	// ��������Ѿ�����������
	TrackMove();       // �Ĵ����ת��
	Delay(800);
	SlideIn();         // ��������ƶ��ջ�
	Delay(500);
	MoveSrv15(1);      // ����̧��
	Delay(1500);
	TrackStop();       // �Ĵ�ֹͣת��
	Delay(500);
	MoveSrv7(0);       // �ϲ�۷���
	Delay(500);
	// ������Կ�ʼ������
	Right_MPU(89);     // ��ת
	Delay(500);
	Back(1);        // Ѳ��һ��
	Delay(500);
	Left_MPU(89);     // ��ת
	Delay(500);
	
  // ��תһ�Σ��������
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼֱ��
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
	Delay(400);
}


// ׼��
void prepare(void){
	// �����ʼ��
  GPIO_Config();
	ADVANCE_TIM_Init();
	SysTick_Init();
//	ILI9341_Init ();                 // LCD ��ʼ��    
//  ILI9341_GramScan(6);             // LCD ��ʾģʽ6
	USART_Config();                  // USART ��ʼ��
	i2c_GPIO_Config();               // I2C ��ʼ��
	MPU6050_Init();                  // MPU6050 ��ʼ��
	
	// ��ʼ�ٶ�ȫ������Ϊ0
	Set_Speed(LEFTWHEEL_PWM_OUT, 0);
	Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
	Set_Speed(TRACK_PWM, 0);
	Set_Speed(SLIDE_PWM, 0);
	
	GPIO_Low(NANO6_GPIO_PORT, NANO6_GPIO_PIN);
	
	MoveSrv15(1);
//	// LCD ��ʼ��������
//	LCD_SetBackColor(BLACK);
//	LCD_SetFont(&Font8x16);          // ��������
//	LCD_SetColors(WHITE,BLACK);      // ������ɫ���β�1Ϊǰ��ɫ��������ɫ�����β�2Ϊ����ɫ
//  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
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
//		                                                                                                                                                                        Seven_Read(right, 3), 
//	                           Seven_Read(right, 4), 
//	                           Seven_Read(right, 5), 
//	                           Seven_Read(right, 6), 
//		                         Seven_Read(right, 7)));
//	}

//--------//
//	MoveSrv13(0);
//	MoveSrv14(0);
//	Delay(800);
//	
//	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼֱ��
//  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
//  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
//	Delay(2000);
//	
//	Back(1);        // Ѳ������
//	Delay(500);
//	Right_MPU(90);     // ��ת
//	Delay(500);
//	Back(1);        // Ѳ������
//	Delay(500);
//	Right_MPU(90);     // ��ת
//	Delay(500);
//	Back(1);        // Ѳ������
//	Delay(1000);
//	
//	Test1();
//	
//	Forward(1);        // Ѳ��һ��
//	Test1();
//	
//	Delay(1000);
//	Back(5);        // Ѳ������
//--------//

	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼֱ��
  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
	Delay(1200);
	
	Back_Front(1);    // Ѳ��һ�񣨺�Ҷ����ߣ�
	Delay(500);
	Left_MPU(90);     // ��ת
	Delay(500);
//	Forward(1);        // Ѳ������
//	Delay(500);

//	Forward_Front(1);  // Ѳ��һ��ǰ�Ҷ����ߣ�
//	Delay(500);
//	Left_MPU(90);      // ��ת
//	Delay(500);

	Back_Slide(2);

//	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼֱ��
//  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
//  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
//	Delay(2000);
//	TrunTo_MPU(90);
	
//  NanoIOHigh();
//	Forward(2);
//	Delay(500);
//	Right_MPU(90);
//	Delay(500); 
//	Forward_Front(1);
//	Delay(500);
//	Left_MPU(90);
//	Delay(500);
//	
//	Catch();

//	Delay(500);
//	Left_MPU(90);
//	Delay(500);
//	Forward(2);
//	Delay(500);
//	Right_MPU(90);
//	Delay(500);
//	Forward(2);

//	NanoStart();
//  Usart_SendString(DEBUG_USARTx, "heyhey");
//	Delay(1000);
	
//	MoveSrv1(0);                   // ץ���ջ�
//	MoveSrv2(0);
//	MoveSrv3(0);
//	MoveSrv4(0);
//	MoveSrv5(0);
//	MoveSrv6(0);
//	Delay(1000);
//	NanoCatch();

//	Usart_SendByte( DEBUG_USARTx, 65);


//  int time_flag = 0;
//	int Nano1_sum, Nano2_sum, Nano3_sum, Nano4_sum, Nano5_sum, Nano6_sum = 0;
//	double Nano1_res, Nano2_res, Nano3_res, Nano4_res, Nano5_res, Nano6_res = 0;		
//	while(time_flag <= 100){
//		Nano1_sum += Nano_Read(1);
//		Nano2_sum += Nano_Read(2);
//		Nano3_sum += Nano_Read(3);
//		Nano4_sum += Nano_Read(4);
//		Nano5_sum += Nano_Read(5);
//		Nano6_sum += Nano_Read(6);
//		
//		time_flag ++;
//		Delay(10);
//	}
//	Nano1_res = Nano1_sum * 0.01;
//	Nano2_res = Nano2_sum * 0.01;
//	Nano3_res = Nano3_sum * 0.01;
//	Nano4_res = Nano4_sum * 0.01;
//	Nano5_res = Nano5_sum * 0.01;
//	Nano6_res = Nano6_sum * 0.01;
//	
//	if(Nano1_res >= 0.5){ MoveSrv1(1); }else{ MoveSrv1(0); }
//	if(Nano2_res >= 0.5){ MoveSrv2(1); }else{ MoveSrv2(0); }
//	if(Nano3_res >= 0.5){ MoveSrv3(1); }else{ MoveSrv3(0); }
//	if(Nano4_res >= 0.5){ MoveSrv4(1); }else{ MoveSrv4(0); }
//	if(Nano5_res >= 0.5){ MoveSrv5(1); }else{ MoveSrv5(0); }
//	if(Nano6_res >= 0.5){ MoveSrv6(1); }else{ MoveSrv6(0); }

//	while(1){
//		if(Nano_Buff[1] == 0x12){
//			GPIO_Low(GREEN_GPIO_PORT, GREEN_GPIO_PIN);    // ���̵�
//			GPIO_Low(RED_GPIO_PORT, RED_GPIO_PIN);
//			GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
//		}
//		else{
//			GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);    // ���̵�
//			GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);
//			GPIO_High(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
//		}
//	}
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



// ��Nano���ݸߵ�ƽIO�ź�
void NanoIOHigh()
{
	GPIO_High(NANO6_GPIO_PORT, NANO6_GPIO_PIN);
	Delay(5);
	GPIO_Low(NANO6_GPIO_PORT, NANO6_GPIO_PIN);
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

