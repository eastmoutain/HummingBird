#include "stm32f10x.h"
#include "i2c.h"
#include <stdio.h>

void I2C_GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* Configure I2C1 pins: SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  IIC_SCL_Pin | IIC_SDA_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;

	GPIO_Init(IIC_GPIO, &GPIO_InitStructure);

	SDA_H();
	SCL_H();
}



// delay funtion for I2C 
static void IIC_Dealy(void)
{
	u32 i = 15;
	while( i-- );
}

/*******************************************************************
TWI_START
发送启动数据
*******************************************************************/
static uint8_t IIC_Start(void)
{
	SDA_H();
	SCL_H();
	IIC_Dealy();

	if( IIC_SDA_STATE == RESET )
	{
		return IIC_BUS_BUSY;
	}

	SDA_L();
	IIC_Dealy();

	if( IIC_SDA_STATE == SET )
	{
		return IIC_BUS_ERROR;
	}

	return IIC_BUS_READY;
}

/*******************************************************************
TWI_STOP
发送停止数据
*******************************************************************/
static void IIC_Stop(void)
{
	SDA_L();
	SCL_H();
	IIC_Dealy();

	SDA_H();
	IIC_Dealy();
	SDA_H();
}

/*******************************************************************************
* 函数名称:TWI_SendNACK                                                                     
* 描    述:收到数据,发送NACK                                                                                                                                       
 *******************************************************************************/
static void IIC_SendNACK(void)
{
	SCL_L();
	SDA_H();
	IIC_Dealy();
	SCL_H();
	IIC_Dealy();
	SCL_L(); 
	IIC_Dealy(); 
}

/*******************************************************************************
* 函数名称:TWI_SendACK                                                                     
* 描    述:收到数据,发送ACK                                                                                                                                        
*******************************************************************************/
static void IIC_SendACK(void)
{
	SCL_L();
	SDA_L();
	IIC_Dealy();
	SCL_H();
	IIC_Dealy();
	SCL_L(); 
	IIC_Dealy();
}

/*******************************************************************************
 * 函数名称:TWI_SendByte                                                                     
 * 描    述:发送一个字节                                                                                                                                      
 *******************************************************************************/
static u8 IIC_SendByte(u8 Data)
{
	 uint8_t i;
	
	
	 for(i=0;i<8;i++)
	 {  
		  SCL_L();
		IIC_Dealy();
		if(Data&0x80)
		{
			SDA_H();
		}
		else
		{
			SDA_L();
		} 
		Data<<=1;
		IIC_Dealy();
		SCL_H(); 
		IIC_Dealy();
		 
	 }
	 //接收从机的应答  
	 SCL_L(); 
	 IIC_Dealy();
	 SCL_H();
	 IIC_Dealy(); 
 
	 if(IIC_SDA_STATE)
	 {
		printf("no ack");
		SCL_L();
		return IIC_NACK;
	 }
	 else
	 {	
		 SCL_L();
		return IIC_ACK;  
	 }    
}

/*******************************************************************************
 * 函数名称:TWI_ReceiveByte                                                                     
 * 描    述:接收一个字节                                                                                                                                       
 *******************************************************************************/
static char IIC_RecvByte(void)
{
	 char i,Dat = 0;
	 SDA_H();
	 Dat=0;

	 for(i=0;i<8;i++)
	 {
		SCL_L();
		 IIC_Dealy();
		 SCL_H();//产生时钟上升沿[正脉冲],让从机准备好数据 
		IIC_Dealy(); 
		Dat<<=1;
		if(IIC_SDA_STATE) //读引脚状态
		{
			Dat|=0x01; 
		}       
	 }
	 
	 return Dat;
}

/******	busrt one byte via I2C	*****/
void I2C_WriteByte(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t REG_data)
{
    IIC_Start();                  //起始信号
    IIC_SendByte(SlaveAddress);   //发送设备地址+写信号
    IIC_SendByte(REG_Address);    //内部寄存器地址， //请参考中文pdf22页 
    IIC_SendByte(REG_data);       //内部寄存器数据， //请参考中文pdf22页 
    IIC_Stop();                   //发送停止信号
}

/******	busrt write bytes via I2C	*****/
void I2C_WriteBytes(uint8_t SlaveAddress,uint8_t REG_Address,uint8_t *REG_data, uint8_t num)
{
	int i;
    IIC_Start();                  //起始信号
    IIC_SendByte(SlaveAddress);   //发送设备地址+写信号
    IIC_SendByte(REG_Address);    //内部寄存器地址， //请参考中文pdf22页 
          
	for(i = 0; i < num; i++) {
		IIC_SendByte(REG_data[i]);	//内部寄存器数据， //请参考中文pdf22页 
	}
    IIC_Stop();                   //发送停止信号
}

/********单字节读取*****************************************/
uint8_t I2C_ReadByte(uint8_t SlaveAddress, uint8_t REG_Address)
{  
	char REG_data;
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress);           //发送设备地址+写信号
    IIC_SendByte(REG_Address);            //发送存储单元地址，//从0开始	
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data = IIC_RecvByte();              //读出寄存器数据
	IIC_SendNACK();   
	IIC_Stop();                           //停止信号
    return REG_data; 
}

/*
* Function: burst read bytes
*/
void I2C_ReadBytes(uint8_t SlaveAddress, uint8_t REG_Address, uint8_t *buf, uint8_t num)
{  
	int i = num;
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress);           //发送设备地址+写信号
    IIC_SendByte(REG_Address);            //发送存储单元地址，//从0开始	
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	for(i = 0; i < num; i++) {
		buf[i] = IIC_RecvByte();
		// if it is the last byte to be read, then it should end up with an IIC_SendNACK()
		if (i == num - 1) { 
			IIC_SendNACK();
			break;
		// else it needs an acknowledgement
		} else 
			IIC_SendACK();
	}
	IIC_Stop(); 

    return; 
}

