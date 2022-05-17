/*---------------- 2022年17届中控杯购物赛总程序 ----------------*/

#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"

#include "main.h"


__IO float DutyCycle_Left = 0;        // 底盘左右轮的占空比和频率的全局变量
__IO float Frequency_Left = 0;
__IO float DutyCycle_Right = 0;
__IO float Frequency_Right = 0;

unsigned char TxBuffer[256];
unsigned char TxCounter=0;
unsigned char imu_count=0; 
void CopeSerial2Data(unsigned char ucData);

int IMU_Data;                         // IMU数据
short Accel[3];                       // 陀螺仪加速度、角加速度、温度的全局变量
short Gyro[3];
float Temp;
float gyroX, gyroY, gyroZ;            // 三轴角速度的全局变量
short Angle[3];                       // 陀螺仪角度的全局变量
float integralX = 0.0f, integralY = 0.0f, integralZ = 0.0f;             // 累计偏角
int g_GetZeroOffset = 0;

char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};  // 进入加速度校准模式
char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};  // 保存当前配置
int POS[6] = {0,0,0,0,0,0};                     // 上位机返回抓取位置信息
uint8_t Nano_Buff[8] = {0};
int flag_get = 0;
uint8_t time_now = 0;                           // 开机到现在的运行时间

// IMU 信号类型定义
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


// 读取MPU6050数据标志
// 置 1 表示读取MPU6050数据完成，需要在主循环处理MPU6050数据
// 置 0 表示未完成读取MPU6050数据，需要在中断中读取MPU6050数据
int task_readdata_finish = 0;


// 第一次测试
void Test1()
{
//	Forward(1);        // 巡线两格
//  Delay(500);
//	TrunTo_MPU(-180);
//	Delay(1000);
	
	NanoIOHigh();      // 第一次给Nano发信号，拍照片
	Delay(1500);
	Right_MPU(92);     // 右转
	Delay(500); 
	Forward_Front(1);  // 巡线一格（前灰度数线）
	Delay(500);
	Left_MPU(90);      // 左转
	Delay(1000);
	// 这里已经停到货架面前了
	MoveSrv7(1);       // 上层臂抬起
	MoveSrv15(0);      // 翻斗放下
	Delay(500);
	NanoIOHigh();      // 第二次给Nano发信号，爪子张开
	Delay(500);
	SlideOut();        // 滑轨向前移动
	Delay(500);
	NanoIOHigh();      // 第三次给Nano发信号，抓取
	Delay(1000);
	// 这里货物已经掉进翻斗了
	TrackMove();       // 履带向后转动
	Delay(800);
	SlideIn();         // 滑轨向后移动收回
	Delay(500);
	MoveSrv15(1);      // 翻斗抬起
	Delay(1500);
	TrackStop();       // 履带停止转动
	Delay(500);
	MoveSrv7(0);       // 上层臂放下
	Delay(500);
	// 这里可以开始返回了
	Right_MPU(89);     // 右转
	Delay(500);
	Back(1);        // 巡线一格
	Delay(500);
	Left_MPU(89);     // 右转
	Delay(500);
	
  // 先转一段，跨过黑线
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
	Delay(400);
}


// 第二次测试
void Test2()
{
//	Forward(1);        // 巡线两格
//  Delay(500);
//	TrunTo_MPU(-180);
//	Delay(1000);
	
	NanoIOHigh();      // 第一次给Nano发信号，拍照片
	Delay(1500);
	Right_MPU(92);     // 右转
	Delay(500); 
	Forward_Front(1);  // 巡线一格（前灰度数线）
	Delay(500);
	Left_MPU(90);      // 左转
	Delay(1000);
	// 这里已经停到货架面前了
	MoveSrv7(1);       // 上层臂抬起
	MoveSrv15(0);      // 翻斗放下
	Delay(500);
	NanoIOHigh();      // 第二次给Nano发信号，爪子张开
	Delay(500);
	SlideOut();        // 滑轨向前移动
	Delay(500);
	NanoIOHigh();      // 第三次给Nano发信号，抓取
	Delay(1000);
	// 这里货物已经掉进翻斗了
	TrackMove();       // 履带向后转动
	Delay(800);
	SlideIn();         // 滑轨向后移动收回
	Delay(500);
	MoveSrv15(1);      // 翻斗抬起
	Delay(1500);
	TrackStop();       // 履带停止转动
	Delay(500);
	MoveSrv7(0);       // 上层臂放下
	Delay(500);
	// 这里可以开始返回了
	Right_MPU(89);     // 右转
	Delay(500);
	Back(1);        // 巡线一格
	Delay(500);
	Left_MPU(89);     // 右转
	Delay(500);
	
  // 先转一段，跨过黑线
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
	Delay(400);
}


// 准备
void prepare(void){
	// 外设初始化
  GPIO_Config();
	ADVANCE_TIM_Init();
	SysTick_Init();
//	ILI9341_Init ();                 // LCD 初始化    
//  ILI9341_GramScan(6);             // LCD 显示模式6
	USART_Config();                  // USART 初始化
	i2c_GPIO_Config();               // I2C 初始化
	MPU6050_Init();                  // MPU6050 初始化
	
	// 初始速度全部设置为0
	Set_Speed(LEFTWHEEL_PWM_OUT, 0);
	Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
	Set_Speed(TRACK_PWM, 0);
	Set_Speed(SLIDE_PWM, 0);
	
	GPIO_Low(NANO6_GPIO_PORT, NANO6_GPIO_PIN);
	
	MoveSrv15(1);
//	// LCD 初始化并清屏
//	LCD_SetBackColor(BLACK);
//	LCD_SetFont(&Font8x16);          // 设置字体
//	LCD_SetColors(WHITE,BLACK);      // 设置颜色。形参1为前景色（字体颜色），形参2为背景色
//  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
}


// 开始
void start(void){
	// 1、底盘电机驱动 Demo
//	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // 左轮 High ，右轮 Low 向前；左轮 Low ，右轮 High 向后
//	GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//	Set_Speed(RIGHTWHEEL_PWM_OUT, 100);
//	Set_Speed(LEFTWHEEL_PWM_OUT, 100);

  // 2、滑轨电机驱动 Demo
//	GPIO_Low(SLIDE_GPIO_PORT, SLIDE_GPIO_PIN);              // 滑轨 Low 向前，High 向后
//	Set_Speed(SLIDE_PWM, 36);
//	SysTick_Delay_ms(500);
//	Set_Speed(SLIDE_PWM, 0);
	
  // 3、LCD 屏显示 Demo
//  uint16_t num = 31;
//  char s[100] = "helloworld";
//  LCD_Printn(num);
//  LCD_Prints(s);
	
	// 4、控制舵机 Demo
//	MoveSrv1(1);
//	MoveSrv1(0);
	
	// 5、巡线+数线停止+伸出滑轨+右转+张开爪子demo
//	Forward(1);                    // 向前巡线并数一根线
//	Delay(1000);
	
	//Catch();
	
//	Left();                        // 左转
	
  // 6、数两根线demo
  //Forward(5);

  // 7、履带运动demo
//	Set_Speed(TRACK          PWM, 128);

  // 8、MPU6050 转向demo
//	Left_MPU(90);
//	Delay(1000);
	
	// 9、显示电机速度+四个七路返回值demo
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
//	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
//  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
//	Delay(2000);
//	
//	Back(1);        // 巡线两格
//	Delay(500);
//	Right_MPU(90);     // 右转
//	Delay(500);
//	Back(1);        // 巡线两格
//	Delay(500);
//	Right_MPU(90);     // 右转
//	Delay(500);
//	Back(1);        // 巡线两格
//	Delay(1000);
//	
//	Test1();
//	
//	Forward(1);        // 巡线一格
//	Test1();
//	
//	Delay(1000);
//	Back(5);        // 巡线两格
//--------//

	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
	Delay(1200);
	
	Back_Front(1);    // 巡线一格（后灰度数线）
	Delay(500);
	Left_MPU(90);     // 左转
	Delay(500);
//	Forward(1);        // 巡线两格
//	Delay(500);

//	Forward_Front(1);  // 巡线一格（前灰度数线）
//	Delay(500);
//	Left_MPU(90);      // 左转
//	Delay(500);

	Back_Slide(2);

//	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
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
	
//	MoveSrv1(0);                   // 抓臂收回
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
//			GPIO_Low(GREEN_GPIO_PORT, GREEN_GPIO_PIN);    // 打开绿灯
//			GPIO_Low(RED_GPIO_PORT, RED_GPIO_PIN);
//			GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
//		}
//		else{
//			GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);    // 打开绿灯
//			GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);
//			GPIO_High(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
//		}
//	}
}


// main函数
int main(void)
{	
	prepare();                                        // 运行准备函数
	
	while(1){
	  if(GPIO_Read(START_GPIO_PORT, START_GPIO_PIN) == 1){
	  	GPIO_Low(GREEN_GPIO_PORT, GREEN_GPIO_PIN);    // 打开绿灯
			GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);
			
			start();                                      // 运行开始函数
			break;
	  }
		else if(GPIO_Read(START_GPIO_PORT, START_GPIO_PIN) == 0){
			GPIO_Low(RED_GPIO_PORT, RED_GPIO_PIN);
			GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);   // 打开红灯
	  }
  }
	
	return 0;
}



// 向Nano传递高电平IO信号
void NanoIOHigh()
{
	GPIO_High(NANO6_GPIO_PORT, NANO6_GPIO_PIN);
	Delay(5);
	GPIO_Low(NANO6_GPIO_PORT, NANO6_GPIO_PIN);
}


// LCD 屏显示数字函数
void LCD_Printn(int line, uint32_t num)
{
	char dispBuff[100];
	sprintf(dispBuff, "    %07d ",num);        // 使用c标准库把变量转化成字符串并显示
  LCD_ClearLine(LINE(line));	                          // 清除单行文字
	ILI9341_DispStringLine_EN_CH(LINE(line),dispBuff);
	
	Delay(300);
}


// LCD 屏显示字符串函数
void LCD_Prints(int line, char dispBuff[])
{
  LCD_ClearLine(LINE(line));	                          // 清除单行文字
	ILI9341_DispStringLine_EN_CH(LINE(line),dispBuff);
	
	Delay(300);
}


//// LCD屏幕测试函数
//void LCD_Test(void)
//{
//	LCD_SetFont(&Font8x16);          // 设置字体
//	LCD_SetColors(WHITE,BLACK);      // 设置颜色。形参1为前景色（字体颜色），形参2为背景色
//	
//	static uint8_t testCNT = 0;	
//	char dispBuff[100];
//	
//	testCNT++;	
//	
//	// 显示字符串示例
//  ILI9341_DispStringLine_EN_CH(LINE(0),"This is ZhongKongBei Robot");
//  ILI9341_DispStringLine_EN_CH(LINE(1),"Hello!!!");

//	LCD_SetTextColor(WHITE);        // 单独设置前景色

//	sprintf(dispBuff,"Display Data: %d ",testCNT);    // 使用c标准库把变量转化成字符串并显示
//  LCD_ClearLine(LINE(5));	                          // 清除单行文字
//	ILI9341_DispStringLine_EN_CH(LINE(5),dispBuff);
//	
//	Delay(300);

////	// 显示图形
////  // 画直线
////  LCD_ClearLine(LINE(7));/* 清除单行文字 */
////	LCD_SetTextColor(BLUE);
////  ILI9341_DispStringLine_EN_CH(LINE(7),"画直线：");
////	LCD_SetTextColor(RED);
////  ILI9341_DrawLine(50,170,210,230);  
////  ILI9341_DrawLine(50,200,210,240);
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawLine(100,170,200,230);  
////  ILI9341_DrawLine(200,200,220,240);
////	LCD_SetTextColor(BLUE);
////  ILI9341_DrawLine(110,170,110,230);  
////  ILI9341_DrawLine(130,200,220,240);
////  ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* 清屏，显示全黑 */

////  
////  // 画矩形
////  LCD_ClearLine(LINE(7));	/* 清除单行文字 */
////	LCD_SetTextColor(BLUE);
////  ILI9341_DispStringLine_EN_CH(LINE(7),"画矩形：");
////	LCD_SetTextColor(RED);
////  ILI9341_DrawRectangle(50,200,100,30,1);
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawRectangle(160,200,20,40,0);
////	LCD_SetTextColor(BLUE);
////  ILI9341_DrawRectangle(170,200,50,20,1);
////	ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* 清屏，显示全黑 */

////  // 画圆
////  LCD_ClearLine(LINE(7));	/* 清除单行文字 */
////	LCD_SetTextColor(BLUE);
////  ILI9341_DispStringLine_EN_CH(LINE(7),"画圆");
////	LCD_SetTextColor(RED);
////  ILI9341_DrawCircle(100,200,20,0);
////	LCD_SetTextColor(GREEN);
////  ILI9341_DrawCircle(100,200,10,1);
////	LCD_SetTextColor(BLUE);
////	ILI9341_DrawCircle(140,200,20,0);
////  ILI9341_Clear(0,16*8,LCD_X_LENGTH,LCD_Y_LENGTH-16*8);	/* 清屏，显示全黑 */
//}

///*"当"字符的字模16x16 */ 	  
//unsigned char charater_matrix[] =    
//{ /*"当",0*/
//0x01,0x00,0x21,0x08,0x11,0x08,0x09,0x10,0x09,0x20,0x01,0x00,0x7F,0xF8,0x00,	0x08,
//0x00,0x08,0x00,0x08,0x3F,0xF8,0x00,0x08,0x00,0x08,0x00,0x08,0x7F,0xF8,0x00,0x08,

//};   

