#include "pwm.h"
#include "led.h"
#include "usart.h"
#include "arm_math.h"

void PWM1_Init(u32 arr,u32 psc,u8 choose)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef					GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(PWM1_TIM_CLK,ENABLE);  	//TIM14时钟使能    
	RCC_AHB1PeriphClockCmd(PWM1_GPIO_CLK, ENABLE); 	//使能PORTF时钟	
	
	PWM1_GPIO_PIN_AF_TIM
	
	GPIO_InitStructure.GPIO_Pin = PWM1_GPIO_PIN;         //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(PWM1_GPIO_PORT,&GPIO_InitStructure);              //初始化PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(PWM1_TIM_USE,&TIM_TimeBaseStructure);//初始化定时器14
	
	//初始化TIM14 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	
	switch(choose)
	{
		case 1:
			TIM_OC1Init(PWM1_TIM_USE, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
			TIM_OC1PreloadConfig(PWM1_TIM_USE, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
			break;
		case 2:
			TIM_OC2Init(PWM1_TIM_USE, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
			TIM_OC2PreloadConfig(PWM1_TIM_USE, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
			break;
		case 3:
			TIM_OC3Init(PWM1_TIM_USE, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
			TIM_OC3PreloadConfig(PWM1_TIM_USE, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
			break;
		case 4:
			TIM_OC4Init(PWM1_TIM_USE, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
			TIM_OC4PreloadConfig(PWM1_TIM_USE, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
			break;
		default:
			break;
	}
	
  TIM_ARRPreloadConfig(PWM1_TIM_USE,ENABLE);//ARPE使能 
	
	TIM_Cmd(PWM1_TIM_USE, ENABLE);  //使能TIM14
 				  
}  

void PWM2_Init(u32 arr,u32 psc)
{
		//此部分需手动修改IO口设置	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //GPIOF9复用为定时器2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
    
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//初始化定时器2
	
	//初始化TIM5 Channel1 PWM模式	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM5在CCR1上的预装载寄存器

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM5在CCR1上的预装载寄存器
 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM5在CCR1上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM5, ENABLE);  //使能TIM5	
}

void TIM1_CH1_PWM_Init(u16 per,u16 psc)
{
//结构体初始化
	GPIO_InitTypeDef 	GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef 	TIM_OCInitStructure;
	TIM_BDTRInitTypeDef 	TIM_BDTRInitStructure;
//时钟	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//使能TIM1时钟
//IO复用
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM1);//管脚复用
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM1);//管脚复用	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);//管脚复用
//IO配置   PA6刹车  PA7主PWM 8副PWM									   
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //复用输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;//管脚设置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;//
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化结构体

	//GPIO_ResetBits(GPIOA,GPIO_Pin_6); 
	
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //复用输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;//管脚设置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化结构体
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //复用输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;//管脚设置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化结构体
// 定时器配置									 	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
// 定时器比较输出通道配置
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//PWM1模式
	TIM_OCInitStructure.TIM_Pulse=0;//设置占空比
    //主通道
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出通道电平极性设置
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//输出使能
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset;//输出通道空闲电平极性配置
	//互补通道
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High;//互补输出通道电平极性设置
	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;//互补输出使能
	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//互补输出通道空闲电平极性配置

	TIM_OC1Init(TIM1,&TIM_OCInitStructure); //输出比较通道1初始化
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable); //使能TIMx在 CCR1 上的预装载寄存器
// 刹车死区配置
	TIM_BDTRInitStructure.TIM_AutomaticOutput=TIM_AutomaticOutput_Enable;// 自动输出功能使能
	TIM_BDTRInitStructure.TIM_Break=TIM_Break_Disable;//刹车输入
	TIM_BDTRInitStructure.TIM_BreakPolarity=TIM_BreakPolarity_High; //刹车输入管脚极性高 
	TIM_BDTRInitStructure.TIM_DeadTime=168; //输出打开和关闭状态之间的延时 84-1us  168-2us 
	TIM_BDTRInitStructure.TIM_LOCKLevel=TIM_LOCKLevel_OFF;// 锁电平参数: 不锁任何位
	TIM_BDTRInitStructure.TIM_OSSIState=TIM_OSSIState_Disable; //设置在运行模式下非工作状态选项
	TIM_BDTRInitStructure.TIM_OSSRState=TIM_OSSRState_Disable; //设置在运行模式下非工作状态选项
	TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);

	TIM_ARRPreloadConfig(TIM1,ENABLE);//使能预装载寄存器  	
	TIM_Cmd(TIM1,ENABLE); //使能定时器		
	TIM_CtrlPWMOutputs(TIM1,ENABLE); //主输出使能  

}

void TIM1_CenterMode_PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);

//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM10);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	TIM_TimeBaseInitStructure.TIM_Period = 8400 - 1; //20kHz
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
//	TIM_TimeBaseInitStructure.TIM_Period = 8400 - 1; //20kHz
//	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM1,&TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM1,&TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(TIM1,&TIM_OCInitStructure);
	
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
//	TIM_OCInitStructure.TIM_Pulse = 0;
//	TIM_OC1Init(TIM10,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
//	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);
	
//	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
//	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
//	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
//	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
//	TIM_BDTRInitStructure.TIM_DeadTime = 17;
//	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable; 
//	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable; 
//	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);	
	
	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
//	TIM_Cmd(TIM10,ENABLE);
//	TIM_CtrlPWMOutputs(TIM10, ENABLE);
}



