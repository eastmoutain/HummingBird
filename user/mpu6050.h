#ifndef __MPU6050_H_
#define __MPU6050_H_

#define MPU6050_INT_GPIO	GPIOB
#define RCC_APB1_MPU6050_INT_GPIO			RCC_AHB1Periph_GPIOB
#define MPU6050_INT_GPIO_Pin					GPIO_Pin_5

#define SELF_TEST_X				0x0D
#define SELF_TEST_Y				0x0E
#define SELF_TEST_Z				0x0F
#define SELF_TEST_A				0x10
#define	SMPLRT_DIV				0x19	// R/W 陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG					0x1A	// R/W 低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG				0x1B	// R/W 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG			0x1C	// R/W 加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define MOT_THR					0x1F	// R/W
#define FIFO_EN					0x23	// R/W
#define I2C_MST_CTRL			0x24	// R/W
#define I2C_SLV0_ADDR			0x25	// R/W
#define I2C_SLV0_REG			0x26	// R/W
#define I2C_SLV0_CTRL			0x27	// R/W
#define I2C_SLV1_ADDR			0x28	// R/W
#define I2C_SLV1_REG			0x29	// R/W
#define I2C_SLV1_CTRL			0x2A	// R/W
#define I2C_SLV2_ADDR			0x2B	// R/W
#define I2C_SLV2_REG			0x2C	// R/W
#define I2C_SLV2_CTRL			0x2D	// R/W
#define I2C_SLV3_ADDR			0x2E	// R/W
#define I2C_SLV3_REG			0x2F	// R/W
#define I2C_SLV3_CTRL			0x30	// R/W
#define I2C_SLV4_ADDR			0x31	// R/W
#define I2C_SLV4_REG			0x32	// R/W
#define I2C_SLV4_DO				0x33	// R/W
#define I2C_SLV4_CTRL			0x34	// R/W
#define I2C_SLV4_DI				0x35	// R
#define I2C_MST_STATUS			0x36	// R
#define INT_PIN_CFG				0x37	// R/W
#define INT_ENABLE				0x38	// R/W
#define INT_STATUS				0x3A	// R
#define ACCEL_XOUT_H			0x3B	// R
#define ACCEL_XOUT_L			0x3C	// R
#define ACCEL_YOUT_H			0x3D	// R
#define ACCEL_YOUT_L			0x3E	// R
#define ACCEL_ZOUT_H			0x3F	// R
#define ACCEL_ZOUT_L			0x40	// R
#define	TEMP_OUT_H				0x41	// R
#define	TEMP_OUT_L				0x42	// R
#define	GYRO_XOUT_H				0x43	// R
#define	GYRO_XOUT_L				0x44	// R
#define	GYRO_YOUT_H				0x45	// R
#define	GYRO_YOUT_L				0x46	// R
#define	GYRO_ZOUT_H				0x47	// R
#define	GYRO_ZOUT_L				0x48	// R
#define	EXT_SENS_DATA_00		0x49	// R
#define	EXT_SENS_DATA_01		0x4A	// R
#define	EXT_SENS_DATA_02		0x4B	// R
#define	EXT_SENS_DATA_03		0x4C	// R
#define	EXT_SENS_DATA_04		0x4D	// R
#define	EXT_SENS_DATA_05		0x4E	// R
#define	EXT_SENS_DATA_06		0x4F	// R
#define	EXT_SENS_DATA_07		0x50	// R
#define	EXT_SENS_DATA_08		0x51	// R
#define	EXT_SENS_DATA_09		0x52	// R
#define	EXT_SENS_DATA_10		0x53	// R
#define	EXT_SENS_DATA_11		0x54	// R
#define	EXT_SENS_DATA_12		0x55	// R
#define	EXT_SENS_DATA_13		0x56	// R
#define	EXT_SENS_DATA_14		0x57	// R
#define	EXT_SENS_DATA_15		0x58	// R
#define	EXT_SENS_DATA_16		0x59	// R
#define	EXT_SENS_DATA_17		0x5A	// R
#define	EXT_SENS_DATA_18		0x5B	// R
#define	EXT_SENS_DATA_19		0x5C	// R
#define	EXT_SENS_DATA_20		0x5D	// R
#define	EXT_SENS_DATA_21		0x5E	// R
#define	EXT_SENS_DATA_22		0x5F	// R
#define	EXT_SENS_DATA_23		0x60	// R
#define	I2C_SLV0_DO				0x63	// R/W
#define	I2C_SLV1_DO				0x64	// R/W
#define	I2C_SLV2_DO				0x65	// R/W
#define	I2C_SLV3_DO				0x66	// R/W
#define	I2C_MST_DELAY_CTRL		0x67	// R/W
#define	SIGNAL_PATH_RESET		0x68	// R/W
#define	MOT_DETECT_CTRL			0x69	// R/W
#define	USER_CTRL				0x6A	// R/W
#define	PWR_MGMT_1				0x6B	// R/W
#define	PWR_MGMT_2				0x6C	// R/W
#define	FIFO_COUNTH				0x72	// R/W
#define	FIFO_COUNTL				0x73	// R/W
#define	FIFO_R_W				0x74	// R/W
#define	WHO_AM_I				0x75	// R
#define	SLAVEADRESS				0xD0	//IIC写入时的地址字节数据，+1为读取
// initial MPU6050 interrupt port
//static void MPU6050_INT_GPIO_Config(void);
//初始化MPU6050
extern void MPU6050_Inital(void);

#include <stdint.h>
//获取加速度计的值
extern uint16_t getAccX(void);
extern uint16_t getAccY(void);
extern uint16_t getAccZ(void);

//获取陀螺仪的值
extern uint16_t getGyroX(void);
extern uint16_t getGyroY(void);
extern uint16_t getGyroZ(void);

//获取温度
extern uint16_t getTemperature(void);



#endif

