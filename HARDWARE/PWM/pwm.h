#ifndef _PWM_H
#define _PWM_H
#include "sys.h"

#define PWM1_TIM_USE						TIM14
#define PWM1_TIM_CLK						RCC_APB1Periph_TIM14

#define PWM1_GPIO_AF_TIM				GPIO_AF_TIM14
#define PWM1_GPIO_PINSOURCE			GPIO_PinSource9

#define PWM1_GPIO_PORT					GPIOF
#define PWM1_GPIO_PIN						GPIO_Pin_9
#define PWM1_GPIO_CLK						RCC_AHB1Periph_GPIOF

#define PWM1_GPIO_PIN_AF_TIM	\
				GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14);\

void PWM1_Init(u32 arr,u32 psc,u8 choose);
void PWM2_Init(u32 arr,u32 psc);
void TIM1_CH1_PWM_Init(u16 per,u16 psc);
void TIM1_CenterMode_PWM_Init(void);
void SVPWMmodulation(float Ur, float Udc, float theta);

#endif
