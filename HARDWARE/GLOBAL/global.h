#ifndef __GLOBAL_H
#define __GLOBAL_H

//这个文件作为程序中的全局变量存储区
#include "sys.h"
#include "temporary.h"
#include "arm_math.h"

//pi的宏定义封装
#define PI_RAD 	3.1415926535898f

//***********************Part1： 快速排序*************************//
int qusort(int s[],u32 start,u32 end);





//***********************Part2： PR控制器*************************//
//PR控制器运算结构体
typedef struct{
	float x[4];
	float y[4];
}Controller_Structure;
//PR控制器运算函数
void AAL_Control_Controller(Controller_Structure *p,float x);





//***********************Part3： 抗饱和PID*************************//
//抗饱和PI控制器运算结构体
typedef struct {
	volatile float  	pid_ref_reg;		/* Input: Reference input  */
	volatile float  	pid_fdb_reg;		/* Input: Feedback input  */
	volatile float  	e_reg; 					/* Variable: Error	  */
	volatile float  	Kp_reg;					/* Parameter: Proportional gain  */
	volatile float  	up_reg;					/* Variable: Proportional output  */
	volatile float  	ui_reg;					/* Variable: Integral output	*/
	volatile float  	ud_reg;					/* Variable: Derivative output	  */
	volatile float  	uprsat_reg;		  /* Variable: Pre-saturated output  */
	volatile float  	pid_out_max;		/* Parameter: Maximum output	*/
	volatile float  	pid_out_min;		/* Parameter: Minimum output	*/
	volatile float  	pid_out_reg;		/* Output: PID output	 */
	volatile float  	saterr_reg;		  /* Variable: Saturated difference */
	volatile float 		Ki_reg;					/* Parameter: Integral gain   */
	volatile float  	Kc_reg;					/* Parameter: Integral correction gain	*/
	volatile float  	Kd_reg;					/* Parameter: Derivative gain	*/
	volatile float  	up1_reg;				/* History: Previous proportional output  */
} PIDREG;
//抗饱和PI控制器运算函数
void pid_reg_calc(PIDREG *v);





//***********************Part4： SOGI滤波器*************************//
//二阶广义积分SOGI滤波器运算结构体
typedef struct {
	volatile float	SOGI_Un;
	volatile float	SOGI_Yn;
	volatile float	SOGI_X1n;
	volatile float	SOGI_X2n;
	volatile float	SOGI_X1n_1;
	volatile float	SOGI_X2n_1;
	volatile float	SOGI_A[2][2];
	volatile float	SOGI_B[2];
	volatile float	SOGI_C[2];
	volatile float	SOGI_D;
}SOGI_Filter;
//二阶广义积分SOGI滤波器运算函数
void SOGI_Filter_Calc(SOGI_Filter* p);





//***********************Part5： SOGI_PLL*************************//
//SOGI_PLL锁相环运算结构体
typedef	struct {
	volatile float	Value;
	volatile float	Alpha;
	volatile float	Beta;
	volatile float	D;
	volatile float	Q;
	volatile float	VectorAngle;
	volatile float	SinTheta;
	volatile float  CosTheta;
}SinglePhaseVector;
//SOGI_PLL锁相环运算主函数
void SOGI_PLL(SinglePhaseVector *p,SOGI_Filter *v,PIDREG *k);
//派克变换（DQ变换）实现函数
void Park(SinglePhaseVector *p);
//相位归一化处理
void PERIOD_DEFINE_2PI(float Angle);

#endif


