#ifndef __I2C_H_
#define __I2C_H_

#include "stm32f10x.h"

enum IIC_REPLAY_ENUM
{
	IIC_NACK = 0,
	IIC_ACK = 1
};

enum IIC_BUS_STATE_ENUM
{
	IIC_BUS_READY = 0,
	IIC_BUS_BUSY=1,
	IIC_BUS_ERROR=2
};

#define IIC_GPIO					GPIOB
#define RCC_APB1_IIC_GPIO			RCC_AHB1Periph_GPIOB
#define IIC_SCL_Pin					GPIO_Pin_6
#define IIC_SDA_Pin					GPIO_Pin_7

#define SDA_H()			GPIO_SetBits( IIC_GPIO , IIC_SDA_Pin )
#define SDA_L()			GPIO_ResetBits( IIC_GPIO , IIC_SDA_Pin )
#define SCL_H()			GPIO_SetBits( IIC_GPIO , IIC_SCL_Pin )
#define SCL_L()			GPIO_ResetBits( IIC_GPIO , IIC_SCL_Pin)
#define IIC_SDA_STATE 		(IIC_GPIO->IDR & IIC_SDA_Pin)
#define IIC_SCL_STATE 		(IIC_GPIO->IDR & IIC_SCL_Pin)

extern void I2C_GPIO_Configuration(void);
//IIC 写入单字节
extern void I2C_WriteByte(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data);
//IIC 读取单字节
extern uint8_t I2C_ReadByte(uint8_t SlaveAddress, uint8_t REG_Address);
// IIC burst read multiple bytes
extern void I2C_ReadBytes(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t *buf, uint8_t num);
// IIC burst write multiple bytes
extern void I2C_WriteBytes(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t *REG_data, uint8_t num);


#endif


 