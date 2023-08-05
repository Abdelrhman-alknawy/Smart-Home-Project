/*
 * Program.c
 *
 *  Created on: Apr 1, 2023
 *      Author: abdelrhman
 */
#include <avr/delay.h>
#include"..\..\LIB\STD_TYPES.h"
#include"..\..\LIB\BIT_MATH.h"
#include"..\..\MCAL\DIO\DIO_Interface.h"
#include"DC_MOTOR_Interface.h"
#include"../../MCAL/DIO/DIO_Private.h"
#include"DC_MOTOR_Config.h"

void DC_MOTOR_VoidInit(void)
{
	DIO_voidSetPinDirection(MOTOR_PORT,MOTOR_PIN1,OUTPUT);
	DIO_voidSetPinDirection(MOTOR_PORT,MOTOR_PIN2,OUTPUT);
}

void DC_MOTOR_VoidDirection(u8 Copy_u8Direction)
{
	switch(Copy_u8Direction)
	{
			case CCW :
				DIO_voidSetPinValue(MOTOR_PORT,MOTOR_PIN2,LOW);
				DIO_voidSetPinValue(MOTOR_PORT,MOTOR_PIN1,HIGH);

							break ;
			case CW	:
				DIO_voidSetPinValue(MOTOR_PORT,MOTOR_PIN1,LOW);
				DIO_voidSetPinValue(MOTOR_PORT,MOTOR_PIN2,HIGH);
							break;
	}
}

void DC_MOTOR_VoidStop()
{
	DIO_voidSetPinValue(MOTOR_PORT,MOTOR_PIN1,LOW);
	DIO_voidSetPinValue(MOTOR_PORT,MOTOR_PIN2,LOW);
}
