#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "global.h"
#include "led.h"
#include "key.h"
#include "pwm.h"
#include "adc.h"
#include "time.h"
#include "dac.h"
#include "arm_math.h"
#include "oled.h"
#include "adc_dma.h"
#include "bsp_ad7606.h"

extern u16 ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

int main(void)
{
 	SystemInit();//系统初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先级分组为2
	delay_init(168);    //
	uart_init(115200);	//串口初始化 波特率115200
	LED_Init();
	
	Adc_Init();         //ADC 初始化
	// ADC_DmaUse_Init(); dma使用
	
	//AD芯片配置
	bsp_InitAD7606();	
	AD7606_Reset();
	
	PWM2_Init(4200-1,1-1);//初始化pwm2  预重装4200 分频系数1
	PWM1_Init(8400-1,1-1,1);//初始化pwm1 
	
	//OLED配置
	OLED_Init();
	OLED_Clear();
	
	Dac1_Init(); //初始化dac通道1
	
	//配置基本定时器
	BasicTIM1_EXTI_Init(8399,0);
	BasicTIM2_EXTI_Init(8399,99);
	
	EXTIX_Init();//中断初始化
	TIM1_CenterMode_PWM_Init();//初始化TIM1中心对齐pwm 逆变器
	TIM14->CCR1 = 4200;					//设置tim14 寄存器值为4200
	// PWM2_Init(4200-1,1-1);
	// ucRefresh = 1;
	// EXTIX_Init();
	// TIM1_CenterMode_PWM_Init();
	
	//	OLED_Init();
	//	OLED_Clear();
	
	//	OLED_ShowString(1,1,"pro:");
	//	OLED_ShowString(2,1,"i1   :");
	//	OLED_ShowString(3,1,"i2  :");
	
	while(1)
	{
	
	}
}




