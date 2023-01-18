/*
 * LCD_Program.c

 *
 *  Created on: Nov 11, 2022
 *      Author: Windows 10
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "util/delay.h"
#include "../../MCAL//DIO/DIO_Interface.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"



void LCD_voidWriteBitsToSend(u8 copy_u8Byte)
{

	//DIO_SETPinValue(RW_PORT,RW_PIN, LOW);
	DIO_SETPinValue(EN_PORT,EN_PIN, LOW);




	DIO_SETPinValue(D7_PORT,D7_PIN, (copy_u8Byte>> 7) & 1);
	DIO_SETPinValue(D6_PORT,D6_PIN, (copy_u8Byte>> 6) & 1);
	DIO_SETPinValue(D5_PORT,D5_PIN, (copy_u8Byte>> 5) & 1);
	DIO_SETPinValue(D4_PORT,D4_PIN, (copy_u8Byte>> 4) & 1);

	DIO_SETPinValue(EN_PORT,EN_PIN, HIGH);
	_delay_ms(1);
	DIO_SETPinValue(EN_PORT,EN_PIN, LOW);
	_delay_ms(30);

	DIO_SETPinValue(D7_PORT,D7_PIN, (copy_u8Byte>> 3) & 1);
	DIO_SETPinValue(D6_PORT,D6_PIN, (copy_u8Byte>> 2) & 1);
	DIO_SETPinValue(D5_PORT,D5_PIN, (copy_u8Byte>> 1) & 1);
	DIO_SETPinValue(D4_PORT,D4_PIN, (copy_u8Byte>> 0) & 1);

	DIO_SETPinValue(EN_PORT,EN_PIN, HIGH);
	_delay_ms(1);
	DIO_SETPinValue(EN_PORT,EN_PIN, LOW);
	_delay_ms(30);



}


void LCD_voidInit(void)
{
	_delay_ms(30);

	DIO_SETPinDirection(RS_PORT,RS_PIN,OUTPUT);
	//DIO_SETPinDirection(RW_PORT,RW_PIN,OUTPUT);
	DIO_SETPinDirection(EN_PORT, EN_PIN,OUTPUT);


	DIO_SETPinDirection(D4_PORT,D4_PIN,OUTPUT);
	DIO_SETPinDirection(D5_PORT,D5_PIN,OUTPUT);
	DIO_SETPinDirection(D6_PORT,D6_PIN,OUTPUT);
	DIO_SETPinDirection(D7_PORT,D7_PIN,OUTPUT);




	LCD_voidWriteCommand(0x02);
    _delay_ms(2);

	LCD_voidWriteCommand(0x2C);
	_delay_ms(2);

	LCD_voidWriteCommand(0x0C);
	_delay_ms(2);

	LCD_voidWriteCommand(0x01);

	_delay_ms(2);

	LCD_voidWriteCommand(0x06 );

}
void LCD_voidWriteData(u8 copy_u8data)
{

	DIO_SETPinValue(RS_PORT,RS_PIN,HIGH);


	LCD_voidWriteBitsToSend(copy_u8data);
}
void LCD_voidWriteCommand(u8 copy_u8Command)
{
	DIO_SETPinValue(RS_PORT,RS_PIN,LOW);



	LCD_voidWriteBitsToSend(copy_u8Command);
}
void LCD_voidWriteString(u8 * copy_str)
{
	u32 i= 0;
	while(copy_str[i] != '\0')
	{
		LCD_voidWriteData(copy_str[i]);
		i++;
	}
}

void LCD_voidWriteChar(u8 CharData)
{
	LCD_voidWriteData(CharData);
}

void LCD_SetCursor(u8 Row , u8 Col)
{
	switch(Row)
	{
		case Row0 : LCD_voidWriteCommand( ((0x80) |Col ) );  break;
		case Row1 : LCD_voidWriteCommand( ((0x80) | (0x40) | Col ) );  break;
		default :  break;
	}

}

void LCD_voidClear(void)
{
	LCD_voidWriteCommand( 0x01);
}

//	void LCD_voidPrintNumber(u16 number)   //to display number like 123 char by char
//	{
//		u8 i =-1;
//		u8 x;
//		 u8 NumberIndex[10];
//
//		while(number != 0);
//		{
//			i++;
//			x=number % 10;
//			number /= 10;
//			NumberIndex[i] = x;
//
//		}
//		while(i >= 0)
//		{
//			LCD_voidWriteData(NumberIndex[i]);
//			i--;
//		}
//
//	}
void LCD_voidWriteNumber( u32 Copy_u8num )
{
	u32 LOCAL_NUMBER=Copy_u8num ;
	u8 LOCAL_ARR[10] ,i=0 ;

	do
	{
		LOCAL_ARR[i]= ((LOCAL_NUMBER%10)+48);
		LOCAL_NUMBER=LOCAL_NUMBER/10 ;

		i++ ;
	}
	while(LOCAL_NUMBER!=0);
	/*
	if(Copy_u8num==0)
		{
				LCD_voidWriteData(48);
		}*/

	for(;i>0;i--)
	{
		LCD_voidWriteData(LOCAL_ARR[i-1]);
	}

}
