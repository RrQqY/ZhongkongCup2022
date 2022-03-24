/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

#include "main.h"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}


// IMU中断读取数据
void IMU_USART_IRQHandler(void)
{
	USART_ClearITPendingBit(IMU_USARTx, USART_IT_TXE);
	USART_ClearITPendingBit(IMU_USARTx, USART_IT_RXNE);
	
	if(USART_GetITStatus(IMU_USARTx, USART_IT_TXE) != RESET)
  { 
    USART_SendData(IMU_USARTx, TxBuffer[TxCounter++]); 
    USART_ClearITPendingBit(IMU_USARTx, USART_IT_TXE);
    if(TxCounter == imu_count) USART_ITConfig(IMU_USARTx, USART_IT_TXE, DISABLE);
  }
	else if(USART_GetITStatus(IMU_USARTx, USART_IT_RXNE) != RESET)       // 接收中断
  {
		GPIO_Low(RED_GPIO_PORT, RED_GPIO_PIN);           // 打开白灯
		GPIO_Low(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
		GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
		
		CopeSerial2Data((unsigned char)IMU_USARTx->DR);                    // 处理数据
		USART_ClearITPendingBit(IMU_USARTx, USART_IT_RXNE);
  }
	
	USART_ClearITPendingBit(IMU_USARTx, USART_IT_ORE);
}


// NANO中断读取数据
void NANO_USART_IRQHandler(void)
{
	
}


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

void SysTick_Handler(void)
{
	static const float dt = 1.0 / 1000;               // 间隔8ms
	static const int ZERO_OFFSET_COUN = (1 / dt);     // 1/8 = 125次每秒
	
	/* 任务1：MPU6050任务 */
	if( ! task_readdata_finish ){
		MPU6050ReadGyro(Gyro);
		gyroZ = ((Gyro[2]-22.95)/16.4f)*3.55f;          // 减的越大零偏跃靠近负数，调整系数越大转的越多
		integralZ += gyroZ * dt;
		
		task_readdata_finish = 1; //标志位置1，表示需要在主循环处理MPU6050数据
  }
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

// PWM 输入捕获中断函数

__IO uint16_t IC2Value_Left = 0;    // CCR1对应周期，CCR2对应占空比
__IO uint16_t IC1Value_Left = 0;

void TIM3_IRQHandler(void)
{
  // 清除中断标志位
  TIM_ClearITPendingBit(LEFTWHEEL_TIM_IN, TIM_IT_CC1);

  // 获取输入捕获值
  IC1Value_Left = TIM_GetCapture1(LEFTWHEEL_TIM_IN);    // CCR1对应周期，CCR2对应占空比
  IC2Value_Left = TIM_GetCapture2(LEFTWHEEL_TIM_IN);
	
  // 注意：捕获寄存器CCR1和CCR2的值在计算占空比和频率的时候必须加1
	if (IC1Value_Left != 0){
    // 占空比计算
    DutyCycle_Left = (float)((IC2Value_Left+1) * 100) / (IC1Value_Left + 1);

    // 频率计算
    Frequency_Left = (72000000/(ADVANCE_TIM_PSC+1))/(float)(IC1Value_Left+1);
	
//		printf("DutyCycle: %0.2f%%   Frequency: %0.2f Hz\n", DutyCycle, Frequency);
		
//		GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);          // 打开蓝灯
//   	GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
//	  GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
  }
	else{
		DutyCycle_Left = 0;
		Frequency_Left = 0;
		
		GPIO_Low(RED_GPIO_PORT, RED_GPIO_PIN);           // 打开红灯
   	GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
	  GPIO_High(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
	}
	
	// 清除中断标志位
  TIM_ClearITPendingBit(LEFTWHEEL_TIM_IN, TIM_IT_CC1);
}


__IO uint16_t IC2Value_Right = 0;    // CCR1对应周期，CCR2对应占空比
__IO uint16_t IC1Value_Right = 0;

void TIM4_IRQHandler(void)
{
  // 清除中断标志位
  TIM_ClearITPendingBit(RIGHTWHEEL_TIM_IN, TIM_IT_CC1);

  // 获取输入捕获值
  IC1Value_Right = TIM_GetCapture1(RIGHTWHEEL_TIM_IN);    // CCR1对应周期，CCR2对应占空比
  IC2Value_Right = TIM_GetCapture2(RIGHTWHEEL_TIM_IN);
	
  // 注意：捕获寄存器CCR1和CCR2的值在计算占空比和频率的时候必须加1
	if (IC1Value_Right != 0){
    // 占空比计算
    DutyCycle_Right = (float)((IC2Value_Right+1) * 100) / (IC1Value_Right + 1);

    // 频率计算
    Frequency_Right = (72000000/(ADVANCE_TIM_PSC+1))/(float)(IC1Value_Right+1);
	
//		printf("DutyCycle: %0.2f%%   Frequency: %0.2f Hz\n", DutyCycle, Frequency);
		
//		GPIO_High(RED_GPIO_PORT, RED_GPIO_PIN);          // 打开蓝灯
//   	GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
//	  GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
  }
	else{
		DutyCycle_Right = 0;
		Frequency_Right = 0;
		
		GPIO_Low(RED_GPIO_PORT, RED_GPIO_PIN);           // 打开红灯
   	GPIO_High(GREEN_GPIO_PORT, GREEN_GPIO_PIN);
	  GPIO_High(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
	}
	
	// 清除中断标志位
  TIM_ClearITPendingBit(RIGHTWHEEL_TIM_IN, TIM_IT_CC1);
}



/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


// EXTI Line --> PF9
//void macXPT2046_EXTI_INT_FUNCTION ( void )
//{ 
//  if ( EXTI_GetITStatus ( macXPT2046_EXTI_LINE ) != RESET )
//  {	
//    ucXPT2046_TouchFlag = 1;
//		
//    EXTI_ClearITPendingBit ( macXPT2046_EXTI_LINE );
//		
//  }
//	
//}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
