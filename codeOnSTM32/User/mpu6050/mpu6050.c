#include "mpu6050.h"

// 写数据到MPU6050寄存器
void MPU6050_WriteReg(u8 reg_add,u8 reg_dat)
{
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS);
	i2c_WaitAck();
	i2c_SendByte(reg_add);
	i2c_WaitAck();
	i2c_SendByte(reg_dat);
	i2c_WaitAck();
	i2c_Stop();
}


// 从MPU6050寄存器读取数据
void MPU6050_ReadData(u8 reg_add,unsigned char*Read,u8 num)
{
	unsigned char i;
	
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS);
	i2c_WaitAck();
	i2c_SendByte(reg_add);
	i2c_WaitAck();
	
	i2c_Start();
	i2c_SendByte(MPU6050_SLAVE_ADDRESS+1);
	i2c_WaitAck();
	
	for(i=0;i<(num-1);i++){
		*Read=i2c_ReadByte(1);
		Read++;
	}
	*Read=i2c_ReadByte(0);
	i2c_Stop();
}


// 初始化MPU6050芯片
void MPU6050_Init(void)
{
  int i=0,j=0;
  // 在初始化之前要延时一段时间，若没有延时，则断电后再上电数据可能会出错
  for(i=0;i<1000;i++){
    for(j=0;j<1000;j++){
      ;
    }
  }
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	    // 解除休眠状态
	MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    // 陀螺仪采样率，1KHz
	MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	        // 低通滤波器的设置，截止频率是1K，带宽是5K
	MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x00);	  // 配置加速度传感器工作在2G模式，不自检
	MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     // 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
}


// 读取MPU6050的ID
uint8_t MPU6050ReadID(void)
{
	unsigned char Re = 0;
    MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);      // 读器件地址
	if(Re != 0x68){
		return 0;
	}
	else{
		return 1;
	}
}


// 读取MPU6050的加速度数据
void MPU6050ReadAcc(short *accData)
{
    u8 buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}


// 读取MPU6050的角加速度数据
void MPU6050ReadGyro(short *gyroData)
{
    u8 buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}


// 靠原始角速度数据计算角度
void MPU6050_ReadAngle(short *angleData, int clearFlag)
{
	if(task_readdata_finish){
//		GPIO_Low(BLUE_GPIO_PORT, BLUE_GPIO_PIN);
		angleData[2] = integralZ;
		task_readdata_finish = 0;                   // 清零标志位
	}
}
