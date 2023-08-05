
/* Library Layer */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* Lower Layer */
#include "../../MCAL/DIO/DIO_interface.h"

/* Self Files */
#include"LCD_interface.h"
#include"LCD_config.h"
#include"LCD_private.h"

#include <util/delay.h>



void LCD_voidSendCommand(u8 Copy_u8Command)
{
	/* Set The RS Pin To Be Low: 0v for Command */
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, LOW);
	
	/* Set The RW Pin To Be Low: 0v for Write */
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
	
	/* Set The Port Value To Be The Command */
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Command);
	
	/* Set The Enable Pin To High*/
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
	
	/* Wait For 2msec */
	_delay_ms(2);
	
	/* Set The Enable Pin To Low*/
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN,LOW);
	
}


void LCD_voidSendData(u8 Copy_u8Data)
{
	/* Set The RS Pin To Be High: 5v for Data */
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, HIGH);
	
	/* Set The RW Pin To Be Low: 0v for Write */
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, LOW);
	
	/* Set The Port Value To Be The Data */
	DIO_voidSetPortValue(LCD_DATA_PORT, Copy_u8Data);
	
	/* Set The Enable Pin To High*/
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, HIGH);
	
	/* Wait For 2msec */
	_delay_ms(2);
	
	/* Set The Enable Pin To Low*/
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, LOW);
	
}

void LCD_voidInit(void)
{
	/* Set The Data Port To Be Output */
	DIO_voidSetPortDirection(LCD_DATA_PORT, OUTPUT);
	
	/* Set The Control Pins To Be Output */
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_EN_PIN, OUTPUT);
	/* Wait For 40msec*/
	_delay_ms(40);
	/* Send The Function set, N: 1 => 2-Lines, F: 0 => 5*8 dots*/
	LCD_voidSendCommand(0x38);
	LCD_voidSendCommand(0x0F);
	LCD_voidSendCommand(0x01);
	
}



void LCD_voidGoToXY(u8 Copy_u8XPosition, u8 Copy_u8YPosition)
{
	u8 Local_u8Address = 0;
	/* Check if we are at the first row */
	if(Copy_u8XPosition == 0)
	{
		Local_u8Address = Copy_u8YPosition;
	}
	/* Check if we are at the second row */
	else if(Copy_u8XPosition == 1)
	{
		/* Add 0x40 To The Y-Position */
		Local_u8Address = Copy_u8YPosition + 0x40;
	}
	/* Set The 8th Bit to be 1 */
	SET_BIT(Local_u8Address, 7);
	/* Send The Set Address Of DDRAM */
	LCD_voidSendCommand(Local_u8Address);
}

void LCD_voidSendString(u8 * Copy_pu8String)
{
	u8 Local_u8LoopCounter = 0;
	while(Copy_pu8String[Local_u8LoopCounter] != '\0')
	{
		LCD_voidSendData(Copy_pu8String[Local_u8LoopCounter]);
		Local_u8LoopCounter++;
	}
}


void LCD_voidSendCustomCharacter(
								u8 * Copy_pu8CharacterArray, 
								u8 Copy_u8PatternNum,
								u8 Copy_u8XPosition,
								u8 Copy_u8YPosition)
{
	u8 Local_u8LoopCounter;
	u8 Local_u8CGRAMAddress;
	/* Calculate the CGRAM Address = PatternNum * 8 */
	Local_u8CGRAMAddress = Copy_u8PatternNum * 8;
	SET_BIT(Local_u8CGRAMAddress, 6);
	/* Send Set CGRAM Address */
	LCD_voidSendCommand(Local_u8CGRAMAddress);
	for(Local_u8LoopCounter = 0; Local_u8LoopCounter < 8; Local_u8LoopCounter++)
	{
		/* Send Byte from The CharacterArray */
		LCD_voidSendData(Copy_pu8CharacterArray[Local_u8LoopCounter]);	
	}
	/* Send The Command To Set DDRAM Address */
	LCD_voidGoToXY(Copy_u8XPosition, Copy_u8YPosition);
	/* Display the pattern From the CGRAM */ 
	LCD_voidSendData(Copy_u8PatternNum);
}

void LCD_voidSendNumber(u16 Copy_u16Number)
{
	u8 Local_u8Result[10];
	s8 Local_s8LoopCounter=0;
	u8 Local_u8NumOfIterations = 0;
	if(Copy_u16Number == 0)
	{
		LCD_voidSendData('0');
	}
	else if(Copy_u16Number > 0)
	{
		while(Copy_u16Number != 0)
		{
			Local_u8Result[Local_s8LoopCounter] = Copy_u16Number % 10;
			Copy_u16Number /= 10;
			Local_s8LoopCounter++;
			Local_u8NumOfIterations++;
		}
		for(Local_s8LoopCounter = (Local_u8NumOfIterations-1); Local_s8LoopCounter>=0; Local_s8LoopCounter--)
		{
			LCD_voidSendData(Local_u8Result[Local_s8LoopCounter] + '0');
		}
	}


}


void LCD_voidClearDisplay(void)
{
	LCD_voidSendCommand(CLEAR_COMMAND);
}

