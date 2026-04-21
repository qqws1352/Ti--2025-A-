#ifndef __TEMPORARY_H
#define __TEMPORARY_H

#include "sys.h"
#include "global.h"
#include "arm_math.h"

#define 	PLL_IS_SET 	1
#define 	PLL_NO_SET 	0

//		   *抗饱和PI控制器参数整定 宏定义*  	  //

// 锁相环PI参数及输出限幅
#define SPLL_KP					0.2f    
#define SPLL_KI					0.02f   
#define SPLL_OUT_MAX		0.05f
#define SPLL_OUT_MIN		-0.05f
#define SOGI_PID_INIT 	{0,0,0,SPLL_KP,0,0,0,0,SPLL_OUT_MAX,SPLL_OUT_MIN,0,0,SPLL_KI,SPLL_KI,0,0}

// 电压环PI参数及输出限幅
#define VOL_KP			  	0.6f    
#define VOL_KI			  	0.125f   
#define VOL_OUT_MAX			3.0f
#define VOL_OUT_MIN			0.0f
#define VOL_PID_INIT 		{0,0,0,VOL_KP,0,0,0,0,VOL_OUT_MAX,VOL_OUT_MIN,0,0,VOL_KI,VOL_KI,0,0}

//PR控制器参数设定
#define PR_Kr   -50.0f
#define PR_Kp   -0.025f
#define PR_w_c  2.0f
#define PR_w_0  (2.0f*50.0f*PI_RAD)
#define PR_Ts   1.0f/(10000.0f)
#define PR_Max  1.0f
#define PR_Min  -1.0f

#define PR_Kr_3   -28.0f
#define PR_Kp_3   -0.003f
#define PR_w_c_3  20.0f
#define PR_w_0_3  (2.0f*150.0f*PI_RAD)
#define PR_Ts_3   1.0f/(10000.0f)
#define PR_Max_3  1
#define PR_Min_3  -1

// SOGI滤波器参数 (10kHz)
#define SOGI_FILTRE_50HZ_INIT {0,0,0,0,0,0,{0.999513786364320f,0.0307233098775979f,-0.0307233098775979f,0.956071026197396f},		\
															{0.000687506080851944f,0.0434427601669234f},{0,0},0}

// SOGI滤波器参数 (5kHz)
//#define SOGI_FILTRE_50HZ_INIT {0,0,0,0,0,0,{0.998083887362504f,0.060082038188258f,-0.060082038188258f,0.913127885364308f},	\
															{0.002709383269419f,0.084956001998196f},{0,0},{0}}
// 单极性PWM输出
	void PWM_output_zheng_liu_ce(float duty);

#endif
