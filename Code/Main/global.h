/*************************************************
* File Name          : global.h
* Author             : Tatarchenko S.
* Version            : v 1.1
* Description        : global.c header	
*************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/*-----------------------------------------------*/
#include "stm32f10x.h"
#include "string.h"
#include "i2c.h"
#include "adc.h"
#include "dma.h"
#include "pwm.h"
#include "ext.h"
#include "usart.h"
#include "can.h"
#include "mcp23x17.h"
#include "adg72x.h"
#include "mcp3221.h"
/*-----------------------------------------------*/
/*----------- global define----------------------*/

/**/
#ifdef MCP23017_ADRESS
	
	#define	OUTPUTS 	PortA_Byte_All.PortA_Byte 
	#define INPUTS		PortB_Byte_All.PortB_Byte 
	
	#define NUM_OF_INPUTS	8
	#define NUM_OF_OUTPUTS	8
	
	#define OUT0	PortA_Byte_All.bit.B0
	#define OUT1	PortA_Byte_All.bit.B1
	#define OUT2	PortA_Byte_All.bit.B2
	#define OUT3	PortA_Byte_All.bit.B3
	#define OUT4	PortA_Byte_All.bit.B4
	#define OUT5	PortA_Byte_All.bit.B5
	#define OUT6	PortA_Byte_All.bit.B6
	#define OUT7	PortA_Byte_All.bit.B7

	#define IN0		PortB_Byte_All.bit.B0
	#define IN1		PortB_Byte_All.bit.B1
	#define IN2		PortB_Byte_All.bit.B2
	#define IN3		PortB_Byte_All.bit.B3
	#define IN4		PortB_Byte_All.bit.B4
	#define IN5		PortB_Byte_All.bit.B5
	#define IN6		PortB_Byte_All.bit.B6
	#define IN7		PortB_Byte_All.bit.B7
	
#endif

#ifdef	ADG729_ADRESS
	
	#define AIN1	AnalogValue1.Value
	#define AIN2	AnalogValue2.Value
	#define AIN3	AnalogValue3.Value
	#define AIN4	AnalogValue4.Value
	
#endif

#define LED_OFF 		(GPIOC->BSRR |= GPIO_BSRR_BS13);
#define LED_ON 			(GPIOC->BSRR |= GPIO_BSRR_BR13);


#define MCP23017_RESET 	(GPIOB->BSRR = GPIO_BSRR_BS5);
#define MCP23017_START 	(GPIOB->BSRR = GPIO_BSRR_BR5);


/*-----------local function prototypes----------*/
/*init different IO pins*/
void DifPinInit(void);
/*init all peripherals and external circuits*/
void Core_Init(void);
/*----------- global function prototypes---------*/
/*��� ��������� ������� ������� ��� ������ � ����� � ������������� ������������ */

/*run only in high priority tasks*********************************************
******************************************************************************/

/*get state of all available IO ports and puts it in the appropriate structure,
  return true if success*/
extern _Bool Get_IO_State(void);

/*set state of chosen IO pin and puts it in the appropriate structure, return
  true if success*/
extern _Bool Set_IO_State(int pin,int pin_state);

/*set state of all chosen IO port and puts it in the appropriate structure, 
return true if success*/
extern _Bool Set_IO_Byte(uint8_t byte);

/*get analog state in mV of chosen port and puts it in the appropriate structure,
return true if success*/
extern _Bool Get_AIn_State(int port);

/*calc adc value*/
void adc_calc_value(void);

/**/
uint16_t get_dvl1000_value(uint16_t adc_voltage);
uint16_t get_lac300_value(uint16_t adc_voltage);
/**/
void led_invertor(void);

#define adc_filter_size	60
extern uint16_t adc_moving_average_filter(uint16_t *buff, uint32_t buff_size);

extern uint16_t adc_ch1_buffer[adc_filter_size];
extern uint16_t adc_ch2_buffer[adc_filter_size];
extern uint16_t adc_ch3_buffer[adc_filter_size];
extern uint16_t adc_ch4_buffer[adc_filter_size];
extern uint16_t adc_ch5_buffer[adc_filter_size];
extern uint16_t adc_ch6_buffer[adc_filter_size];

/**/
int comparator(int plus, int minus);

/*low priority tasks**********************************************************
******************************************************************************/
/*error handler for internal errors during execution ( MCP23017 error )*/
extern void ResetIO_Model(void);
/*----------- global typedef---------------------*/

/*state of all io port */
#pragma pack(push,1)
typedef struct{
	union{
		uint8_t PortA_Byte;
		struct{
			unsigned A0:1;
			unsigned A1:1;
			unsigned A2:1;
			unsigned A3:1;
			unsigned A4:1;
			unsigned A5:1;
			unsigned A6:1;
			unsigned A7:1;
			} bit;
		} PortA_Byte_All;	
	union{
		uint8_t PortB_Byte;
		struct{
			unsigned B0:1;
			unsigned B1:1;
			unsigned B2:1;
			unsigned B3:1;
			unsigned B4:1;
			unsigned B5:1;
			unsigned B6:1;
			unsigned B7:1;
			} bit;
		} PortB_Byte_All;
		
}PortState_REGISTR;
#pragma pack(pop)

#pragma pack(push,1)

typedef struct{
	
	uint16_t adc1_value;
	uint16_t adc2_value;
	uint16_t adc3_value;
	uint16_t adc4_value;
	uint16_t adc5_value;
	uint16_t adc6_value;
	
	uint16_t CH1_ADC;
	uint16_t CH2_ADC;
	uint16_t CH3_ADC;
	uint16_t CH4_ADC;
	uint16_t CH5_ADC;
	uint16_t CH6_ADC;
	
	uint16_t TEMP_SENSOR;
	
}value_ADC_REGISTR;

#pragma pack(pop)
/*value in mV(voltage) of avaliable analog inputs */
#pragma pack(push,1)
typedef struct{
	/**/
	union{
		uint16_t Value;
		struct{
			uint8_t HHalf;
			uint8_t LHalf;
		}byte;
	}AnalogValue1;
	/**/
	union{
		uint16_t Value;
		struct{
			uint8_t HHalf;
			uint8_t LHalf;
		}byte;
	}AnalogValue2;
	/**/
	union{
		uint16_t Value;
		struct{
			uint8_t HHalf;
			uint8_t LHalf;
		}byte;
	}AnalogValue3;
	/**/
	union{
		uint16_t Value;
		struct{
			uint8_t HHalf;
			uint8_t LHalf;
		}byte;
	}AnalogValue4;	
}AnalogState_REGISTR;
#pragma pack(pop)

/*----------- global variables-------------------*/
#define ADC1_BUF_SIZE	7

extern uint16_t ADC1_DataArray[ADC1_BUF_SIZE];

extern PortState_REGISTR IO_STATE;
extern PortState_REGISTR *IO_Pointer;

extern value_ADC_REGISTR value_ADC;
extern value_ADC_REGISTR *adc_val;

/**/
extern AnalogState_REGISTR AIN_State;
extern AnalogState_REGISTR *AIN_Pointer;

#define pU16(val) *((uint16_t*)&val)

#define OPAM_ADC_REF		3300

#endif














