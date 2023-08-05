/*AUTHOR : Islam Negm / Abdelrhman Elknawy
 *Version : V01
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
#include"../MCAL/TIMER/TIMER_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include"../HAL/KEYPAD/KEYPAD_Interface.h"
#include "../HAL/LCD/LCD_interface.h"
//#include"../HAL/KPD/KPD_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include"../MCAL/ADC/ADC_interface.h"
#include"AppInit.c"
#include"../HAL/DC_MOTOR/DC_MOTOR_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void App_voidInit(void)
{

		TIMER_voidTimer1Init();
		M_UART_voidInit();
		ADC_voidInit();
		DC_MOTOR_VoidInit();
		DIO_voidSetPinDirection(PORTD,PIN0,INPUT);
		DIO_voidSetPinDirection(PORTD,PIN1,OUTPUT);
		DIO_voidSetPinDirection(PORTB,PIN0,OUTPUT);
		DIO_voidSetPinDirection(PORTB,PIN1,OUTPUT);
		DIO_voidSetPinDirection(PORTB,PIN2,OUTPUT);
		DIO_voidSetPinDirection(PORTA,PIN0,INPUT);
		DIO_voidSetPinDirection(PORTD,PIN5,OUTPUT);
		DIO_voidSetPinDirection(PORTC,PIN5,OUTPUT);
		DIO_voidSetPinDirection(PORTC,PIN0,OUTPUT);
		DIO_voidSetPinDirection(PORTC,PIN1,OUTPUT);

}

int main(void)
{

static u8 local_stats = 0;
	App_voidInit();
    u8 read = 0;
    read = M_UART_voidRecieveData();
	while(1)
	{
      switch(read)
      {
      //light
      case 1:
    	  DIO_voidSetPortValue(PORTB,1);
    	  break;
    	  //fan
      case 2:
    	  DIO_voidSetPinValue(PORTC,PIN5,HIGH);
    	  DIO_voidSetPinValue(PORTC,PIN1,LOW);
    	  DIO_voidSetPinValue(PORTC,PIN0,LOW);

    	  break;
      case 3:
    	  DC_MOTOR_VoidDirection(CW);
    	  _delay_ms(3000);
		  DC_MOTOR_VoidStop();
    	  break;
      case 4:
    	  DIO_voidSetPortValue(PORTB,2);

    	  break;
      case 5:
    	  DIO_voidSetPinValue(PORTC,PIN0,HIGH);
    	  DIO_voidSetPinValue(PORTC,PIN5,LOW);
    	  DIO_voidSetPinValue(PORTC,PIN1,LOW);
    	  break;

      case 6:

    	  break;

      case 7:
    	  DIO_voidSetPortValue(PORTB,4);

    	  break;

      case 8:
    	  DIO_voidSetPinValue(PORTC,PIN1,HIGH);
    	  DIO_voidSetPinValue(PORTC,PIN0,LOW);
    	  DIO_voidSetPinValue(PORTC,PIN5,LOW);
    	  break;

      case 9:
    	  DC_MOTOR_VoidDirection(CCW);
    	  _delay_ms(3000);
    	  DC_MOTOR_VoidStop();
    	  break;
      case 10 :
    	  if(local_stats =	= 0)
    	  {
    	  TIMER_voidTimer1ASetCompareValue(999);
			_delay_ms(1000);
			TIMER_voidTimer1ASetCompareValue(1999);
			_delay_ms(1000);
			local_stats =1;
    	  }
    	  break ;
      default:	break;
      }

      read = M_UART_voidRecieveData();
	}
	return 0 ;
}

