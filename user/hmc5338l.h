#ifndef __HMC5338L_H_
#define __HMC5338L_H_

#include <stdint.h>
// 7 bit address of the HMC58X3 used with the Wire library
#define HMC58X3_ADDR 0x3C 
#define HMC_POS_BIAS 1
#define HMC_NEG_BIAS 2
// HMC58X3 register map. For details see HMC58X3 datasheet
#define HMC58X3_R_CONFA 0
#define HMC58X3_R_CONFB 1
#define HMC58X3_R_MODE 2
#define HMC58X3_R_XM 3
#define HMC58X3_R_XL 4

#define HMC58X3_R_YM (7)  //!< Register address for YM.
#define HMC58X3_R_YL (8)  //!< Register address for YL.
#define HMC58X3_R_ZM (5)  //!< Register address for ZM.
#define HMC58X3_R_ZL (6)  //!< Register address for ZL.

#define HMC58X3_R_STATUS 9
#define HMC58X3_R_IDA 10
#define HMC58X3_R_IDB 11
#define HMC58X3_R_IDC 12

typedef struct {
	uint16_t megaX;
	uint16_t megaY;
	uint16_t megaZ;	
}MegaTypeDef;

typedef struct {
	uint8_t id[3];	
}MegaID_TypeDef;

extern void HMC5338L_Configuration(void);
extern void _HMC5338L_ReadValue(MegaTypeDef * mega_xyz);
extern void HMC5338L_GetID(MegaID_TypeDef *ID);

#endif
