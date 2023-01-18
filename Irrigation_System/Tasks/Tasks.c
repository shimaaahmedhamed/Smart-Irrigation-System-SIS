/*
 * Tasks.c
 *
 *  Created on: Jan 17, 2023
 *      Author: Windows 10
 */

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/UART/USRT_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/semphr.h"
#include "../FreeRTOS/task.h"
#include "Tasks_Interface.h"
#include "avr/delay.h"

void soil_moisture_sensor_ISR(void)
{
	/*	Local Variable for new value of Global_Soil_percent	*/
	u8 Local_NewData=0;

	/*	ADC Channel Select for soil_moisture_sensor	*/
	ADC_voidChannelSellect(5);

	Global_Soil_percent=(Global_SoilMoisture_Data*100)/700;
	/*	Display Soil Moisture value in LCD	*/
	if(Global_Soil_percent<10)
	{
		LCD_SetCursor(0,9);
		LCD_voidWriteNumber(Global_Soil_percent);
		LCD_SetCursor(0,10);
		LCD_voidWriteChar('%');
		LCD_SetCursor(0,11);
		LCD_voidWriteChar(' ');
	}
	else if(Global_Soil_percent<100)
	{
		LCD_SetCursor(0,9);
		LCD_voidWriteNumber(Global_Soil_percent);
		LCD_SetCursor(0,11);
		LCD_voidWriteChar('%');
	}

	/*	Set the MSB	*/
	Local_NewData = (Global_Soil_percent | 128);

	/*	Send the Data to Gateway	*/
	USART_Transmitter(Local_NewData);

		/*	Turn the sensor off	*/
	DIO_SETPinValue(PORTA_ID,PIN4_ID,LOW);

	/*	Give the Semaphore	*/
	(void)xSemaphoreGive(Sem);
}

void soil_moisture_sensor(void)
{
	u8 SemState ;

	while(1)
	{
		SemState=xSemaphoreTake(Sem,10);
		if(SemState==pdPASS)
		{
			/*	Turn the Soil Moisture sensor on	*/
			DIO_SETPinValue(PORTA_ID,PIN4_ID,HIGH);

			/*	Start Conversion of Soil Moisture sensor	*/
			ADC_StartConversion(&Global_SoilMoisture_Data);

			/*	ADC Call ISR	*/
			ADC_voidSetCallBack(soil_moisture_sensor_ISR);
		}
		else
		{
			/* Do nothing */
		}

		vTaskDelay(3000);
	}
}

void water_level_sensor(void)
{
	u8 SemState ;
	while(1)
	{
		SemState=xSemaphoreTake(Sem,10);
		if(SemState==pdPASS)
		{
			/*	Turn the Soil Moisture sensor on	*/
			DIO_SETPinValue(PORTA_ID,PIN6_ID,HIGH);

			/*	Start Conversion of Soil Moisture sensor	*/
			ADC_StartConversion(&Global_WaterLevel_Data);

			/*	ADC Call ISR	*/
			ADC_voidSetCallBack(water_level_sensor_ISR);
		}
		else
		{
			/* Do nothing */
		}

		vTaskDelay(3000);
	}
}

void water_level_sensor_ISR(void)
{
	/*	Local Variable for new value of Global_Soil_percent	*/
	u8 Local_NewData=0;

	/*	ADC Channel Select for water_leve_sensor	*/
	ADC_voidChannelSellect(7);

	Global_WaterLevel_percent=(Global_WaterLevel_Data*100)/700;

		/*	Display Soil Moisture value in LCD	*/
	if(Global_WaterLevel_percent<10)
	{
		LCD_SetCursor(1,12);
		LCD_voidWriteNumber(Global_WaterLevel_percent);
		LCD_SetCursor(1,13);
		LCD_voidWriteChar('%');
		LCD_SetCursor(1,14);
		LCD_voidWriteChar(' ');
	}
	else if(Global_WaterLevel_percent<100)
	{
		LCD_SetCursor(1,12);
		LCD_voidWriteNumber(Global_WaterLevel_percent);
		LCD_SetCursor(1,14);
		LCD_voidWriteChar('%');
	}

	/*	Clear the MSB	*/
	Local_NewData = (Global_WaterLevel_percent & 127);

	/*	Send the Data to Gateway	*/
	USART_Transmitter(Local_NewData);

		/*	Turn the sensor off	*/
	DIO_SETPinValue(PORTA_ID,PIN6_ID,LOW);

	/*	Give the Semaphore	*/
	(void)xSemaphoreGive(Sem);
}


void Pump(void)
{
	u8 SemState ;

	while(1)
	{
		SemState=xSemaphoreTake(Sem,10);
		if(SemState==pdPASS)
		{
			/********	Motor Status	********/
			if(Global_Soil_percent>=70)
			{
				DIO_SETPinValue(PORTC_ID,PIN7_ID,HIGH);
			}
			else
			{
				DIO_SETPinValue(PORTC_ID,PIN7_ID,LOW);
			}
		}

		else
		{
			/* Do nothing */
		}
		/*	Give the Semaphore	*/
		(void)xSemaphoreGive(Sem);

		vTaskDelay(4000);
	}
}

void Buzzer(void)
{
	u8 SemState ;

	while(1)
	{
		SemState=xSemaphoreTake(Sem,10);
		if(SemState==pdPASS)
		{
			/*	Buzzer Status	*/
			if(15 >= Global_WaterLevel_percent)
			{
				DIO_SETPinValue(PORTC_ID,PIN6_ID,HIGH);
			}
			else
			{
				DIO_SETPinValue(PORTC_ID,PIN6_ID,LOW);
			}
		}

		else
		{
			/* Do nothing */
		}
		/*	Give the Semaphore	*/
		(void)xSemaphoreGive(Sem);

		vTaskDelay(4000);
	}
}
