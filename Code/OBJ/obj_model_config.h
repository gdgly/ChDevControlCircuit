/*-------------------------------------------------
                SOM global config 
-------------------------------------------------*/
#ifndef OBJ_CONFIG_H_
#define	OBJ_CONFIG_H_

#define RTOS_USAGE	TRUE
#define SOM_MODE	APP_MODE
#define DEBUG_MODE TRUE
#define REVISION	1
	
#define NUM_OF_OBJ_ADC	8
#define NUM_OF_OBJ_INPUTS	8
#define NUM_OF_OBJ_OUTPUTS	8
#define NUM_OF_PWM	2

/*-----------------------------------------------
************communication channels***************
-----------------------------------------------*/
#define USART_COM_ENABLE	TRUE
#define CAN_COM_ENABLE    	FALSE
/*-----------------------------------------------
************SOM memory usage config**************
-----------------------------------------------*/

#if SOM_MODE == APP_MODE
	#define HARDWARE_OBJECT TRUE
	#define USART_DATA_FAST	TRUE
	#define OBJECT_TIMER	TRUE

	#define	num_of_all_obj		100
	#define MES_BUF_SIZE		20

	#if HARDWARE_OBJECT == TRUE
		#define NUM_OF_HWOBJ    50
	#endif
	#if OBJECT_TIMER == TRUE
		#define NUM_OF_TIMER    20
	#endif

	#ifndef TARGET
		#include "DEFAULT.h"
	#endif
#endif

#if RTOS_USAGE == TRUE
	#include "RTOS.h"
#endif

/*-------------------------------------------------
           !board special! (remove to other file)
-------------------------------------------------*/
#ifdef	TARGET
#if	TARGET == 0
	#include "TEST.h"
#elif TARGET == 72
	#include "B72.h"
#endif
#endif


#endif

