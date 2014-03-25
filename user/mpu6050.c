#include "mpu6050.h"
#include "i2c.h"
#include "delay.h"
#include <stdio.h>


void MPU6050_Inital(void)
{
//	MPU6050_INT_GPIO_Config();
	Delay_ms(10);
	//½â³ýÐÝÃß
	I2C_WriteByte( SLAVEADRESS , PWR_MGMT_1 , 0x00);	// set clock
	printf("Read from PWR_MGMT 0X%x, should be 0x00\r\n", I2C_ReadByte( SLAVEADRESS , PWR_MGMT_1 ));
		
	I2C_WriteByte( SLAVEADRESS , GYRO_CONFIG , 0x18 ); //set grop scale to +-2000 degree per second
	printf("Read from GYRO_CONFIG 0X%x, should be 0x18\r\n", I2C_ReadByte( SLAVEADRESS , GYRO_CONFIG ));
	
	I2C_WriteByte( SLAVEADRESS , ACCEL_CONFIG , 0x00 ); //set gravity to +-2G
	printf("Read from ACCEL_CONFIG 0X%x, should be 0x00\r\n", I2C_ReadByte( SLAVEADRESS , ACCEL_CONFIG ));

	I2C_WriteByte( SLAVEADRESS , SMPLRT_DIV , 0x01 );
	printf("Read from SMPLRT_DIV 0X%x,should be 0x01\r\n", I2C_ReadByte( SLAVEADRESS , SMPLRT_DIV ));

	I2C_WriteByte( SLAVEADRESS , CONFIG , 0x06); //µÍÍ¨ÂË²¨
	printf("Read from CONFIG 0X%x, should be 0x06\r\n", I2C_ReadByte( SLAVEADRESS , CONFIG ));
	
//	I2C_WriteByte( SLAVEADRESS , USER_CTRL , 1<<5);

	// interrupt active high, pull up, pin changes to low level when interrupt is cleard by any reading
	I2C_WriteByte( SLAVEADRESS , INT_PIN_CFG , 0x32 ); 
	printf("Read from CONFIG 0X%x, should be 0x32\r\n", I2C_ReadByte( SLAVEADRESS , CONFIG ));
	
		// 
	I2C_WriteByte( SLAVEADRESS ,INT_ENABLE , 0x01 ); 
	printf("Read from CONFIG 0X%x, should be 0x01\r\n", I2C_ReadByte( SLAVEADRESS , CONFIG ));


	Delay_ms(10);
}


uint16_t getAccX(void)
{
	uint16_t AccX = 0;
	uint8_t AccXH = 0 , AccXL = 0;

	AccXH = I2C_ReadByte( SLAVEADRESS , ACCEL_XOUT_H );
	AccXL = I2C_ReadByte( SLAVEADRESS , ACCEL_XOUT_L );

	AccX = (AccXH << 8) | AccXL;

	return AccX;
}

uint16_t getAccY(void)
{
	uint16_t AccY = 0;
	uint8_t AccYH = 0 , AccYL = 0;

	AccYH = I2C_ReadByte( SLAVEADRESS , ACCEL_YOUT_H );
	AccYL = I2C_ReadByte( SLAVEADRESS , ACCEL_YOUT_L );

	AccY = ( AccYH << 8) | (u8)AccYL;

	return AccY;
}

uint16_t getAccZ(void)
{
	uint16_t AccZ = 0;
	uint8_t AccZH = 0 , AccZL = 0;

	AccZH = I2C_ReadByte( SLAVEADRESS , ACCEL_ZOUT_H );
	AccZL = I2C_ReadByte( SLAVEADRESS , ACCEL_ZOUT_L );

	AccZ = (AccZH << 8) | (u8)AccZL;

	return AccZ;
}

uint16_t getGyroX(void)
{
	uint16_t GyroX = 0;
	uint8_t GyroXH = 0 , GyroXL = 0; 
	
	GyroXH = I2C_ReadByte( SLAVEADRESS , GYRO_XOUT_H );
	GyroXL = I2C_ReadByte( SLAVEADRESS , GYRO_XOUT_H );
	
	GyroX = (GyroXH << 8) | (u8)GyroXL;
	
	return GyroX;	
}

uint16_t getGyroY(void)
{
   	uint16_t GyroY = 0;
	uint8_t GyroYH = 0 , GyroYL = 0; 
	
	GyroYH = I2C_ReadByte( SLAVEADRESS , GYRO_YOUT_H );
	GyroYL = I2C_ReadByte( SLAVEADRESS , GYRO_YOUT_H );
	
	GyroY = (GyroYH << 8) | (u8)GyroYL;
	
	return GyroY;	
}

uint16_t getGyroZ(void)
{
   	uint16_t GyroZ = 0;
	uint8_t GyroZH = 0 , GyroZL = 0; 
	
	GyroZH = I2C_ReadByte( SLAVEADRESS , GYRO_ZOUT_H );
	GyroZL = I2C_ReadByte( SLAVEADRESS , GYRO_ZOUT_H );
	
	GyroZ = (GyroZH << 8) | (u8)GyroZL;
	
	return GyroZ;	
}

uint16_t getTemperature(void)
{
 	uint16_t temperature = 0;
	uint8_t temperatureH = 0 , temperatureL = 0;
	

	temperatureH = I2C_ReadByte( SLAVEADRESS , TEMP_OUT_H );
	temperatureL = I2C_ReadByte( SLAVEADRESS , TEMP_OUT_L );

	temperature = (temperatureH << 8) | (u8)temperatureL;

	return temperature;
}

