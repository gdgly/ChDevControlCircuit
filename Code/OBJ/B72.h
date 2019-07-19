#ifndef B72_H_
#define	B72_H_

#include "OBJ_MODEL.h"
#include "obj_ID.h"
#include "global.h"
/*-------------------------------------------------*/
#define	ID_NETWORK			0x01
#define	ID_DEVICE			0x72
#define ID_REMOTE_CNTRL		0x02
#define	FLAG_RX_ALL			0xFF
/*-------------------board special---------------------*/
enum obj_hw{adc_0 = 0,adc_1 = 1,adc_2 = 2,adc_3 = 3,adc_4 = 4,adc_5 = 5,in_0 = 6,in_1 = 7,in_2 = 8,in_3 = 9,
			out_0 = 10,out_1 = 11,out_2 = 12,out_3 = 13,out_4 = 14,out_5 = 15,out_6 = 16,out_7 = 17,
			pwm_0=18,pwm_1=19};

#define out_offset	out_0
#define pwm_offset	pwm_0
#define adc_offset	adc_0
#define in_offset	in_0			
/*-------------------board special---------------------*/
/*
v 0.3
1) create object name  example   " #define obj_name	(IND_obj_NULL + x)"
2) create object init like "obj_name_init  obj_index,class,snap,handler	
3) add 	object init to 	_obj_cofig_	
*/
/*----------------------------------------------------------------------------------------------------\
           name           |      index          |   class     | type     | hw_snap  |   Handler       | 
\----------------------------------------------------------------------------------------------------*/
#define _obj_STATUS_init       obj_STATUS           ,IND_obj_CAS  ,obj_soft  ,   NULL   ,board_START
/*---------------------------------------------------------------------------------------------------*/
#define _obj_ADC0_init	       IND_obj_aINV         ,IND_obj_SWC  ,obj_hard  ,   adc_0   ,NULL
#define _obj_ADC1_init	       IND_obj_aINC         ,IND_obj_SWC  ,obj_hard  ,   adc_1   ,NULL
#define _obj_ADC2_init	       IND_obj_aOUTV        ,IND_obj_SWC  ,obj_hard  ,   adc_2   ,NULL
#define _obj_ADC3_init	       IND_obj_aOUTC        ,IND_obj_SWC  ,obj_hard  ,   adc_3   ,NULL
#define _obj_ADC4_init	       IND_obj_aDRV         ,IND_obj_SWC  ,obj_hard  ,   adc_4   ,NULL
#define _obj_ADC5_init	       IND_obj_aDRC         ,IND_obj_SWC  ,obj_hard  ,   adc_5   ,NULL
#define _obj_PWM1_init	       IND_obj_PWM1         ,IND_obj_CAS  ,obj_hard  ,   pwm_0   ,PWM1_Handler
#define _obj_PWM2_init	       IND_obj_PWM2         ,IND_obj_CAS  ,obj_hard  ,   pwm_1   ,PWM2_Handler
#define _obj_OUT6_init	       IND_obj_PredZar      ,IND_obj_CAS  ,obj_hard  ,   out_6   ,NULL
#define _obj_OUT7_init	       IND_obj_KM1          ,IND_obj_CAS  ,obj_hard  ,   out_7   ,NULL
/*---------------------------------------------------------------------------------------------------*/
#define _obj_TICK_1S_init      IND_obj_TICK_1S      ,IND_obj_SWC  ,obj_soft  ,   NULL   ,TICK_Handler
#define _obj_ADC_CONV_init     IND_obj_ADC_CONV     ,IND_obj_CAS  ,obj_soft  ,   NULL   ,ADC_Handler

#define _obj_PID1_KP_init      IND_obj_PID1_KP      ,IND_obj_COM  ,obj_soft  ,   NULL   ,PID_COEF_Handler
#define _obj_PID1_KI_init      IND_obj_PID1_KI      ,IND_obj_COM  ,obj_soft  ,   NULL   ,PID_COEF_Handler
#define _obj_PID1_KD_init      IND_obj_PID1_KD      ,IND_obj_COM  ,obj_soft  ,   NULL   ,PID_COEF_Handler
#define _obj_PID_init          IND_obj_PID_ON       ,IND_obj_CAS  ,obj_soft  ,   NULL    ,PID_Control_Handler

#define _obj_PWM_FRQ_init      IND_obj_PWM_FREQ     ,IND_obj_CAS  ,obj_soft  ,   NULL    ,PWM_freq_config_Handler
#define _obj_PWM_ON_init       IND_obj_PWM_ON       ,IND_obj_CAS  ,obj_soft  ,   NULL    ,PWM_Control_Handler
 
#define _obj_BUCK_init         IND_obj_BUCK_MODE    ,IND_obj_CAS  ,obj_soft  ,   NULL    ,BUCK_Mode_Handler
#define _obj_BOOST_init        IND_obj_BOOST_MODE   ,IND_obj_CAS  ,obj_soft  ,   NULL    ,BOOST_Mode_Handler

	

#define _obj_cofig_	{_obj_STATUS_init},{_obj_TICK_1S_init}, \
					{_obj_PID1_KP_init},{_obj_PID1_KI_init},{_obj_PID1_KD_init},{_obj_PID1_KP_init},{_obj_PID_init}, \
					{_obj_ADC0_init},{_obj_ADC1_init},{_obj_ADC2_init},{_obj_ADC3_init},{_obj_ADC4_init},{_obj_ADC5_init},{_obj_ADC_CONV_init},	\
					{_obj_OUT6_init},{_obj_OUT7_init},{_obj_PWM1_init},{_obj_PWM2_init},{_obj_PWM_FRQ_init},{_obj_PWM_ON_init}, \
					{_obj_BUCK_init},{_obj_BOOST_init}
					

/*--------------------------------------------------------------------------------------*/
			
/*-------------------------------------------------*/
/*obj handlers*/
void board_START(OBJ_STRUCT *obj);
void ADC_Handler(OBJ_STRUCT *obj);
void TICK_Handler(OBJ_STRUCT *obj);
					
void PWM1_Handler(OBJ_STRUCT *obj);
void PWM2_Handler(OBJ_STRUCT *obj);
void PWM_freq_config_Handler(OBJ_STRUCT *obj);
void PWM_Control_Handler(OBJ_STRUCT *obj);

void BUCK_Mode_Handler(OBJ_STRUCT *obj);
void BOOST_Mode_Handler(OBJ_STRUCT *obj);

void PID_COEF_Handler(OBJ_STRUCT *obj);
void PID_Control_Handler(OBJ_STRUCT *obj);
#endif