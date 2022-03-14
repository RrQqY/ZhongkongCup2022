/*---------------- 2022年17届中控杯购物赛总程序 ----------------*/

#include <stdio.h>
#include "stm32f10x.h"

#include "main.h"


__IO float DutyCycle_Left = 0;        // 底盘左右轮的占空比和频率的全局变量
__IO float Frequency_Left = 0;
__IO float DutyCycle_Right = 0;
__IO float Frequency_Right = 0;

short Accel[3];                       // 陀螺仪加速度、角加速度、温度的全局变量
short Gyro[3];
float Temp;
float gyroX, gyroY, gyroZ;            // 三轴角速度的全局变量
short Angle[3];                       // 陀螺仪角度的全局变量
float integralX = 0.0f, integralY = 0.0f, integralZ = 0.0f;             // 累计偏角
int g_GetZeroOffset = 0;

// 读取MPU6050数据标志
// 置 1表示读取MPU6050数据完成，需要在主循环处理MPU6050数据
// 置 0表示未完成读取MPU6050数据，需要在中断中读取MPU6050数据
int task_readdata_finish = 0;


// 准备
void prepare(void){
	// 外设初始化
  GPIO_Config();
	ADVANCE_TIM_Init();
	SysTick_Init();
	ILI9341_Init ();                 // LCD 初始化    
  ILI9341_GramScan(6);             // LCD 显示模式6
	USART_Config();                  // USART 初始化
	i2c_GPIO_Config();               // I2C 初始化
	MPU6050_Init();                  // MPU6050 初始化
	
	// 初始速度全部设置为0
	Set_Speed(LEFTWHEEL_PWM_OUT, 0);
	Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
	Set_Speed(TRACK_PWM, 0);
	Set_Speed(SLIDE_PWM, 0);
	
	// LCD 初始化并清屏
	LCD_SetBackColor(BLACK);
	LCD_SetFont(&Font8x16);          // 设置字体
	LCD_SetColors(WHITE,BLACK);      // 设置颜色。形参1为前景色（字体颜色），形参2为背景色
  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
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

