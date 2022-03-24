/*----------ǰ������ת90�ȣ���ת90�ȣ�ֹͣ---------*/      

#include "Move.h"

#include <stdio.h>
#include <stdlib.h>   


// Ѳ��ֱ�� n ���ߡ��β�1Ϊ��������
void Forward(int Line_Count) {            
  int Temp_Count = 0;                     // ��ǰ��������
	int flag = 0;                           // ��ʼ������־
	
//	// ��תһ�Σ��������
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼֱ��
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
	Delay(750);
	
	while (1) {
    if (Seven_Read(left, 4) == low) {                          // ��⵽��ɫ����������׼��
	    flag = 1;
	  }
	  if ((flag == 1) && (Seven_Read(left, 4) == high)) {        // �ɺ�ɫ��Ϊ��ɫ������һ��
		  Temp_Count ++;                                                             
		  flag = 0;
	  }
		
		// ����ǰ��ǰ����
		if ((Seven_Read(left, 3) == high) || (Seven_Read(right, 3)) == high) {        // �м��ǰһ���Ҷ�������ʱ�ȼ���
		  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed - PreSlow);
      Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed - PreSlow);
			Delay(250);
	  }
		
		// ����ǰת��
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // ����м���ȼ�⵽��
		  while(1){
			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
				if(Seven_Read(right, 4) == high) break;
			}
	  }
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // �Ҳ��м���ȼ�⵽��
		  while(1){
			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
				if(Seven_Read(left, 4) == high) break;
			}
	  }
		
		// ������Ӧ�ĸ����˳�ѭ��
		if (Temp_Count >= Line_Count) {
		  Stop();
			return;
	  }
		
		LCD_Printn(1, Temp_Count);                                 // ��ʾ�Ѿ����˼�����
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
														 
	  PID();                                                   // ��ʼPIDѭ��
	}
}


// Ѳ��ֱ�� n ���ߣ�ǰ��·���ߣ���
void Forward_Front(int Line_Count) {            
  int Temp_Count = 0;                     // ��ǰ��������
	int flag = 0;                           // ��ʼ������־
	
//	// ��תһ�Σ��������
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼֱ��
  GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed);
  Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed);
	Delay(750);
	
	while (1) {
    if (Seven_Read(left, 4) == low) {                          // ��⵽��ɫ����������׼��
	    flag = 1;
	  }
	  if ((flag == 1) && (Seven_Read(front, 2) == high) && (Seven_Read(front, 5) == high)){        // �ɺ�ɫ��Ϊ��ɫ������һ��
		  Temp_Count ++;                                                             
		  flag = 0;
	  }
		
		// ����ǰ��ǰ����
		if ((Seven_Read(left, 3) == high) || (Seven_Read(right, 3)) == high) {        // �м��ǰһ���Ҷ�������ʱ�ȼ���
		  Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed - PreSlow);
      Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed - PreSlow);
			Delay(250);
	  }
		
		// ����ǰת��
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // ����м���ȼ�⵽��
		  while(1){
			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
				if(Seven_Read(right, 4) == high) break;
			}
	  }
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // �Ҳ��м���ȼ�⵽��
		  while(1){
			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
				if(Seven_Read(left, 4) == high) break;
			}
	  }
		
		// ������Ӧ�ĸ����˳�ѭ��
		if (Temp_Count >= Line_Count) {
		  Stop();
			return;
	  }
		
		LCD_Printn(1, Temp_Count);                                 // ��ʾ�Ѿ����˼�����
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
														 
	  PID();                                                   // ��ʼPIDѭ��
	}
}


// ֹͣ
void Stop(void) 
{
  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
}


// ��ת
void Left(void)
{
	int flag = 0;                                                 // ��ʼת�����־
	
	// ��תһ�Σ��������
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼ��ת
  GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
  Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed);
  Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed);
	Delay(1500);
	
	while (1) {
		// ��⵽��ɫ����������׼��
		if ((GPIO_Read(LEFTSEVEN4_GPIO_PORT, LEFTSEVEN4_GPIO_PIN) == low) && (GPIO_Read(RIGHTSEVEN4_GPIO_PORT, RIGHTSEVEN4_GPIO_PIN) == low)) {            
			flag = 1;
		}
		
		// ����ǰת��
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // ����м���ȼ�⵽��
		  while(1){
			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
				if(Seven_Read(right, 4) == high) break;
			}
	  }
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // �Ҳ��м���ȼ�⵽��
		  while(1){
			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
				if(Seven_Read(left, 4) == high) break;
			}
	  }
		
		// �ɰ�ɫ��Ϊ��ɫ��ת��λ���˳�ת��
		if ((flag == 1) && ((GPIO_Read(LEFTSEVEN4_GPIO_PORT, LEFTSEVEN4_GPIO_PIN) == high) && (GPIO_Read(RIGHTSEVEN4_GPIO_PORT, RIGHTSEVEN4_GPIO_PIN) == high))) {
			GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);      // �ټ�����תһ����ʱ
      GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed-15);
      Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed-15);
			Delay(240);
			Stop();
			return;
		}
		
		GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼ��ת
    GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed);
    Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed);
	}   
} 


// ��ת
void Right(void)
{
	int flag = 0;                                                  // ��ʼת�����־
	
	// ��תһ�Σ��������
	GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼ��ת
	GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
	Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed);
	Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed);
	Delay(1500);
	
	while (1) {
		// ��⵽��ɫ����������׼��
		if ((GPIO_Read(LEFTSEVEN4_GPIO_PORT, LEFTSEVEN4_GPIO_PIN) == low) && (GPIO_Read(RIGHTSEVEN4_GPIO_PORT, RIGHTSEVEN4_GPIO_PIN) == low)) {          
			flag = 1;
		}
		
		// ����ǰת��
		if ((Seven_Read(left, 4) == high) && (Seven_Read(right, 4) == low)) {       // ����м���ȼ�⵽��
		  while(1){
			  Set_Speed(LEFTWHEEL_PWM_OUT, 0);
				if(Seven_Read(right, 4) == high) break;
			}
	  }
		else if ((Seven_Read(left, 4) == low) && (Seven_Read(right, 4) == high)) {  // �Ҳ��м���ȼ�⵽��
		  while(1){
			  Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
				if(Seven_Read(left, 4) == high) break;
			}
	  }
		
		// �ɰ�ɫ��Ϊ��ɫ��ת��λ���˳�ת��
		if ((flag == 1) && ((GPIO_Read(LEFTSEVEN4_GPIO_PORT, LEFTSEVEN4_GPIO_PIN) == high) && (GPIO_Read(RIGHTSEVEN4_GPIO_PORT, RIGHTSEVEN4_GPIO_PIN) == high))) {
      GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);     // �ټ�����תһ����ʱ
      GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed-15);
      Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed-15);
			Delay(240);
			Stop();
			return;
		}
		
		GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);        // ��ʼ��ת
		GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		Set_Speed(RIGHTWHEEL_PWM_OUT, RightTruningSpeed);
		Set_Speed(LEFTWHEEL_PWM_OUT, LeftTruningSpeed);
	}
}


// ����MPU6050��ת
void Left_MPU(int angle)
{
	char cStr [ 70 ];
  int target_angle;
	target_angle = Angle[2] + angle + 1;
	SysTick_Init();                                     // ���³�ʼ��systick����ֹ��delay���ܸ���
	
  while(1){	
		MPU6050_ReadAngle(Angle, 0);
		if(Angle[2] < target_angle){
			GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);       // ��ʼ��ת
      GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, MPUTurningSpeed);
      Set_Speed(LEFTWHEEL_PWM_OUT, MPUTurningSpeed);
		}
		else{
			Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
      Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//			Angle[2] = 0;                                 // ��ʼ��ת���
			return;
		}
		
		sprintf (cStr, "Left Gyro:  %8d", Angle[2]);	  // Z����ת�Ƕ�����
		ILI9341_DispStringLine_EN(LINE(5),cStr); 	
	}
}


// ����MPU6050��ת
void Right_MPU(int angle)
{
	char cStr [ 70 ];
	int target_angle;
	target_angle = Angle[2] - angle - 1;
	task_readdata_finish = 0;
	SysTick_Init();                                     // ���³�ʼ��systick����ֹ��delay���ܸ���
	
  while(1){	
		MPU6050_ReadAngle(Angle, 0);
		if(Angle[2] > target_angle){
			GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);       // ��ʼ��ת
      GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, MPUTurningSpeed);
      Set_Speed(LEFTWHEEL_PWM_OUT, MPUTurningSpeed);
		}
		else{
			Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
      Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//			Angle[2] = 0;                                 // ��ʼ��ת���
			return;
		}
		
		sprintf (cStr, "Right Gyro: %8d", Angle[2]);	  // Z����ת�Ƕ�����
		ILI9341_DispStringLine_EN(LINE(5),cStr); 	
	}
}


// ����MPU6050ת���ض��Ƕ�
void TrunTo_MPU(int angle)
{
	char cStr [ 70 ];
	SysTick_Init();                                     // ���³�ʼ��systick����ֹ��delay���ܸ���
	
  while(1){	
		MPU6050_ReadAngle(Angle, 0);
		if(Angle[2] < angle){                             // �����ǰ�Ƕ�С��Ŀ��ǣ��������ת
			GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);       // ��ʼ��ת
      GPIO_Low(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, MPUTurningSpeed);
      Set_Speed(LEFTWHEEL_PWM_OUT, MPUTurningSpeed);
		}
		else if(Angle[2] > angle){                        // �����ǰ�Ƕȴ���Ŀ��ǣ��������ת
			GPIO_High(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);       // ��ʼ��ת
      GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
		  Set_Speed(RIGHTWHEEL_PWM_OUT, MPUTurningSpeed);
      Set_Speed(LEFTWHEEL_PWM_OUT, MPUTurningSpeed);
		}
		else{
			Set_Speed(RIGHTWHEEL_PWM_OUT, 0);
      Set_Speed(LEFTWHEEL_PWM_OUT, 0);
//			Angle[2] = 0;                                 // ��ʼ��ת���
			return;
		}
		
		sprintf (cStr, "Left Gyro:  %8d", Angle[2]);	  // Z����ת�Ƕ�����
		ILI9341_DispStringLine_EN(LINE(5),cStr); 	
	}
}


// PID Ѳ��
void PID(void)
{
	GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);          // �����ƣ���ʾ����PIDѲ��
  GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
	GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
	
	static int sensor[7];
	static int error = 0;
	static double P = 0, I = 0, D = 0;
	static double Kp = KP, Ki = KI, Kd = KD;         // PID ϵ��
	static double PID_value;
	static int previous_error = 0;
	
  sensor[0] = GPIO_Read(FRONTSEVEN1_GPIO_PORT, FRONTSEVEN1_GPIO_PIN);
	sensor[1] = GPIO_Read(FRONTSEVEN2_GPIO_PORT, FRONTSEVEN2_GPIO_PIN);
	sensor[2] = GPIO_Read(FRONTSEVEN3_GPIO_PORT, FRONTSEVEN3_GPIO_PIN);
	sensor[3] = GPIO_Read(FRONTSEVEN4_GPIO_PORT, FRONTSEVEN4_GPIO_PIN);
	sensor[4] = GPIO_Read(FRONTSEVEN5_GPIO_PORT, FRONTSEVEN5_GPIO_PIN);
	sensor[5] = GPIO_Read(FRONTSEVEN6_GPIO_PORT, FRONTSEVEN6_GPIO_PIN);
	sensor[6] = GPIO_Read(FRONTSEVEN7_GPIO_PORT, FRONTSEVEN7_GPIO_PIN);
	
	if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == high) {
		error = 6;
	}
	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == high && sensor[6] == high) {
		error = 5;
	}
	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == high && sensor[6] == low) {
		error = 4;
	}
	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == high && sensor[5] == high && sensor[6] == low) {
		error = 3;
	}
	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == high && sensor[5] == low && sensor[6] == low) {
		error = 2;
	}
	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == high && sensor[4] == high && sensor[5] == low && sensor[6] == low) {
		error = 1;
	}
	else if ((sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == high && sensor[4] == low && sensor[5] == low && sensor[6] == low) ||
		       (sensor[0] == high && sensor[1] == high && sensor[2] == high && sensor[3] == high && sensor[4] == high && sensor[5] == high && sensor[6] == high)) {
		error = 0;
	}
	else if (sensor[0] == low && sensor[1] == low && sensor[2] == high && sensor[3] == high && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
		error = -1;
	}
	else if (sensor[0] == low && sensor[1] == low && sensor[2] == high && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
		error = -2;
	}
	else if (sensor[0] == low && sensor[1] == high && sensor[2] == high && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
		error = -3;
	}
	else if (sensor[0] == low && sensor[1] == high && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
		error = -4;
	}
	else if (sensor[0] == high && sensor[1] == high && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
		error = -5;
	}
	else if (sensor[0] == high && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
		error = -6;
	}
	else if (sensor[0] == low && sensor[1] == low && sensor[2] == low && sensor[3] == low && sensor[4] == low && sensor[5] == low && sensor[6] == low) {
		if (previous_error == -6) {
			error = -7;
		}
		else if(previous_error == 6){
			error = 7;
		}
		else{
		  error = 0;
		}
	}
	
	P = error;
	I = I + error;
	D = error - previous_error;
	PID_value = Kp * P + Ki * I + Kd * D;
	previous_error = error;
	
	GPIO_Low(RIGHTWHEEL_GPIO_PORT, RIGHTWHEEL_GPIO_PIN);    // ���� High ������ Low ��ǰ������ Low ������ High ���
	GPIO_High(LEFTWHEEL_GPIO_PORT, LEFTWHEEL_GPIO_PIN);
	Set_Speed(RIGHTWHEEL_PWM_OUT, FowardSpeed + PID_value);
	Set_Speed(LEFTWHEEL_PWM_OUT, FowardSpeed - PID_value);
}


// �������
void SlideOut(void)
{
  GPIO_Low(SLIDE_GPIO_PORT, SLIDE_GPIO_PIN);              // ���� Low ��ǰ��High ���
	Set_Speed(SLIDE_PWM, 80);
	SysTick_Delay_ms(1500);
	Set_Speed(SLIDE_PWM, 0);
}


// �ջػ���
void SlideIn(void)
{
  GPIO_High(SLIDE_GPIO_PORT, SLIDE_GPIO_PIN);              // ���� Low ��ǰ��High ���
	Set_Speed(SLIDE_PWM, 80);
	SysTick_Delay_ms(1500);
	Set_Speed(SLIDE_PWM, 0);
}


// ���һ��ץȡ
void Catch(void)
{
	MoveSrv7(1);                   // �ϲ��̧��
	MoveSrv15(0);                  // ��������
	Delay(500);
	
	MoveSrv1(1);                   // ץ�����
	MoveSrv2(1);
	MoveSrv3(1);
	MoveSrv4(1);
	MoveSrv5(1);
	MoveSrv6(1);
	Delay(500);
	
	SlideOut();                    // �������    
	Delay(1500);
	
	MoveSrv1(0);                   // ץ���ջ�
	MoveSrv2(0);
	MoveSrv3(0);
	MoveSrv4(0);
	MoveSrv5(0);
	MoveSrv6(0);
	Set_Speed(TRACK_PWM, 128);     // �Ĵ���ʼ�˶�
	Delay(500);
	
	MoveSrv7(0);                   // �ϲ�۷��� 
	MoveSrv15(1);                  // ����̧��
	Delay(750);
	
	Set_Speed(TRACK_PWM, 0);       // �Ĵ�ֹͣ�˶�
	SlideIn();                     // �����ջ�
}
