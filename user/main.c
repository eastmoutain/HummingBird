#include <stdio.h>                          /* standard I/O .h-file           */
#include <ctype.h> 
#include <math.h>                         /* character functions            */
#include "stm32f10x.h"
#include "i2c.h"
#include "nvic.h"
#include "usart.h"
#include "delay.h"
#include "lcd.h"
#include "mpu6050.h"
#include "hmc5338l.h"

static MegaTypeDef mega;
static MegaID_TypeDef id;


int main(void)
{  
	static double rad = 0.0; 
	static uint16_t radius = 90;
	const static double rad_step = 2*3.1415926/60;
	const static double circle_rad = 2*3.1415926;


	Delay_Init();
	
	LCD_Init();
	/* 
	* Init USART1, pay attention here, USART initialization should 
	* be after LCD initialization, or it will hardware fault. 
	*/
	USART1_Init();

	I2C_GPIO_Configuration();
	MPU6050_Inital();
	HMC5338L_Configuration();
	HMC5338L_Configuration();

//	LCD_DrawLine(0, 0, 180, 120, RED);
	    	
    Draw_Circle(120, 160, 100, RED);
	Draw_Circle(120, 159, 100, RED);	
	Draw_Circle(121, 159, 100, RED);
	Draw_Circle(121, 160, 100, RED);

	while(1) {
		printf("ok!!!\r\n");
		_HMC5338L_ReadValue(&mega);
		HMC5338L_GetID(&id);		
		Delay_ms(100);

		if(rad >= circle_rad) {
			rad = 0.0 ;
		}
		else 
			rad += rad_step;
//		 LCD_DrawLine(120, 160, 180, 120, RED);
		LCD_DrawLine(120, 160,  (uint16_t)(120 + radius*cos(rad)), (uint16_t)(160 + radius*sin(rad)), RED);
		LCD_DrawLine(120, 159,  (uint16_t)(120 + radius*cos(rad)), (uint16_t)(159 + radius*sin(rad)), RED);
		LCD_DrawLine(121, 159,  (uint16_t)(121 + radius*cos(rad)), (uint16_t)(159 + radius*sin(rad)), RED);
		LCD_DrawLine(121, 160,  (uint16_t)(121 + radius*cos(rad)), (uint16_t)(160 + radius*sin(rad)), RED);
//		LCD_DrawLine(120, 160,  (uint16_t)(120 + radius*cos(rad)), (uint16_t)(159 + radius*sin(rad)), RED);
		Delay_ms(900);
//		LCD_DrawLine(120, 160, 180, 120, BLACK);
		LCD_DrawLine(120, 160,  (uint16_t)(120 + radius*cos(rad)), (uint16_t)(160 + radius*sin(rad)), BLACK);
		LCD_DrawLine(120, 159,  (uint16_t)(120 + radius*cos(rad)), (uint16_t)(159 + radius*sin(rad)), BLACK);
		LCD_DrawLine(121, 159,  (uint16_t)(121 + radius*cos(rad)), (uint16_t)(159 + radius*sin(rad)), BLACK);
		LCD_DrawLine(121, 160,  (uint16_t)(121 + radius*cos(rad)), (uint16_t)(160 + radius*sin(rad)), BLACK);
//		LCD_DrawLine(120, 160,  (uint16_t)(120 + radius*cos(rad)), (uint16_t)(159 + radius*sin(rad)), BLACK);


		printf("temperature=%d\r\n", (int16_t)getTemperature());
		printf("getAccX=%d\r\n", (int16_t)getAccX());
		printf("getAccY=%d\r\n", (int16_t)getAccY());
		printf("getAccZ=%d\r\n", (int16_t)getAccZ());	   
		printf("getGyroX=%d\r\n", (int16_t)getGyroX());
		printf("getGyroY=%d\r\n", (int16_t)getGyroY());
		printf("getGyroZ=%d\r\n", (int16_t)getGyroZ());

		
		 
	}

 
}


