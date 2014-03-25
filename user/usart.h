#ifndef __USART_H_
#define __USART_H_

	#define GPIO_USART_TxPin	GPIO_Pin_9
	#define GPIO_USART_RxPin	GPIO_Pin_10


extern void USART1_Init(void);
extern void Usart_SendChar(USART_TypeDef* USARTx, char dat);

#endif
