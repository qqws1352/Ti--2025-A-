#include "dac.h"

//DAC通道1输出初始化
void Dac1_Init(void)
{  
  GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB1PeriphClockCmd(DAC_CLK, ENABLE);//使能DAC时钟
  RCC_AHB1PeriphClockCmd(DAC_GPIO_CLK, ENABLE);//使能GPIOA时钟
 
  GPIO_InitStructure.GPIO_Pin = DAC_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(DAC_GPIO_PORT, &GPIO_InitStructure);//初始化

	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Enable ;	//DAC1输出缓存关闭 BOFF1=1
  DAC_Init(DAC_CHANNEL,&DAC_InitType);	 //初始化DAC通道1

	DAC_Cmd(DAC_CHANNEL, ENABLE);  //使能DAC通道1
  
  DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
}


