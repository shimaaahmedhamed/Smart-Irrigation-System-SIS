/*
 * main.c
 *
 *  Created on: Jan 11, 2023
 *      Author: Windows 10
 */

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/GIE/GIE_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "MCAL/UART/USRT_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/semphr.h"
#include "FreeRTOS/task.h"
#include "Tasks/Tasks_Interface.h"
#include "avr/delay.h"

int main(void)
{
/************	Soil Moisture Sensor CONFIG	*****************/
			/*		OUTPUT LOW volt		*/
	DIO_SETPinDirection(PORTA_ID,PIN4_ID,OUTPUT);
	DIO_SETPinValue(PORTA_ID,PIN4_ID,LOW);
			/*	INPUT PULLUP Signal	*/
	DIO_SETPinDirection(PORTA_ID,PIN0_ID,INPUT);
	DIO_SETPinValue(PORTA_ID,PIN0_ID,HIGH);

/*************	Water level Sensor CONFIG	*****************/
			/*		OUTPUT LOW volt		*/
	DIO_SETPinDirection(PORTA_ID,PIN6_ID,OUTPUT);
	DIO_SETPinValue(PORTA_ID,PIN6_ID,LOW);
			/*	INPUT PULLUP Signal	*/
	DIO_SETPinDirection(PORTA_ID,PIN7_ID,INPUT);
	DIO_SETPinValue(PORTA_ID,PIN7_ID,HIGH);

/*****************	Motor Pump CONFIG	*******************/
		/*		OUTPUT LOW volt		*/
	DIO_SETPinDirection(PORTC_ID,PIN7_ID,OUTPUT);
	DIO_SETPinValue(PORTC_ID,PIN7_ID,LOW);

/*****************	Motor Pump CONFIG	*******************/
		/*		OUTPUT LOW volt		*/
	DIO_SETPinDirection(PORTC_ID,PIN6_ID,OUTPUT);
	DIO_SETPinValue(PORTC_ID,PIN6_ID,LOW);

/****************		Initialization		****************/
	/*	Enable GIE	*/
	GIE_VoidEnable();
		/*	LCD INIT	*/
	LCD_voidInit();
		/*	ADC INIT	*/
	ADC_VoidInit();
	/*	UART INIT	*/
	USART_INIT(9600);

/********************	Create tasks	***********************/
	xTaskCreate(soil_moisture_sensor,"Sensor1",100,NULL,2,NULL);
	xTaskCreate(water_level_sensor,"Sensor2",100,NULL,2,NULL);
	xTaskCreate(Pump,"Motor",100,NULL,4,NULL);
	xTaskCreate(Buzzer,"Buzzer",100,NULL,3,NULL);

/*******************	create semaphore	*******************/
	vSemaphoreCreateBinary(Sem);

/***************	Display Strings in LCD		**************/
	/*	Display Strings in LCD */
	LCD_voidWriteString((u8*)"Humidity:");
	LCD_SetCursor(1,0);
	LCD_voidWriteString((u8*)"Water Level: ");



	/*	RTOS Init	*/
	vTaskStartScheduler();

	while(1)
	{

	}

	return 0;
}
