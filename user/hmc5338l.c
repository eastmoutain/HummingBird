#include "hmc5338l.h"
#include "stm32f10x.h"
#include "i2c.h"
#include <stdio.h>



void HMC5338L_Configuration(void)
{
	// 8 samples averaged, 75Hz frequency, no artificial bias.
	I2C_WriteByte(HMC58X3_ADDR, HMC58X3_R_CONFA, 0x70); 
	I2C_WriteByte(HMC58X3_ADDR, HMC58X3_R_CONFB, 0xA0);
	I2C_WriteByte(HMC58X3_ADDR, HMC58X3_R_MODE, 0x00);
}

void HMC5338L_GetID(MegaID_TypeDef *mega_id)
{
	mega_id->id[0] = (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_IDA);
	mega_id->id[1] = (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_IDB);
	mega_id->id[2] = (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_IDC);

	printf("id0 = %x,\t should be 0x48\r\n", (int16_t)mega_id->id[0]);
	printf("id1 = %x,\t should be 0x34\r\n", (int16_t)mega_id->id[1]);
	printf("id2 = %x,\t should be 0x33\r\n", (int16_t)mega_id->id[2]);
	
	return;
}

 void _HMC5338L_ReadValue(MegaTypeDef * mega_xyz)
{
	uint8_t tmp;

	tmp = (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_XM);
	mega_xyz->megaX = tmp<<8 | (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_XL);
	tmp = (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_YM);
	mega_xyz->megaY = tmp<<8 | (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_YL);
	tmp = (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_ZM);
	mega_xyz->megaZ = tmp<<8 | (uint8_t)I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_ZL);

//	I2C_ReadBytes(HMC58X3_ADDR, HMC58X3_R_XM, data, 6);
//	mega_xyz->megaX = data[0]<<1 | (unsigned char)data[1];
//	mega_xyz->megaY = data[2]<<1 | (unsigned char)data[3];
//	mega_xyz->megaX = data[4]<<1 | (unsigned char)data[5];

	printf("megaX=%d,\tmegaY=%d,\tmegaZ=%d\r\n",
			(int16_t)mega_xyz->megaX,
			(int16_t)mega_xyz->megaY,
			(int16_t)mega_xyz->megaZ);

	return;
}

//void HMC5338L_ReadValue(MegaTypeDef * mega_xyz)
//{
//	MegaTypeDef temp;
//	int i;
//	uint32_t sumx, sumy, sumz;
//	for(i = 0; i < 4; i++) {
//		_HMC5338L_ReadValue(&temp);
//		sumx += temp.megaX;
//		sumy += temp.megaY;
//		sumz += temp.megaZ;
//	}
//	
//	mega_xyz->megaX = sumx>>2;
//	mega_xyz->megaY = sumy>>2;
//	mega_xyz->megaZ = sumz>>2;
//
//	printf("megaX=%d,\tmegaY=%d,\tmegaZ=%d\r\n",
//			mega_xyz->megaX,
//			mega_xyz->megaY,
//			mega_xyz->megaZ);
//
//	return ;
//}

//void HMC5338L_GetID(MegaID_TypeDef *ID)
//{
//	
//	ID->id[0] = I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_IDA);
//	ID->id[1] = I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_IDB);
//	ID->id[2] = I2C_ReadByte(HMC58X3_ADDR, HMC58X3_R_IDC);
//
//	printf("id[0] = %x\tshould be 0x48\r\n", ID->id[0]);
//	printf("id[1] = %x\tshould be 0x38\r\n", ID->id[1]);
//	printf("id[2] = %x\tshould be 0x33\r\n", ID->id[2]);
//
//	return;
//}
