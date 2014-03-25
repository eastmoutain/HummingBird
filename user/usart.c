#include "stm32f10x.h"
#include "usart.h"
#include <stdio.h>

static void USART1_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_USART_TxPin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USARTx_Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_USART_RxPin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/* USARTx configuration ------------------------------------------------------*/
  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
static void USARTx_configuration(void)
{
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	 
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1, ENABLE);
}

void USART1_Init(void)
{
	USART1_GPIO_Configuration();
	USARTx_configuration();
}

//USART send a char 
void Usart_SendChar(USART_TypeDef* USARTx, char dat)
{
	while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));	
	USART_SendData(USARTx,dat);

}
//USART receive a char
//static char Usart_GetCahr(USART_TypeDef* USARTx)
//{
//	char dat;
//	while(!USART_GetFlagStatus(USARTx,USART_FLAG_RXNE));
//	dat = (char)(USART_ReceiveData(USARTx)&0xff);
//	
//	return dat;		
//}

int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	Usart_SendChar(USART1, (uint8_t) ch);

	return ch;
}


// USART1 interrupt handler
void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
	{
		USART_ClearFlag(USART1,USART_FLAG_RXNE); 	
	}	
	Usart_SendChar(USART2,USART_ReceiveData(USART1));
}
