#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED端口定义，位带操作
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1

#define	LED_GPIO_CLK 				RCC_AHB1Periph_GPIOF
#define	LED_GPIO_PORT 			GPIOF
#define LED_GPIO_PIN				GPIO_Pin_10

void LED_Init(void);//初始化		 				    
#endif
