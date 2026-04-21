#include "temporary.h"

void PWM_output_zheng_liu_ce(float duty)
{
		if(duty > 0)
		{
			TIM_SetCompare3(TIM5,0);
			TIM_SetCompare4(TIM5, duty*4200);
		}
		else
		{
			TIM_SetCompare4(TIM5,0);
			TIM_SetCompare3(TIM5,-duty*4200);
		}
}

