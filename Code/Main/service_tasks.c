/*************************************************
* File Name          : service_tasks.c
* Author             : Tatarchenko S.
* Version            : v 1.0
* Description        : ---
**************************************************/
#include "service_tasks.h"
/*----------- global variables-------------------*/
/*semaphore for I/O pool*/
xSemaphoreHandle InputEvent;
/*----------- local variables--------------------*/
uint32_t BlinkFrequency; //LED flashing frequency

/*mutex for I2C , perform correct transmit */
xSemaphoreHandle xMutex_BUS_BUSY;

/*************************************************
 Initial configuration and start other tasks
*************************************************/
void StartInit(void *pvParameters){	
	_Bool state;
	Core_Init();
	
	/**/
	InputEvent = xSemaphoreCreateCounting(3,0);
	xMutex_BUS_BUSY = xSemaphoreCreateMutex();
	//
	state = Get_IO_State();
	
	/*start other tasks*/
	
	/*high level tasks*/
	if(state){
		/*run with higher priority (use I2C)*/
		xTaskCreate(vGetIOState,"I/O pool ", configMINIMAL_STACK_SIZE, NULL, 6, NULL );	
	
		/*start diagnostic of charging device*/
		xTaskCreate(vTestHardvare,"diagnostic", configMINIMAL_STACK_SIZE, NULL, 3, NULL );
	
		vTaskDelete(NULL); /*delete task*/		
	}else{
		/*internal error, loading aborted*/
		
		/*start error handling task*/
		xTaskCreate(vInternalErrorHandler,"error handling", configMINIMAL_STACK_SIZE, NULL, 10, NULL );
		
		// add error handler
		vTaskDelete(NULL); /*delete task*/
	}
}
/*************************************************
the task is performed on a semaphore "InputEvent"
*************************************************/
void vGetIOState(void *pvParameters){
	UBaseType_t SemaphoreCount;
	for(;;){
		/*the task is waiting for the semaphore */
		xSemaphoreTake(InputEvent,portMAX_DELAY);
		/*task take the semaphore */
		
		xSemaphoreTake(xMutex_BUS_BUSY,portMAX_DELAY);
		/*get current IO state*/
		if(!Get_IO_State()){
			// internal circuit error (add handler)
		}
		xSemaphoreGive(xMutex_BUS_BUSY);
			
		SemaphoreCount = uxSemaphoreGetCount(InputEvent);	
		if(SemaphoreCount > 1){
			//error overclocking IO port(add handler)
		}
	}
	//vTaskDelete(NULL);
}
/*************************************************
internal error handler task (max priority )
*************************************************/
void vInternalErrorHandler(void *pvParameters){
	
	ResetIO_Model();  
	LED_OFF;
	for(;;){
		vTaskDelay(1500);
		/* add sending error message handler (USART)*/
	}
	
}
/*************************************************
LED blink (get blink frequency in ms
as task parameter)
*************************************************/
void vBlinker (void *pvParameters){
	
	volatile TickType_t *BlinkFreq;
	BlinkFreq =(TickType_t*)pvParameters;
	
	for(;;){	
		LED_ON;
		vTaskDelay(*BlinkFreq);			
		LED_OFF;
		vTaskDelay(*BlinkFreq);			
	}
}

/*************************************************
 diagnostic of hardware state (external ADC,
 check input and output state of MCP23017 )
*************************************************/
void vTestHardvare(void *pvParameters){
	
	/*test blink*/
	BlinkFrequency = 500;
	xTaskCreate(vBlinker, "blink", configMINIMAL_STACK_SIZE,(void*)&BlinkFrequency, 4, NULL );	
		
	for(;;){
		DMA_Ch4_Reload(USART1_DEFAULT_BUF_SIZE);
		xSemaphoreTake(xMutex_BUS_BUSY,portMAX_DELAY);
		Get_IO_State();
		xSemaphoreGive(xMutex_BUS_BUSY);
		vTaskDelay(1500);
	}
//	vTaskDelete(NULL); /*delete task*/
	
}