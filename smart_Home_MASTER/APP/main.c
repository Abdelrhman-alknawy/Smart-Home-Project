/*AUTHOR : Abdelrhman Elknawy
 *Version : V02
 *Date : 6/5/2023
 *Desc: Smart home System based on SuperLoop archtiechture /Static Layers
 *Preiphrals Used :
 *MCAL : DIO / TWI /ADC/GIE/TIMER
 *HAL : LCD / KPD / EEPROM / MOTORS (AC)
 *Services : None
 * */

#include "../LIB/STD_TYPES.h"
#include "../MCAL/TWI/TWI_interface.h"
#include"../MCAL/UART/UART_Interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include"../HAL/KEYPAD/KEYPAD_Interface.h"
#include "../HAL/LCD/LCD_interface.h"
//#include"../HAL/KPD/KPD_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include"../MCAL/ADC/ADC_Interface.h"
#include"../MCAL/TIMER/TIMER_interface.h"
#include"../MCAL/EXTI/EXTI_interface.h"
#include"../MCAL/GIE/GIE_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
u8 Local_u8Flag ;
u8 stats = 0;
void Reset(void) ;
void Appinit(void)
{
	GIE_voidEnableGlobalInterrupt();
	EXTI_VoidInit();
	EXTI_VoidEnable(0,FALLING_EDGE);
	EXTI_SetCallBack_INT0(&Reset);
	DIO_voidSetPinDirection(PORTA,PIN3,OUTPUT);
	M_UART_voidInit();
	ADC_voidInit();
	DIO_voidSetPinDirection(PORTD,PIN0,INPUT);
	DIO_voidSetPinDirection(PORTD,PIN1,OUTPUT);
	DIO_voidSetPinDirection(PORTA,PIN0,INPUT);
	/*keypad initialization*/
	KPD_voidInit();
	DIO_voidSetPinDirection(PORTD,PIN5,OUTPUT);
	DIO_voidSetPinValue(PORTD,PIN5,HIGH);
	/*two wired initialization*/
	TWI_voidInitMaster(0);
	/*Lcd initialization*/
	LCD_voidInit();
}
void Reset(void)
{
	Local_u8Flag = 0 ;
	EEPROM_voidSendDataByte(2,0);
	DIO_voidSetPinValue(PORTA,PIN3,LOW);
}
int main(void)
{


	Appinit();
	for(u8 i = 0 ;  i <= 10 ; i+=5 )
	{
		EEPROM_voidSendWord(i , i);
	}
	u8 keypressed = 255 ;
	u16 data ;
	data = EEPROM_u16ReadWord(0);
	u8 Local_u8ReadFlag = EEPROM_u8ReadDataByte(2);
	u8 Local_u8Iterator =0 ;
	u16 password ;
	u16 reading = ADC_u16GetAnalogReadSYNC(0);
	reading =	(reading*5000UL)/1024;
	u16 temp = reading/10;
	Local_u8Flag = Local_u8ReadFlag;
	while(1)
	{
		if(Local_u8Flag == 3   )
		{
			LCD_voidClearDisplay();
			LCD_voidSendString("No More Tries ");
			_delay_ms(500);
			LCD_voidClearDisplay();
			LCD_voidSendString("Your Blocked ");
			EEPROM_voidSendDataByte(2,Local_u8Flag);
			DIO_voidSetPinValue(PORTA,PIN3,HIGH);
			while(Local_u8Flag ==3 );
		}
		keypressed =255 ;
		Local_u8Iterator = 0 ;
		if(data == 0xffff&&stats==0)
		{
			LCD_voidSendString("First time entry ");
			_delay_ms(500);
			LCD_voidClearDisplay();
			LCD_voidSendString("enter password");

			while(Local_u8Iterator!=4)
			{
				do
				{
					keypressed = KPD_u8GetPressedKey();
				}while(keypressed==255);
				password=(password*10)+keypressed;
				LCD_voidGoToXY(1,Local_u8Iterator);
				LCD_voidSendNumber(keypressed);
				_delay_ms(5);
				LCD_voidGoToXY(1,Local_u8Iterator);
				LCD_voidSendString("*");
				Local_u8Iterator++;
			}
			data = password;
			EEPROM_voidSendWord(0,data);
			stats =1;
		}
		else if(data != 0xffff && stats==0)
		{
			password = 0 ;
			LCD_voidClearDisplay();
			LCD_voidSendString("Welcome again  ");
			_delay_ms(500);
			LCD_voidGoToXY(1,0);
			LCD_voidSendString("Enter Your  Pass :");
			_delay_ms(300);
			LCD_voidClearDisplay();
			data = EEPROM_u16ReadWord(0);
			LCD_voidSendString("password");

			while(Local_u8Iterator!=4)
			{
				do
				{
					keypressed = KPD_u8GetPressedKey();

				}while(keypressed==255);
				password=(password*10)+keypressed;
				LCD_voidGoToXY(1,Local_u8Iterator);
				LCD_voidSendNumber(keypressed);
				_delay_ms(20);
				LCD_voidGoToXY(1,Local_u8Iterator);
				LCD_voidSendString("*");
				Local_u8Iterator++;

			}

		}
	if(password==data||stats==1)
	{
		stats =1 ;
		M_UART_voidSendData(10);
		LCD_voidClearDisplay();
		LCD_voidSendString("Welcome");
		_delay_ms(200);
		LCD_voidClearDisplay();
		LCD_voidGoToXY(0,0);
        LCD_voidSendString("1-ROOM1");
        LCD_voidGoToXY(0,8);
        LCD_voidSendString("2-ROOM2");
        LCD_voidGoToXY(1,0);
        LCD_voidSendString("3-ROOM3");
        keypressed = 255;
        do
        {
        	keypressed = KPD_u8GetPressedKey();
        }while(keypressed == 255);
        LCD_voidClearDisplay();
        switch(keypressed)
        {
        case 1:
        	LCD_voidSendString("Light:1");
			LCD_voidGoToXY(0,8);
			LCD_voidSendString("FAN :2");

			LCD_voidGoToXY(1,0);
			LCD_voidGoToXY(1,5);
			LCD_voidSendString("CURTAINS :3");
        	keypressed = 255;
			do
			{
				keypressed = KPD_u8GetPressedKey();
			}while(keypressed == 255);
			switch(keypressed)
			{
				case 1 :
					M_UART_voidSendData(1);
					break;
				case 2 :
				LCD_voidClearDisplay();
				M_UART_voidSendData(keypressed);
				u16 reading = ADC_u16GetAnalogReadSYNC(0);
				reading =	(reading*5000UL)/1024;
				u16 temp = reading/10;
				LCD_voidSendString("FAN IS ON ");
				_delay_ms(1000);
				LCD_voidGoToXY(1,0);
				LCD_voidSendString("Temp is : " );
				LCD_voidSendNumber(temp);
				_delay_ms(1000);
				break;
				case 3 :
					LCD_voidClearDisplay();
					LCD_voidSendString(" 1 -Open  ");
					_delay_ms(1000);
					LCD_voidGoToXY(1,0);
					LCD_voidSendString("2-  close" );
					keypressed = 255;
					do
					{
					keypressed = KPD_u8GetPressedKey();
					}while(keypressed == 255);
				switch(keypressed)
				{
					case 1 : M_UART_voidSendData(3);
					break ;
					case 2:
						M_UART_voidSendData(9);
						break;
				}

			}
			break;
        case 2:
			LCD_voidClearDisplay();
        	LCD_voidSendString("light:4");
			LCD_voidGoToXY(0,8);
			LCD_voidSendString("fan :5");
			keypressed = 255;
			do
			{
				keypressed = KPD_u8GetPressedKey();
			}while(keypressed == 255);
        switch(keypressed)
				{
        			case 5 :
					LCD_voidClearDisplay();
					M_UART_voidSendData(keypressed);
					u16 reading = ADC_u16GetAnalogReadSYNC(0);
					reading =	(reading*5000UL)/1024;
					u16 temp = reading/10;
					LCD_voidSendString("FAN IS ON ");
					_delay_ms(1000);
					LCD_voidGoToXY(1,0);
					LCD_voidSendString("Temp is : " );
					LCD_voidSendNumber(temp);
					_delay_ms(1000);
					break;
        			case 4 :
					M_UART_voidSendData(4);
					break;

			 	}
        	break;

        case 3:
        	LCD_voidSendString("light:7");
			LCD_voidGoToXY(0,8);
			LCD_voidSendString("fan :8");
			LCD_voidGoToXY(1,0);
			keypressed = 255;
			do
			{
				keypressed = KPD_u8GetPressedKey();
			}while(keypressed == 255);
			switch(keypressed)
				{
				case 8 :
					LCD_voidClearDisplay();
					M_UART_voidSendData(8);
					u16 reading = ADC_u16GetAnalogReadSYNC(0);
					reading =	(reading*5000UL)/1024;
					u16 temp = reading/10;
					LCD_voidSendString("FAN IS ON ");
					_delay_ms(1000);
					LCD_voidGoToXY(1,0);
					LCD_voidSendString("Temp is : " );
					LCD_voidSendNumber(temp);
					_delay_ms(1000);
					break;
				case 7 :
					M_UART_voidSendData(7);
					break;
				}

        	break;
        }
	}
	else
	{
		LCD_voidClearDisplay();
		LCD_voidSendString("Wrong Pass ");
		_delay_ms(500);
		LCD_voidGoToXY(1,0);
		LCD_voidSendString("try again");
		_delay_ms(500);
		Local_u8Flag ++;
	}

	}
	return 0 ;
}

