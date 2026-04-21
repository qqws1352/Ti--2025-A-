#ifndef __ADC_DMA_H
#define __ADC_DMA_H	
#include "sys.h" 

#define RHEOSTAT_NOFCHANEL      3

/*=====================通道1 IO======================*/
#define RHEOSTAT_ADC_GPIO_PORT1    GPIOC
#define RHEOSTAT_ADC_GPIO_PIN1     GPIO_Pin_0
#define RHEOSTAT_ADC_GPIO_CLK1     RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL1      ADC_Channel_10

/*=====================通道2 IO ======================*/
#define RHEOSTAT_ADC_GPIO_PORT2    GPIOC
#define RHEOSTAT_ADC_GPIO_PIN2     GPIO_Pin_1
#define RHEOSTAT_ADC_GPIO_CLK2     RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL2      ADC_Channel_11

/*=====================通道3 IO ======================*/
#define RHEOSTAT_ADC_GPIO_PORT3    GPIOC
#define RHEOSTAT_ADC_GPIO_PIN3     GPIO_Pin_2
#define RHEOSTAT_ADC_GPIO_CLK3     RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL3    	 ADC_Channel_12

/*=====================通道4 IO ======================*/
#define RHEOSTAT_ADC_GPIO_PORT4    GPIOC
#define RHEOSTAT_ADC_GPIO_PIN4     GPIO_Pin_3
#define RHEOSTAT_ADC_GPIO_CLK4     RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL4    	 ADC_Channel_13

/*=====================通道5 IO ======================*/
#define RHEOSTAT_ADC_GPIO_PORT5    GPIOC
#define RHEOSTAT_ADC_GPIO_PIN5     GPIO_Pin_4
#define RHEOSTAT_ADC_GPIO_CLK5     RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL5    	 ADC_Channel_14

/*=====================通道6 IO ======================*/
#define RHEOSTAT_ADC_GPIO_PORT6    GPIOC
#define RHEOSTAT_ADC_GPIO_PIN6     GPIO_Pin_5
#define RHEOSTAT_ADC_GPIO_CLK6     RCC_AHB1Periph_GPIOC
#define RHEOSTAT_ADC_CHANNEL6    	 ADC_Channel_15

// ADC 序号宏定义
#define RHEOSTAT_ADC               ADC1
#define RHEOSTAT_ADC_CLK           RCC_APB2Periph_ADC1

// ADC 采样时间宏定义
#define RHEOSTAT_ADC_SAMPLETIME		 ADC_SampleTime_112Cycles

// ADC DR寄存器宏定义，ADC转换后的数字值则存放在这里
#define RHEOSTAT_ADC_DR_ADDR    ((u32)ADC1+0x4c)


// ADC DMA 通道宏定义，这里我们使用DMA传输
#define RHEOSTAT_ADC_DMA_CLK      RCC_AHB1Periph_DMA2
#define RHEOSTAT_ADC_DMA_CHANNEL  DMA_Channel_0
#define RHEOSTAT_ADC_DMA_STREAM   DMA2_Stream0



void ADC_DmaUse_Init(void);

	
#endif