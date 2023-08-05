/*
 * KEYPAD_Program.c
 *
 *  Created on: Mar 29, 2023
 *      Author: abdelrhman
 */
#include <avr/delay.h>
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"../../MCAL/DIO/DIO_interface.h"
#include"KEYPAD_Interface.h"
#include"KEYPAD_Config.h"
#include"../LCD/LCD_Interface.h"
u8 Local_Au8Cols_Num[KEYPAD_COLUM] = { KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3, KEYPAD_COL4};
u8 Local_Au8Rows_Num[KEYPAD_ROWS] = { KEYPAD_R0, KEYPAD_R1, KEYPAD_R2, KEYPAD_R3};
u8  Local_Au8KeysArr[KEYPAD_ROWS][KEYPAD_COLUM]=KEYPAD_KEYS;
//...........................      .//
//.SWC:KPD_voidInit	..........     //
//.I/O : VOID ...............     //
//.RETURN : VOID  ..........     //
//.Desc:Initilazing KEYPAD..    //
//.............................//
void KPD_voidInit(void)
{
	DIO_voidSetPinDirection(KEYPAD_PORT_COL,KEYPAD_COL1,OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT_COL,KEYPAD_COL2,OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT_COL,KEYPAD_COL3,OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT_COL,KEYPAD_COL4,OUTPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT_RO,KEYPAD_R0,INPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT_RO,KEYPAD_R1,INPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT_RO,KEYPAD_R2,INPUT);
	DIO_voidSetPinDirection(KEYPAD_PORT_RO,KEYPAD_R3,INPUT);
	DIO_voidSetPinValue(PORTD,KEYPAD_COL1,HIGH);
	DIO_voidSetPinValue(PORTD,KEYPAD_COL2,HIGH);
	DIO_voidSetPinValue(PORTD,KEYPAD_COL3,HIGH);
	DIO_voidSetPinValue(PORTD,KEYPAD_COL4,HIGH);

	DIO_voidSetPinValue(PORTC,KEYPAD_R0,HIGH);
	DIO_voidSetPinValue(PORTC,KEYPAD_R1,HIGH);
	DIO_voidSetPinValue(PORTC,KEYPAD_R2,HIGH);
	DIO_voidSetPinValue(PORTC,KEYPAD_R3,HIGH);
}

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8Pinvalue;
	u8 Local_PressedKey=255;
	u8 Local_u8ColsIterator;
	u8 Local_u8RowsIterator;
	u8 Local_u8Flag =0;
for( Local_u8ColsIterator=0;Local_u8ColsIterator<4;Local_u8ColsIterator++ )
{
    //DEACTIVATE CURRENT COL
	DIO_voidSetPinValue(KEYPAD_PORT_COL,Local_Au8Cols_Num[Local_u8ColsIterator],LOW);
	for( Local_u8RowsIterator=0;Local_u8RowsIterator<4;Local_u8RowsIterator++ )
	{
		Local_u8Pinvalue=DIO_u8GetPinValue(KEYPAD_PORT_RO,Local_Au8Rows_Num[Local_u8RowsIterator]);
		if(Local_u8Pinvalue==0)
		{
		Local_u8Pinvalue=DIO_u8GetPinValue(KEYPAD_PORT_RO,Local_Au8Rows_Num[Local_u8RowsIterator]);
		while(Local_u8Pinvalue==0)
		{
			Local_u8Pinvalue=DIO_u8GetPinValue(KEYPAD_PORT_RO,Local_Au8Rows_Num[Local_u8RowsIterator]);
		}
		Local_PressedKey=Local_Au8KeysArr[Local_u8RowsIterator][Local_u8ColsIterator];
		Local_u8Flag =1 ;
		break;
		}
	}
	DIO_voidSetPinValue(KEYPAD_PORT_COL,Local_Au8Cols_Num[Local_u8ColsIterator],HIGH);
	if(Local_u8Flag==1 )
	{
		break;
	}
}
return Local_PressedKey ;
}
