/*----------前进，左转90度，右转90度，停止---------*/      

#include "Move.h"

#include <stdio.h>
#include <stdlib.h>   

static int correct_count = 0;


// 履带转动
void TrackMove(void)
{
	Set_Speed(TRACK_PWM, 128);
}


// 履带停止           
void TrackStop(void)                
{
	Set_Speed(TRACK_PWM, 0);
}



// 巡线直行 n  根线。形参1为数线数量
void Forward(int Line_Count) {            
  int Temp_Count = 0;                     // 当前所在线数
	int flag = 0;                           // 开始计数标志
	
	// 先转一段，跨过黑线
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
	Delay(750);
	
	while (1) {		
//		Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
//		Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
//		
    if (Seven_Read(left, 4) == low) {                          // 检测到黑色，开启计数准备
	    flag = 1;
	  }
	  if ((flag == 1) && (Seven_Read(left, 4) == high)) {        // 由黑色变为白色，计数一次
		  Temp_Count ++;                          
			if(Temp_Count < Line_Count){
				// 先转一段，跨过黑线
				Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
				Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
				GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
				GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
				Delay(100);
			}
		  flag = 0;
	  }
		
		// 在线前提前减速
		if ((Seven_Read(left, 1) == high) || (Seven_Read(right, 1)) == high) {        // 中间的前一个灰度数到线时先减速
		  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
      Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
	  }
		
//		// 在线前转正
//		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // 左侧中间的先检测到线
//		  while(1){
//			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//				if(Seven_Read(right, 4) == high) break;
//			}
//	  }
//		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // 右侧中间的先检测到线
//		  while(1){
//			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//				if(Seven_Read(left, 4) == high) break;
//			}
//	  }
		
		// 在线前转正
		// 左侧中间的先检测到线
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) { 
			// 如果右侧灰度前半部分检测到白线，说明右轮应该向前
			if ((Seven_Read(right, 7) == high) || (Seven_Read(right, 6) == high) || (Seven_Read(right, 5) == high)){
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
					Set_Speed(LEFTWHEEL_PWM_OUT, 0);
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
						correct_count = 0;
					}
//					if(Seven_Read(right, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
			}
			// 如果右侧灰度后半部分检测到白线，说明右轮应该向后
			else if ((Seven_Read(right, 3) == high) || (Seven_Read(right, 2) == high) || (Seven_Read(right, 1) == high)) {
				while(1){
					Set_Speed(LEFTWHEEL_PWM_OUT, 0);
					Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
					GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // 右轮向后转
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
						correct_count = 0;
					}
//					if(Seven_Read(right, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
			}
	  }
		// 右侧中间的先检测到线
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) { 
			// 如果左侧灰度前半部分检测到白线，说明左轮应该向前
			if ((Seven_Read(left, 1 == high) || (Seven_Read(left, 2) == high) || (Seven_Read(left, 3) == high))){
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
					Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
					}
//					if(Seven_Read(left, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
				correct_count = 0;
			}
			// 如果左侧灰度后半部分检测到白线，说明左轮应该向后
			else if ((Seven_Read(left, 5) == high) || (Seven_Read(left, 6) == high) || (Seven_Read(left, 7) == high)) {
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
					Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
					GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);    // 左轮向后转
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
					}
//					if(Seven_Read(left, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
				correct_count = 0;
			}
	  }
		
		// 数到对应的根数退出循环
		if (Temp_Count >= Line_Count) {
		  Stop_Forward();
			return;
	  }
		
		Delay(20);
//		LCD_Printn(1, Temp_Count);                                 // 显示已经数了几根线
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
														 
	  PID();                                                   // 开始PID循线
	}
}


// 巡线直行 n 根线（前七路数线）。
void Forward_Front(int Line_Count) {            
  int Temp_Count = 0;                     // 当前所在线数
	int flag = 0;                           // 开始计数标志
	
//	// 先转一段，跨过黑线
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
	Delay(750);
	
	while (1) {
    if (Seven_Read(left, 4) == low) {                          // 检测到黑色，开启计数准备
	    flag = 1;
	  }
	  if ((flag == 1) && 
			  (((Seven_Read(front, 2) == high) && (Seven_Read(front, 6)) == high) || 
			  ((Seven_Read(front, 1) == high) && (Seven_Read(front, 7)) == high))){     // 由黑色变为白色，计数一次
		  Temp_Count ++;                                                             
		  flag = 0;
	  }
		
		// 在线前提前减速
		if ((Seven_Read(left, 3) == high) || (Seven_Read(right, 3)) == high) {        // 中间的前一个灰度数到线时先减速
		  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
      Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
			Delay(250);
	  }
		
		// 在线前转正
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // 左侧中间的先检测到线
		  while(1){
			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
				if(Seven_Read(right, 4) == high) break;
			}
	  }
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // 右侧中间的先检测到线
		  while(1){
			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
				if(Seven_Read(left, 4) == high) break;
			}
	  }
		
		// 数到对应的根数退出循环
		if (Temp_Count >= Line_Count) {
		  Stop_Forward();
			return;
	  }
		
		Delay(10);
		LCD_Printn(1, Temp_Count);                                 // 显示已经数了几根线
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
														 
	  PID();                                                   // 开始PID循线
		Delay(50);
	}
}


// 巡线后退 n 根线（前七路数线）。在从基地出发时左转前使用
void Back_Front(int Line_Count) {            
  int Temp_Count = 0;                     // 当前所在线数
	int flag = 0;                           // 开始计数标志
	
//	// 先转一段，跨过黑线
	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
	Delay(750);
	
	while (1) {
    if (Seven_Read(left, 4) == low) {                          // 检测到黑色，开启计数准备
	    flag = 1;
	  }
		flag = 1;
	  if ((flag == 1) && 
			  (((Seven_Read(front, 2) == high) && (Seven_Read(front, 6)) == high) || 
			  ((Seven_Read(front, 1) == high) && (Seven_Read(front, 7)) == high))){     // 由黑色变为白色，计数一次
		  Temp_Count ++;                                                             
		  flag = 0;
	  }
		
		// 在线前提前减速
		if ((Seven_Read(left, 5) == high) || (Seven_Read(right, 5)) == high) {        // 中间的前一个灰度数到线时先减速
		  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow-5);
      Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow-5);
			Delay(250);
	  }
		
		// 在线前转正
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // 左侧中间的先检测到线
		  while(1){
			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
				if(Seven_Read(right, 4) == high) break;
			}
	  }
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // 右侧中间的先检测到线
		  while(1){
			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
				if(Seven_Read(left, 4) == high) break;
			}
	  }
		
		// 数到对应的根数退出循环
		if (Temp_Count >= Line_Count) {
		  Stop_Forward();
			return;
	  }
		
		Delay(10);
		LCD_Printn(1, Temp_Count);                                 // 显示已经数了几根线
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
														 
	  PIDBack();                                                   // 开始PID循线
		Delay(50);
	}
}


// 巡线前进 n 根线（后七路数线）。在一侧货架走完，撞墙后后退时使用
void Front_Back(int Line_Count) {            
  int Temp_Count = 0;                     // 当前所在线数
	int flag = 0;                           // 开始计数标志
	
//	// 先转一段，跨过黑线
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
	Delay(750);
	
	while (1) {
    if (Seven_Read(left, 4) == low) {                          // 检测到黑色，开启计数准备
	    flag = 1;
	  }
	  if ((flag == 1) && 
			  (((Seven_Read(back, 2) == high) && (Seven_Read(back, 6)) == high) || 
			  ((Seven_Read(back, 1) == high) && (Seven_Read(back, 7)) == high))){     // 由黑色变为白色，计数一次
		  Temp_Count ++;                                                             
		  flag = 0;
	  }
		
		// 在线前提前减速
		if ((Seven_Read(left, 1) == high) || (Seven_Read(right, 1)) == high) {        // 中间的前一个灰度数到线时先减速
		  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
      Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
	  }
		
//		// 在线前转正
//		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // 左侧中间的先检测到线
//		  while(1){
//			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//				if(Seven_Read(right, 4) == high) break;
//			}
//	  }
//		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // 右侧中间的先检测到线
//		  while(1){
//			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//				if(Seven_Read(left, 4) == high) break;
//			}
//	  }
		
		// 在线前转正
		// 左侧中间的先检测到线
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) { 
			// 如果右侧灰度前半部分检测到白线，说明右轮应该向前
			if ((Seven_Read(right, 7) == high) || (Seven_Read(right, 6) == high) || (Seven_Read(right, 5) == high)){
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
					Set_Speed(LEFTWHEEL_PWM_OUT, 0);
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
						correct_count = 0;
					}
//					if(Seven_Read(right, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
			}
			// 如果右侧灰度后半部分检测到白线，说明右轮应该向后
			else if ((Seven_Read(right, 3) == high) || (Seven_Read(right, 2) == high) || (Seven_Read(right, 1) == high)) {
				while(1){
					Set_Speed(LEFTWHEEL_PWM_OUT, 0);
					Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
					GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // 右轮向后转
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
						correct_count = 0;
					}
//					if(Seven_Read(right, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
			}
	  }
		// 右侧中间的先检测到线
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) { 
			// 如果左侧灰度前半部分检测到白线，说明左轮应该向前
			if ((Seven_Read(left, 1 == high) || (Seven_Read(left, 2) == high) || (Seven_Read(left, 3) == high))){
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
					Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
					}
//					if(Seven_Read(left, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
				correct_count = 0;
			}
			// 如果左侧灰度后半部分检测到白线，说明左轮应该向后
			else if ((Seven_Read(left, 5) == high) || (Seven_Read(left, 6) == high) || (Seven_Read(left, 7) == high)) {
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
					Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
					GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);    // 左轮向后转
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
					}
//					if(Seven_Read(left, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
				correct_count = 0;
			}
	  }
		
		// 数到对应的根数退出循环
		if (Temp_Count >= Line_Count) {
		  Stop_Back();
			return;
	  }
		
		Delay(10);
		LCD_Printn(1, Temp_Count);                                 // 显示已经数了几根线
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
														 
	  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right-11);
		Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left-10);
		GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // 左轮 High ，右轮 Low 向前；左轮 Low ，右轮 High 向后
		GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		Delay(50);
	}
}


// 停止
void Stop_Forward(void) 
{
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
	Delay(300);
  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
}

// 停止
void Stop_Back(void) 
{
	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
	Delay(300);
  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
}

// 停止
void Stop_Left(void) 
{
//	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed - PreSlow);
//  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed - PreSlow);
//	Delay(50);
  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
}

// 停止
void Stop_Right(void) 
{
//	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed - PreSlow);
//  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed - PreSlow);
//	Delay(50);
  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
}


// 左转
void Left(void)
{
	int flag = 0;                                                 // 开始转向检测标志
	
	// 先转一段，跨过黑线
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始左转
  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed);
  Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed);
	Delay(1500);
	
	while (1) {
		// 检测到白色，开启计数准备
		if ((GPIO_Read(LEFTSEVEN4_GPIO_PORT, LEFTSEVEN4_GPIO_PIN) == low) && (GPIO_Read(RIGHTSEVEN4_GPIO_PORT, RIGHTSEVEN4_GPIO_PIN) == low)) {            
			flag = 1;
		}
		
		// 在线前转正
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // 左侧中间的先检测到线
		  while(1){
			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
				if(Seven_Read(right, 4) == high) break;
			}
	  }
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // 右侧中间的先检测到线
		  while(1){
			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
				if(Seven_Read(left, 4) == high) break;
			}
	  }
		
		// 由白色变为黑色，转向到位，退出转向
		if ((flag == 1) && ((GPIO_Read(LEFTSEVEN4_GPIO_PORT, LEFTSEVEN4_GPIO_PIN) == high) && (GPIO_Read(RIGHTSEVEN4_GPIO_PORT, RIGHTSEVEN4_GPIO_PIN) == high))) {
			GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);      // 再继续左转一定延时
      GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed-15);
      Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed-15);
			Delay(240);
			Stop_Left();
			return;
		}
		
		GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始左转
    GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed);
    Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed);
	}   
} 


// 右转
void Right(void)
{
	int flag = 0;                                                  // 开始转向检测标志
	
	// 先转一段，跨过黑线
	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始右转
	GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
	Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed);
	Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed);
	Delay(1500);
	
	while (1) {
		// 检测到白色，开启计数准备
		if ((GPIO_Read(LEFTSEVEN4_GPIO_PORT, LEFTSEVEN4_GPIO_PIN) == low) && (GPIO_Read(RIGHTSEVEN4_GPIO_PORT, RIGHTSEVEN4_GPIO_PIN) == low)) {          
			flag = 1;
		}
		
		// 在线前转正
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // 左侧中间的先检测到线
		  while(1){
			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
				if(Seven_Read(right, 4) == high) break;
			}
	  }
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // 右侧中间的先检测到线
		  while(1){
			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
				if(Seven_Read(left, 4) == high) break;
			}
	  }
		
		// 由白色变为黑色，转向到位，退出转向
		if ((flag == 1) && ((GPIO_Read(LEFTSEVEN4_GPIO_PORT, LEFTSEVEN4_GPIO_PIN) == high) && (GPIO_Read(RIGHTSEVEN4_GPIO_PORT, RIGHTSEVEN4_GPIO_PIN) == high))) {
      GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);     // 再继续右转一定延时
      GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed-15);
      Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed-15);
			Delay(240);
			Stop_Right();
			return;
		}
		
		GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始右转
		GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed);
		Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed);
	}
}


// 利用MPU6050左转
void Left_MPU(int angle)
{
	angle = angle - 3;      // 补偿角度，少转1度
	char cStr [ 70 ];
  int target_angle;
	target_angle = Angle[2] + angle + 1;
	SysTick_Init();                                     // 重新初始化systick，防止被delay功能干扰
	
  while(1){	
		MPU6050_ReadAngle(Angle, 0);
		if(Angle[2] < target_angle){
			GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);       // 开始左转
      GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, MPUTurningSpeed-3);
      Set_Speed(LEFTWHEEL_PWM_OUT, MPUTurningSpeed+1);
		}
		else{
			Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
      Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//			Angle[2] = 0;                                 // 初始化转向角
			return;
		}
		
		sprintf (cStr, "Left Gyro:  %8d", Angle[2]);	  // Z轴旋转角度数据
		ILI9341_DispStringLine_EN(LINE(5),cStr); 	
	}
}


// 利用MPU6050右转
void Right_MPU(int angle)
{
	angle = angle - 2;      // 补偿角度，少转1度
	char cStr [ 70 ];
	int target_angle;
	target_angle = Angle[2] - angle - 1;
	task_readdata_finish = 0;
	SysTick_Init();                                       // 重新初始化systick，防止被delay功能干扰
	
  while(1){	
		MPU6050_ReadAngle(Angle, 0);
		if(Angle[2] > target_angle){
			GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);       // 开始右转
      GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, MPUTurningSpeed-3);
      Set_Speed(LEFTWHEEL_PWM_OUT, MPUTurningSpeed+1);
		}
		else{
			Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
      Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//			Angle[2] = 0;                                 // 初始化转向角
			return;
		}
		
		sprintf (cStr, "Right Gyro: %8d", Angle[2]);	  // Z轴旋转角度数据
		ILI9341_DispStringLine_EN(LINE(5),cStr); 	
	}
}


// 利用MPU6050转到特定角度
void TrunTo_MPU(int angle)
{
	char cStr [ 70 ];
	SysTick_Init();                                     // 重新初始化systick，防止被delay功能干扰
	
  while(1){	
		MPU6050_ReadAngle(Angle, 0);
		if(Angle[2] < angle){                             // 如果当前角度小于目标角，则继续左转
			GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);       // 开始左转
      GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, MPUTurningSpeed-3);
      Set_Speed(LEFTWHEEL_PWM_OUT, MPUTurningSpeed+1);
		}
		else if(Angle[2] > angle){                        // 如果当前角度大于目标角，则继续右转
			GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);       // 开始右转
      GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, MPUTurningSpeed-3);
      Set_Speed(LEFTWHEEL_PWM_OUT, MPUTurningSpeed+1);
		}
		else{
			Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
      Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//			Angle[2] = 0;                                 // 初始化转向角
			return;
		}
		
		sprintf (cStr, "Left Gyro:  %8d", Angle[2]);	  // Z轴旋转角度数据
		ILI9341_DispStringLine_EN(LINE(5),cStr); 	
	}
}


// PID 巡线
void PID(void)
{
	GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);          // 打开蓝灯，表示正在PID巡线
  GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
	GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
	
	static int sensor[7];
	static double error = 0;
	static double P = 0, I = 0, D = 0;
	static double Kp = KP, Ki = KI, Kd = KD;         // PID 系数
	static double PID_value;
	static int previous_error = 0;
	
  sensor[0] = GPIO_Read(FRONTSEVEN1_GPIO_PORT, FRONTSEVEN1_GPIO_PIN);
	sensor[1] = GPIO_Read(FRONTSEVEN2_GPIO_PORT, FRONTSEVEN2_GPIO_PIN);
	sensor[2] = GPIO_Read(FRONTSEVEN3_GPIO_PORT, FRONTSEVEN3_GPIO_PIN);
	sensor[3] = GPIO_Read(FRONTSEVEN4_GPIO_PORT, FRONTSEVEN4_GPIO_PIN);
	sensor[4] = GPIO_Read(FRONTSEVEN5_GPIO_PORT, FRONTSEVEN5_GPIO_PIN);
	sensor[5] = GPIO_Read(FRONTSEVEN6_GPIO_PORT, FRONTSEVEN6_GPIO_PIN);
	sensor[6] = GPIO_Read(FRONTSEVEN7_GPIO_PORT, FRONTSEVEN7_GPIO_PIN);
	
//	if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == high) {
//		error = 6;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == high && sensor[6] == high) {
//		error = 5;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == high && sensor[6] == low) {
//		error = 4;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == high && sensor[5] == high && sensor[6] == low) {
//		error = 3;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == high && sensor[5] == low && sensor[6] == low) {
//		error = 2;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == high && sensor[4] == high && sensor[5] == low && sensor[6] == low) {
//		error = 1;
//	}
//	else if ((sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == high && sensor[4] == low && sensor[5] == low && sensor[6] == low) ||
//		       (sensor[0] == high && sensor[1] == high && sensor[2] == high && sensor[3] == high && sensor[4] == high && sensor[5] == high && sensor[6] == high)) {
//		error = 0;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == high && sensor[3] == high && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -1;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == high && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -2;
//	}
//	else if (sensor[0] == low && sensor[1] == high && sensor[2] == high && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -3;
//	}
//	else if (sensor[0] == low && sensor[1] == high && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -4;
//	}
//	else if (sensor[0] == high && sensor[1] == high && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -5;
//	}
//	else if (sensor[0] == high && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -6;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		if (previous_error == -6) {
//			error = -7;
//		}
//		else if(previous_error == 6){
//			error = 7;
//		}
//		else{
//		  error = 0;
//		}
//	}

	static int switch_value = 0;
	switch_value = 1 * sensor[0] + 3 * sensor[1] + 5 * sensor[2] + 7 * sensor[3] + 9 * sensor[4] + 11 * sensor[5] + 13 * sensor[6];
	switch (switch_value) {
		case 48:error = -3.5; break;
		case 45:error = -3; break;
		case 40:error = -2.5; break;
		case 41:error = -2; break;
		case 34:error = -1.5; break;
		case 37:error = -1; break;
		case 28:error = -0; break;
		case 33:error = 1; break;
		case 22:error = 1.5; break;
		case 29:error = 2; break;
		case 16:error = 2.5; break;
		case 25:error = 3; break;
		case 36:error = 3.5; break;
		case 49:if (error == 3) error = 3.5;
					  else if (error == -3) error = -3.5;
						else error = 0;
					  break;
		default:error = 0;break;
	}
	
	P = error;
	I = I + error;
	D = error - previous_error;
	PID_value = Kp * P + Ki * I + Kd * D;
	previous_error = error;
	
	Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right + PID_value);
	Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PID_value);
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // 左轮 High ，右轮 Low 向前；左轮 Low ，右轮 High 向后
	GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
}


// 伸出滑轨
void SlideOut(void)
{
  GPIO_Low(SLIDE_GPIO_PORT, SLIDE_GPIO_PIN);              // 滑轨 Low 向前，High 向后
	Set_Speed(SLIDE_PWM, 80);
	SysTick_Delay_ms(1900);
	Set_Speed(SLIDE_PWM, 0);
}


// 收回滑轨
void SlideIn(void)
{
  GPIO_High(SLIDE_GPIO_PORT, SLIDE_GPIO_PIN);              // 滑轨 Low 向前，High 向后
	Set_Speed(SLIDE_PWM, 80);
	SysTick_Delay_ms(1900);
	Set_Speed(SLIDE_PWM, 0);
}


// 完成一次抓取
void Catch(void)
{
	MoveSrv7(1);                   // 上层臂抬起
	MoveSrv15(0);                  // 翻斗放下
	Delay(500);
	
	MoveSrv1(1);                   // 抓臂伸出
	MoveSrv2(1);
	MoveSrv3(1);
	MoveSrv4(1);
	MoveSrv5(1);
	MoveSrv6(1);
	Delay(500);
	
	SlideOut();                    // 滑轨伸出    
	Delay(1500);
	
	MoveSrv1(0);                   // 抓臂收回
	MoveSrv2(0);
	MoveSrv3(0);
	MoveSrv4(0);
	MoveSrv5(0);
	MoveSrv6(0);
	Set_Speed(TRACK_PWM, 128);     // 履带开始运动
	Delay(1000);
	
	MoveSrv7(0);                   // 上层臂放下 
	MoveSrv15(1);                  // 翻斗抬起
	Delay(500);
	
	Set_Speed(TRACK_PWM, 0);       // 履带停止运动
	SlideIn();                     // 滑轨收回
}


// 倒着巡线直行 n 根线。形参1为数线数量
void Back(int Line_Count) {            
  int Temp_Count = 0;                     // 当前所在线数
	int flag = 0;                           // 开始计数标志
	
	// 先转一段，跨过黑线
	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
	Delay(750);
	
	while (1) {
//		Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
//		Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
//		
    if (Seven_Read(left, 4) == low) {                          // 检测到黑色，开启计数准备
	    flag = 1;
	  }
	  if ((flag == 1) && (Seven_Read(left, 4) == high)) {        // 由黑色变为白色，计数一次
		  Temp_Count ++;     
			if(Temp_Count < Line_Count){
				// 先转一段，跨过黑线
				GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
				GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
				Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
				Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
				Delay(100);
			}
		  flag = 0;
	  }
		
		// 在线前提前减速
		if ((Seven_Read(left, 7) == high) || (Seven_Read(right, 7)) == high) {        // 中间的前一个灰度数到线时先减速
		  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
      Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
	  }
		
//		// 在线前转正
//		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // 左侧中间的先检测到线
//		  while(1){
//			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//				if(Seven_Read(right, 4) == high) break;
//			}
//	  }
//		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // 右侧中间的先检测到线
//		  while(1){
//			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//				if(Seven_Read(left, 4) == high) break;
//			}
//	  }
		
		// 在线前转正
		// 左侧中间的先检测到线
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) { 
			// 如果右侧灰度前半部分检测到白线，说明右轮应该向前
			if ((Seven_Read(right, 1) == high) || (Seven_Read(right, 2) == high) || (Seven_Read(right, 3) == high)){
				while(1){
					Set_Speed(LEFTWHEEL_PWM_OUT, 0);
					Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
					}
//					if(Seven_Read(right, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
				correct_count = 0;
			}
			// 如果右侧灰度后半部分检测到白线，说明右轮应该向后
			else if ((Seven_Read(right, 5) == high) || (Seven_Read(right, 6) == high) || (Seven_Read(right, 7) == high)) {
				while(1){
					Set_Speed(LEFTWHEEL_PWM_OUT, 0);
					Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
					GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // 右轮向后转
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
					}
//					if(Seven_Read(right, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
				correct_count = 0;
			}
	  }
		// 右侧中间的先检测到线
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) { 
			// 如果左侧灰度前半部分检测到白线，说明左轮应该向前
			if ((Seven_Read(left, 5 == high) || (Seven_Read(left, 6) == high) || (Seven_Read(left, 7) == high))){
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
					Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
						correct_count = 0;
					}
//					if(Seven_Read(left, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
			}
			// 如果左侧灰度后半部分检测到白线，说明左轮应该向后
			else if ((Seven_Read(left, 1) == high) || (Seven_Read(left, 2) == high) || (Seven_Read(left, 3) == high)) {
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
					Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
					GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);    // 左轮向后转
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
						correct_count = 0;
					}
//					if(Seven_Read(left, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
			}
	  }
		
		// 数到对应的根数退出循环
		if (Temp_Count >= Line_Count) {
		  Stop_Back();
			return;
	  }
		
		Delay(20);
//	  LCD_Printn(1, Temp_Count);                                 // 显示已经数了几根线
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
														 
	  PIDBack();                                                   // 开始PID循线
		Delay(50);
	}
}


// 倒着 PID 巡线
void PIDBack(void)
{
	GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);          // 打开蓝灯，表示正在PID巡线
  GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
	GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
	
	static int sensor[7];
	static double error = 0;
	static double P = 0, I = 0, D = 0;
	static double Kp = KP, Ki = KI, Kd = KD;         // PID 系数
	static double PID_value;
	static int previous_error = 0;
	
  sensor[6] = GPIO_Read(BACKSEVEN1_GPIO_PORT, BACKSEVEN1_GPIO_PIN);
	sensor[5] = GPIO_Read(BACKSEVEN2_GPIO_PORT, BACKSEVEN2_GPIO_PIN);
	sensor[4] = GPIO_Read(BACKSEVEN3_GPIO_PORT, BACKSEVEN3_GPIO_PIN);
	sensor[3] = GPIO_Read(BACKSEVEN4_GPIO_PORT, BACKSEVEN4_GPIO_PIN);
	sensor[2] = GPIO_Read(BACKSEVEN5_GPIO_PORT, BACKSEVEN5_GPIO_PIN);
	sensor[1] = GPIO_Read(BACKSEVEN6_GPIO_PORT, BACKSEVEN6_GPIO_PIN);
	sensor[0] = GPIO_Read(BACKSEVEN7_GPIO_PORT, BACKSEVEN7_GPIO_PIN);
	
//	if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == high) {
//		error = 6;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == high && sensor[6] == high) {
//		error = 5;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == high && sensor[6] == low) {
//		error = 4;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == high && sensor[5] == high && sensor[6] == low) {
//		error = 3;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == high && sensor[5] == low && sensor[6] == low) {
//		error = 2;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == high && sensor[4] == high && sensor[5] == low && sensor[6] == low) {
//		error = 1;
//	}
//	else if ((sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == high && sensor[4] == low && sensor[5] == low && sensor[6] == low) ||
//		       (sensor[0] == high && sensor[1] == high && sensor[2] == high && sensor[3] == high && sensor[4] == high && sensor[5] == high && sensor[6] == high)) {
//		error = 0;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == high && sensor[3] == high && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -1;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == high && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -2;
//	}
//	else if (sensor[0] == low && sensor[1] == high && sensor[2] == high && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -3;
//	}
//	else if (sensor[0] == low && sensor[1] == high && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -4;
//	}
//	else if (sensor[0] == high && sensor[1] == high && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -5;
//	}
//	else if (sensor[0] == high && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		error = -6;
//	}
//	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
//		if (previous_error == -6) {
//			error = -7;
//		}
//		else if(previous_error == 6){
//			error = 7;
//		}
//		else{
//		  error = 0;
//		}
//	}

	static int switch_value = 0;
	switch_value = 1 * sensor[0] + 3 * sensor[1] + 5 * sensor[2] + 7 * sensor[3] + 9 * sensor[4] + 11 * sensor[5] + 13 * sensor[6];
	switch (switch_value) {
		case 48:error = -3.5; break;
		case 45:error = -3; break;
		case 40:error = -2.5; break;
		case 41:error = -2; break;
		case 34:error = -1.5; break;
		case 37:error = -1; break;
		case 28:error = -0; break;
		case 33:error = 1; break;
		case 22:error = 1.5; break;
		case 29:error = 2; break;
		case 16:error = 2.5; break;
		case 25:error = 3; break;
		case 36:error = 3.5; break;
		case 49:if (error == 6)error = 7;
					  else error = -7;
					  break;
		default:break;
	}
	
	P = error;
	I = I + error;
	D = error - previous_error;
	PID_value = Kp * P + Ki * I + Kd * D;
	previous_error = error;
	
	Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right + PID_value);
	Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PID_value);
	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // 左轮 High ，右轮 Low 向前；左轮 Low ，右轮 High 向后
	GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
}


// 倒着巡线直行 n 根线。形参1为数线数量
void Back_Slide(int Line_Count) {            
  int Temp_Count = 0;                     // 当前所在线数
	int flag = 0;                           // 开始计数标志
	
	// 先转一段，跨过黑线
	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left);
	Delay(750);
	
	while (1) {
//		Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
//		Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
//		
    if (Seven_Read(left, 4) == low) {                          // 检测到黑色，开启计数准备
	    flag = 1;
	  }
	  if ((flag == 1) && (Seven_Read(left, 4) == high)) {        // 由黑色变为白色，计数一次
		  Temp_Count ++;     
			if(Temp_Count < Line_Count){
				// 先转一段，跨过黑线
				GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
				GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
				Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
				Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
				Delay(100);
			}
		  flag = 0;
	  }
		
		// 在线前提前减速
		if ((Seven_Read(left, 7) == high) || (Seven_Read(right, 7)) == high) {        // 中间的前一个灰度数到线时先减速
		  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right - PreSlow);
      Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left - PreSlow);
	  }
		
//		// 在线前转正
//		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // 左侧中间的先检测到线
//		  while(1){
//			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//				if(Seven_Read(right, 4) == high) break;
//			}
//	  }
//		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // 右侧中间的先检测到线
//		  while(1){
//			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//				if(Seven_Read(left, 4) == high) break;
//			}
//	  }
		
		// 在线前转正
		// 左侧中间的先检测到线
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) { 
			// 如果右侧灰度前半部分检测到白线，说明右轮应该向前
			if ((Seven_Read(right, 1) == high) || (Seven_Read(right, 2) == high) || (Seven_Read(right, 3) == high)){
				while(1){
					Set_Speed(LEFTWHEEL_PWM_OUT, 0);
					Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
					}
//					if(Seven_Read(right, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
				correct_count = 0;
			}
			// 如果右侧灰度后半部分检测到白线，说明右轮应该向后
			else if ((Seven_Read(right, 5) == high) || (Seven_Read(right, 6) == high) || (Seven_Read(right, 7) == high)) {
				while(1){
					Set_Speed(LEFTWHEEL_PWM_OUT, 0);
					Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
					GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // 右轮向后转
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
					}
//					if(Seven_Read(right, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
				correct_count = 0;
			}
	  }
		// 右侧中间的先检测到线
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) { 
			// 如果左侧灰度前半部分检测到白线，说明左轮应该向前
			if ((Seven_Read(left, 5 == high) || (Seven_Read(left, 6) == high) || (Seven_Read(left, 7) == high))){
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
					Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
						correct_count = 0;
					}
//					if(Seven_Read(left, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
			}
			// 如果左侧灰度后半部分检测到白线，说明左轮应该向后
			else if ((Seven_Read(left, 1) == high) || (Seven_Read(left, 2) == high) || (Seven_Read(left, 3) == high)) {
				while(1){
					Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
					Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
					GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);    // 左轮向后转
					correct_count ++;
					if(correct_count > 2){    // 如果校准次数超过2次，则退出校准
						break;
						correct_count = 0;
					}
//					if(Seven_Read(left, 4) == high){
//						Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
//						// 先转一段，跨过黑线
//						GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // 开始直走
//						GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
//						Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed - PreSlow);
//						Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed - PreSlow);
//						Delay(200);
//						break;
//					}
				}
			}
	  }
		
		// 数到对应的根数退出循环
		if (Temp_Count >= Line_Count) {
		  Stop_Back();
			return;
	  }
		
		Delay(20);
//	  LCD_Printn(1, Temp_Count);                                 // 显示已经数了几根线
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
														 
	  PID_grab();                                                   // 开始PID循线
		Delay(50);
	}
}

// 用侧面三灰度 PID 巡线
void PID_grab(void)
{
	GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);          
  GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
	GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
	
	static int sensor_grab[3];
	static double error_grab = 0;
	static double P_grab = 0, I_grab = 0, D_grab = 0;
	static double Kp_grab = KP_grab, Ki_grab = KI_grab, Kd_grab = KD_grab;         
	static double PID_value_grab;
	static int previous_error_grab = 0;
	
  sensor_grab[0] = GPIO_Read(GRABTHREE1_GPIO_PORT, GRABTHREE1_GPIO_PIN);     //对新的灰度进行命名 
	sensor_grab[1] = GPIO_Read(GRABTHREE2_GPIO_PORT, GRABTHREE2_GPIO_PIN);
	sensor_grab[2] = GPIO_Read(GRABTHREE3_GPIO_PORT, GRABTHREE3_GPIO_PIN);
	static int switch_value_grab = 0;
	switch_value_grab = 1 * sensor_grab[0] + 3 * sensor_grab[1] + 5 * sensor_grab[2];
	switch (switch_value_grab) {
		case 8:error_grab = -1.4; break;
		case 5:error_grab = -0.8; break;
		case 0:error_grab = 0; break;
		case 1:error_grab = 0.8; break;
		case 4:error_grab = 1.4; break;
		
		case 9:if (error_grab == 1.4) error_grab = 1.5;
					  else if (error_grab == -1.4) error_grab = -1.5;
						else error_grab = 0;
					  break;
		default:error_grab = 0;break;
	}
	
	P_grab = error_grab;
	I_grab = I_grab + error_grab;
	D_grab = error_grab - previous_error_grab;
	PID_value_grab = Kp_grab * P_grab + Ki_grab * I_grab + Kd_grab * D_grab;
	previous_error_grab = error_grab;
	
	Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed_Right -5 + PID_value_grab);
	Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed_Left -5 - 0.6*PID_value_grab);    //左轮转动影响较大，速度变化不能过大 
	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    
	GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
}
