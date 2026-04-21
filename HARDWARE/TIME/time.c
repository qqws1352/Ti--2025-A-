#include "usart.h"
#include "time.h"
#include "adc.h"
#include "global.h"
#include "led.h"
#include "pwm.h"
#include "math.h"
#include "delay.h"
#include "oled.h"
#include "adc_dma.h"
#include "bsp_ad7606.h"

void BasicTIM1_EXTI_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(BASICTIME1_TIMER_CLK,ENABLE);  
	
  TIM_TimeBaseInitStructure.TIM_Period =arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BASICTIME1_TIMER,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(BASICTIME1_TIMER,TIM_IT_Update,ENABLE); //������ʱ��3�����ж�
	TIM_Cmd(BASICTIME1_TIMER,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=BASICTIME1_TIMER_Channel; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void BasicTIM2_EXTI_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(BASICTIME2_TIMER_CLK,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(BASICTIME2_TIMER,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(BASICTIME2_TIMER,TIM_IT_Update,ENABLE); //������ʱ��3�����ж�
	TIM_Cmd(BASICTIME2_TIMER,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=BASICTIME2_TIMER_Channel; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void SVPWMmodulation_TIM1(float Ur, float Udc, float theta)//7��ʽ	�ߵ�ѹU=sqrt(3)*Ur<=Udc
{
	float Tsv1 = 0, Tsv2 = 0, Tsv3 = 0, Tsv4 = 0, Tsv5 = 0, Tsv6 = 0, Tsv7 = 0;
	float Da = 0, Db = 0, Dc = 0;
	
	if(theta > 2.f * PI)
		theta -= 2.f * PI;
	else if(theta < 0)
		theta += 2.f * PI;
	
	if(theta >= 0.f && theta <= PI/3.f)//��һ����	v7->v6->v4->v0
	{
		Tsv4 = 1.5f * Ur * arm_sin_f32(PI/3.f - theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv6 = 1.5f * Ur * arm_sin_f32(theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv7 = 0.5f * (1.f - Tsv4 - Tsv6);	//v0=v7��������*0.5
		Da = Tsv7 + Tsv6 + Tsv4;
		Db = Tsv7 + Tsv6;
		Dc = Tsv7;
	}
	else if(theta <= 2.f*PI/3.f)//�ڶ�����	v7->v6->v2->v0
	{
		theta -= PI/3.f;
		Tsv6 = 1.5f * Ur * arm_sin_f32(PI/3.f - theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv2 = 1.5f * Ur * arm_sin_f32(theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv7 = 0.5f * (1.f - Tsv6 - Tsv2);
		Da = Tsv7 + Tsv6;
		Db = Tsv7 + Tsv6 + Tsv2;
		Dc = Tsv7;
	}
	else if(theta <= PI)//��������	v7->v3->v2->v0
	{
		theta -= 2.f*PI/3.f;
		Tsv2 = 1.5f * Ur * arm_sin_f32(PI/3.f - theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv3 = 1.5f * Ur * arm_sin_f32(theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv7 = 0.5f * (1.f - Tsv3 - Tsv2);
		Da = Tsv7;
		Db = Tsv7 + Tsv3 + Tsv2;
		Dc = Tsv7 + Tsv3;
	}
	else if(theta <= 4.f*PI/3.f)//��������	v7->v3->v1->v0
	{
		theta -= PI;
		Tsv3 = 1.5f * Ur * arm_sin_f32(PI/3.f - theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv1 = 1.5f * Ur * arm_sin_f32(theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv7 = 0.5f * (1.f - Tsv3 - Tsv1);
		Da = Tsv7;
		Db = Tsv7 + Tsv3;
		Dc = Tsv7 + Tsv3 + Tsv1;
	}
	else if(theta <= 5.f*PI/3.f)//��������	v7->v5->v1->v0
	{
		theta -= 4.f*PI/3.f;
		Tsv1 = 1.5f * Ur * arm_sin_f32(PI/3.f - theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv5 = 1.5f * Ur * arm_sin_f32(theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv7 = 0.5f * (1.f - Tsv1 - Tsv5);
		Da = Tsv7 + Tsv5;
		Db = Tsv7;
		Dc = Tsv7 + Tsv5 + Tsv1;
	}
	else if(theta <= 2.f*PI)//��������	v7->v5->v4->v0
	{
		theta -= 5.f*PI/3.f;
		Tsv5 = 1.5f * Ur * arm_sin_f32(PI/3.f - theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv4 = 1.5f * Ur * arm_sin_f32(theta) / (Udc * arm_sin_f32(PI/3.f));
		Tsv7 = 0.5f * (1.f - Tsv5 - Tsv4);
		Da = Tsv7 + Tsv5 + Tsv4;
		Db = Tsv7;
		Dc = Tsv7 + Tsv5;
	}
	else 
		return;//error
	
	if(1)
	{
		TIM1->CCR1 = Da * 8400;
		TIM1->CCR2 = Dc * 8400;
		TIM1->CCR3 = Db * 8400;		
	}
	else 
	{		
		TIM1->CCR1 = Da * 8400;
		TIM1->CCR2 = Db * 8400;
		TIM1->CCR3 = Dc * 8400;		
	}	

//		TIM1->CCR1 = Da * 8400;
//		TIM1->CCR2 = Db * 8400;
//		TIM1->CCR3 = Dc * 8400;	
	
}	

extern u16 ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

// SOGI�˲���
SOGI_Filter SOGI_Single = SOGI_FILTRE_50HZ_INIT;
SOGI_Filter SOGI_Cur 		= SOGI_FILTRE_50HZ_INIT;

// SOGI������������ѹ�������������Ե�PI������
PIDREG pid_SPLL = SOGI_PID_INIT;
PIDREG pid_vol 	= VOL_PID_INIT;

// ������ѹ���������Ľṹ��
SinglePhaseVector Vgrid = { 0.0f };
SinglePhaseVector Igrid = { 0.0f };

// Clark�任ת������->������������
float v_alpha, v_beta;

float vd,vq,v_rms;

float i_alpha, i_beta;

float id,iq,i_rms;

float flo_cos,duty=1.0f;

u32 i=0,j=0,k=0;

float angle;
float V_adcx,V_adcx_a=0;
float I_adcx,I_adcx_a=0;
float A_adcx,A_adcx_a=0;

extern u8 flag;
float angle_goal=1;

float Vdcref = 2.0f, Iref = 0.0f;
float Vr = 0.0f, Vinvr = 0.0f;
float Vdc = 0.0f;

float PhaseShift = 0.0f;
float Iampref    = 0.0f;
float Iamp       = 0.0f;

float angle_ready;

Controller_Structure PR_Controller;

// pid V ctrl
float Verr,Verr_all=0,Vout_put;
float Vkp = 0.15f,Vki = 0.015f;
float Vpid_out_max = 0.95f,Vpid_out_min = 0.6f;

// pid I ctrl
float Ierr,Ierr_all=0,Iout_put;
float Ikp = -0.0015f,Iki = -0.015f;
float Ipid_out_max = 0.95f,Ipid_out_min = 0.5f;

float w_c = 2.0f*PI, phase;
float sin_u, sin_v, sin_w;
float cos_u, cos_v, cos_w;

float sin_i,cos_i;

u16 time_num = 0;

float HZ = 50.0f,w;
float Va, Vb, Vc;
float Vout_ref = 2.4f;

float V_ctrl,I_ctrl;

float Va_ctrl, Vb_ctrl, Vc_ctrl, Ia_ctrl, Ib_ctrl , Ic_ctrl;

int ctrl_time = 0;

void BASICTIME1_TIMER_IRQHandler(void)
{
	if(TIM_GetITStatus(BASICTIME1_TIMER,TIM_IT_Update)==SET)
	{
		// Get Adc Sample
		Va_ctrl = Get_Adc(ADC_Channel_10) * 3.3f / 4095.0f;	//32V:1V PORT:PC0
		Vb_ctrl = Get_Adc(ADC_Channel_11) * 3.3f / 4095.0f;	//32V:1V PORT:PC1
		Vc_ctrl = Get_Adc(ADC_Channel_12) * 3.3f / 4095.0f;	//16V:1V PORT:PC2

		Va_ctrl = Get_Adc(ADC_Channel_13) * 3.3f / 4095.0f;	//2A:1V PORT:PC3
		Ib_ctrl = Get_Adc(ADC_Channel_14) * 3.3f / 4095.0f;	//2A:1V PORT:PC4
		Ic_ctrl = Get_Adc(ADC_Channel_15) * 3.3f / 4095.0f;	//2A:1V PORT:PC5

		// Clark
		v_alpha = Va_ctrl;
		v_beta = 0.66666667f * (0.866025103f * Vb_ctrl - 0.866025103f * Vc_ctrl);

		// Park
		sin_u = arm_sin_f32(w * time_num);
		cos_u = arm_cos_f32(w * time_num);
    vd = v_alpha * cos_u + v_beta * sin_u;
    // vq = v_beta * cos_u - v_alpha * sin_u;

		//Rms calc
		if(vd < 0) vd = -vd;
		V_ctrl = vd * 0.707f;

		// Clark
		i_alpha = Va_ctrl;
		i_beta = 0.66666667f * (0.866025103f * Vb_ctrl - 0.866025103f * Vc_ctrl);

		// Park
		sin_i = arm_sin_f32(w * time_num);
		cos_i = arm_cos_f32(w * time_num);
    	id = i_alpha * cos_i + i_beta * sin_i;
    	// vq = v_beta * cos_u - v_alpha * sin_u;

		//Rms calc
		if(id < 0) id = -id;
		I_ctrl = id * 0.707f;

		// Three phase step theta
		time_num = time_num + 1;
		if(time_num >= 10000.0f/HZ) time_num = 0;

		w  = w_c/(10000.0f/HZ);

		// PID V ctrl
		if(ctrl_time == 0){

			Verr = 2.0F - V_ctrl;
			Verr_all = Verr_all + Ierr;
			Vout_put = Vkp * Verr + Vki * Verr_all;

			if(Vout_put >= Vpid_out_max){
				Vout_put = Vpid_out_max;
				Verr_all = Vpid_out_max / Vki;
			}
			else if(Vout_put <= Vpid_out_min){
				Vout_put = Vpid_out_min;
				Verr_all = Vpid_out_min / Vki;
			}
		}

		// SVPWM PWM out
		SVPWMmodulation_TIM1(Vout_put, 1.732f,(w*time_num));
		/* ----------------------------------------------
		In this config，Udc = sqrt(3)
		out_put range is [0-1] with V [zero out - max out]
		----------------------------------------------- */

		// PID Iout ctrl
		if(ctrl_time == 0){
			
			Ierr = 2.0f - I_ctrl;
			Ierr_all = Ierr_all + Ierr;
			Iout_put = Ikp * Ierr + Iki * Ierr_all;

			if(Iout_put >= Ipid_out_max){
				Iout_put = Ipid_out_max;
				Ierr_all = Ipid_out_max / Iki;
			}
			else if(Iout_put <= Ipid_out_min){
				Iout_put = Ipid_out_min;
				Ierr_all = Ipid_out_min / Iki;
			}
		}

		// Boost PWM
		TIM_SetCompare3(TIM5,Iout_put*4200);
			
		
		ctrl_time++;
		if(ctrl_time >= 200) ctrl_time = 0;

		PFout(9) = !PFout(9);
		
	}
	TIM_ClearITPendingBit(BASICTIME1_TIMER,TIM_IT_Update);
}

u8 usart_show_data_num = 0;

void BASICTIME2_TIMER_IRQHandler(void)
{
	if(TIM_GetITStatus(BASICTIME2_TIMER,TIM_IT_Update)==SET)
	{
		OLED_ShowString(3,1,"Vout   :");
		OLED_ShowString(4,1,"Freq   :");

		OLED_ShowFloat(1,8,V_ctrl*16.0f);
		OLED_ShowFloat(4,8,HZ);
	}
	TIM_ClearITPendingBit(BASICTIME2_TIMER,TIM_IT_Update);

}




