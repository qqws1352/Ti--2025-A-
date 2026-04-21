#include "delay.h"
#include "led.h"
#include "key.h"
#include "pwm.h"
#include "global.h"

void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(KEY_GPIO_CLK, ENABLE);//ʹ开启GPIOA E
	
	GPIO_InitStructure.GPIO_Pin = KEY_01_GPIO_PIN; //PE3 PE4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MH
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(KEY_01_GPIO_PORT, &GPIO_InitStructure);//GPIOE 使能
	
	GPIO_InitStructure.GPIO_Pin = WK_UP_GPIO_PIN;//WK_UP PA0--reset
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(WK_UP_GPIO_PORT, &GPIO_InitStructure);//GPIOA0 使能
 
} 

void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;  // NVIC中断优先级结构体
	EXTI_InitTypeDef   EXTI_InitStructure;  // 外部中断初始化结构体
	
	KEY_Init(); // 先初始化按键对应的GPIO（必须在中断配置前完成）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); // 使能SYSCFG时钟（外部中断依赖此时钟）
 
	// 连接GPIO到外部中断线（映射关系配置）
	SYSCFG_EXTILineConfig(WK_UP_EXTI_LINE_PORT, WK_UP_EXTI_LINE_PIN); // WK_UP（PA0）映射到EXTI_Line0
	SYSCFG_EXTILineConfig(KEY_01_EXTI_LINE_PORT, KEY_1_EXTI_LINE_PIN); // KEY1（PE3）映射到EXTI_Line3
	SYSCFG_EXTILineConfig(KEY_01_EXTI_LINE_PORT, KEY_0_EXTI_LINE_PIN); // KEY0（PE4）映射到EXTI_Line4

	
  /* 配置WK_UP对应的EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = WK_UP_EXTI_LINE_USE; // 选择中断线0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; // 中断模式（非事件模式）
  EXTI_InitStructure.EXTI_Trigger = WK_UP_EXTI_START_MODE; // 上升沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE; // 使能中断线0
  EXTI_Init(&EXTI_InitStructure); // 初始化外部中断
	
	/* 配置KEY0、KEY1对应的EXTI_Line3和Line4 */
	EXTI_InitStructure.EXTI_Line = KEY_01_EXTI_LINE_USE; // 选择中断线3和4
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; // 中断模式
  EXTI_InitStructure.EXTI_Trigger = KEY_01_EXTI_START_MODE; // 下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE; // 使能中断线3和4
  EXTI_Init(&EXTI_InitStructure); // 初始化外部中断
 
	// 配置WK_UP中断的NVIC优先级
	NVIC_InitStructure.NVIC_IRQChannel = WK_UP_EXTI_LINE_INQ; // 中断通道为EXTI0_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04; // 抢占优先级4
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04; // 子优先级4
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // 使能中断通道
  NVIC_Init(&NVIC_InitStructure); // 初始化NVIC
	
	// 配置KEY1中断的NVIC优先级
	NVIC_InitStructure.NVIC_IRQChannel = KEY_1_EXTI_LINE_INQ; // 中断通道为EXTI3_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04; // 抢占优先级4
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; // 子优先级3（比WK_UP高）
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // 使能中断通道
  NVIC_Init(&NVIC_InitStructure); // 初始化NVIC
	
	// 配置KEY0中断的NVIC优先级
	NVIC_InitStructure.NVIC_IRQChannel = KEY_0_EXTI_LINE_INQ; // 中断通道为EXTI4_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04; // 抢占优先级4
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; // 子优先级2（比KEY1高）
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // 使能中断通道
  NVIC_Init(&NVIC_InitStructure); // 初始化NVIC
}

extern float angle_goal;

extern float PhaseShift;

extern float HZ;

u8 flag = 1;

void EXTI0_IRQHandler(void)
{
	delay_us(1000);	//����
	if(WK_UP==1)	 
	{
		HZ = 50.0f;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	

//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_us(1000);	//����
	if(KEY1 == 0)	 
	{
		HZ = HZ - 1.0f;
		if(HZ < 20.0f) HZ = 20.0f;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	delay_us(1000);	//����
	if(KEY0 == 0) 
	{				 
		HZ = HZ + 1.0f;
		if(HZ > 100.0f) HZ = 100.0f;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
}

