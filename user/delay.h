#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f10x_conf.h"
extern void Delay_Init(void);
extern void Delay_ms(u16 nms);
extern void Delay_us(u32 nus);

void Delay_10ms(uint32_t nCount);
#endif
