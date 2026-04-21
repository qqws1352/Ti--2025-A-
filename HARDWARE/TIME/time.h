#ifndef __TIME_H
#define __TIME_H	
#include "sys.h" 

#define BASICTIME1_TIMER							TIM7
#define	BASICTIME1_TIMER_CLK					RCC_APB1Periph_TIM7
#define	BASICTIME1_TIMER_Channel			TIM7_IRQn
#define	BASICTIME1_TIMER_IRQHandler		TIM7_IRQHandler
	
	void BasicTIM1_EXTI_Init(u16 arr,u16 psc);
	
#define BASICTIME2_TIMER							TIM3
#define	BASICTIME2_TIMER_CLK					RCC_APB1Periph_TIM3
#define	BASICTIME2_TIMER_Channel			TIM3_IRQn
#define	BASICTIME2_TIMER_IRQHandler		TIM3_IRQHandler
	void BasicTIM2_EXTI_Init(u16 arr,u16 psc);

	void SVPWMmodulation_TIM1(float Ur, float Udc, float theta);
	
#endif 
