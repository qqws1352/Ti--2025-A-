#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) //PE3
#define WK_UP 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0

#define KEY_GPIO_CLK 				RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE

#define KEY_01_GPIO_PORT		GPIOE
#define KEY_01_GPIO_PIN			GPIO_Pin_3|GPIO_Pin_4

#define WK_UP_GPIO_PORT			GPIOA
#define WK_UP_GPIO_PIN			GPIO_Pin_0

void KEY_Init(void);

#define WK_UP_EXTI_LINE_PORT			EXTI_PortSourceGPIOA
#define WK_UP_EXTI_LINE_PIN				EXTI_PinSource0
#define WK_UP_EXTI_LINE_USE				EXTI_Line0
#define WK_UP_EXTI_LINE_INQ				EXTI0_IRQn
#define WK_UP_EXTI_START_MODE			EXTI_Trigger_Rising

#define KEY_01_EXTI_LINE_PORT			EXTI_PortSourceGPIOE
#define KEY_1_EXTI_LINE_PIN			EXTI_PinSource3
#define KEY_0_EXTI_LINE_PIN			EXTI_PinSource4
#define KEY_01_EXTI_LINE_USE			EXTI_Line3 | EXTI_Line4
#define KEY_01_EXTI_START_MODE		EXTI_Trigger_Falling
#define KEY_0_EXTI_LINE_INQ				EXTI4_IRQn
#define KEY_1_EXTI_LINE_INQ				EXTI3_IRQn

void EXTIX_Init(void);	//外部中断初始化	

#endif
