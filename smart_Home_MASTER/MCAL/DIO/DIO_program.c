#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"



void DIO_voidSetPinDirection(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinMode)
{
	switch(Copy_u8PortName)
	{
		case PORTA:
			if(Copy_u8PinMode == INPUT)
			{
				CLR_BIT(DIO_DDRA, Copy_u8PinNumber);
			}
			else
			{
				SET_BIT(DIO_DDRA, Copy_u8PinNumber);
			}
			break;

		case PORTB:
			if(Copy_u8PinMode == INPUT)
			{
				CLR_BIT(DIO_DDRB, Copy_u8PinNumber);
			}
			else
			{
				SET_BIT(DIO_DDRB, Copy_u8PinNumber);
			}
			break;

		case PORTC:
			if(Copy_u8PinMode == INPUT)
			{
				CLR_BIT(DIO_DDRC, Copy_u8PinNumber);
			}
			else
			{
				SET_BIT(DIO_DDRC, Copy_u8PinNumber);
			}
			break;

		case PORTD:
			if(Copy_u8PinMode == INPUT)
			{
				CLR_BIT(DIO_DDRD, Copy_u8PinNumber);
			}
			else
			{
				SET_BIT(DIO_DDRD, Copy_u8PinNumber);
			}
			break;
			
			
		default:
			break;
	}
}

void DIO_voidSetPinValue(u8 Copy_u8PortName, u8 Copy_u8PinNumber, u8 Copy_u8PinState)
{
	switch(Copy_u8PortName)
	{
		case PORTA:
			if (Copy_u8PinState == HIGH) // INPUT_PULLUP
			{
				SET_BIT(DIO_PORTA, Copy_u8PinNumber);
			}
			else		// DIO_LOW		INPUT_NOPULLUP
			{
				CLR_BIT(DIO_PORTA, Copy_u8PinNumber);
			}
		break;
		
		case PORTB:
			if (Copy_u8PinState == HIGH) // INPUT_PULLUP
			{
				SET_BIT(DIO_PORTB, Copy_u8PinNumber);
			}
			else		// DIO_LOW		INPUT_NOPULLUP
			{
				CLR_BIT(DIO_PORTB, Copy_u8PinNumber);
			}
		break;

		case PORTC:
			if (Copy_u8PinState == HIGH) // INPUT_PULLUP
			{
				SET_BIT(DIO_PORTC, Copy_u8PinNumber);
			}
			else		// DIO_LOW		INPUT_NOPULLUP
			{
				CLR_BIT(DIO_PORTC, Copy_u8PinNumber);
			}
			break;

		case PORTD:
			if (Copy_u8PinState == HIGH) // INPUT_PULLUP
			{
				SET_BIT(DIO_PORTD, Copy_u8PinNumber);
			}
			else		// DIO_LOW		INPUT_NOPULLUP
			{
				CLR_BIT(DIO_PORTD, Copy_u8PinNumber);
			}
			break;

	}
}


//DDRA =  0b00000000;			// Bit (Pin) 0 in Port A is input
//PORTA = 0b00000001;			// Bit (Pin) 0 in port A has pull up resistor turned on  



void DIO_voidSetPortDirection(u8 Copy_u8PortName, u8 Copy_u8PortMode)
{
	switch(Copy_u8PortName)
	{
		case PORTA:
			if(Copy_u8PortMode == OUTPUT)
			{
				DIO_DDRA = OUTPUT_PORT_VALUE;
			}
			else if(Copy_u8PortMode == INPUT)
			{
				DIO_DDRA = INPUT_PORT_VALUE;
			}
		break;
		
		case PORTB:
			if(Copy_u8PortMode == OUTPUT)
			{
				DIO_DDRB = OUTPUT_PORT_VALUE;
			}
			else if(Copy_u8PortMode ==INPUT)
			{
				DIO_DDRB = INPUT_PORT_VALUE;
			}
		break;

		case PORTC:
			if(Copy_u8PortMode == OUTPUT)
			{
				DIO_DDRC = OUTPUT_PORT_VALUE;
			}
			else if(Copy_u8PortMode == INPUT)
			{
				DIO_DDRC = INPUT_PORT_VALUE;
			}
		break;

		case PORTD:
			if(Copy_u8PortMode ==OUTPUT)
			{
				DIO_DDRD = OUTPUT_PORT_VALUE;
			}
			else if(Copy_u8PortMode == INPUT)
			{
				DIO_DDRD = INPUT_PORT_VALUE;
			}
		break;

	}
}


void 	DIO_voidSetPortValue(u8 Copy_u8PortName, u8 Copy_u8Value)
{
	switch(Copy_u8PortName)
	{
		case PORTA: 
			DIO_PORTA = Copy_u8Value;
		break;
		
		case PORTB:
			DIO_PORTB = Copy_u8Value;
		break;

		case PORTC:
			DIO_PORTC = Copy_u8Value;
		break;

		case PORTD:
			DIO_PORTD = Copy_u8Value;
		break;

	}
}

u8 DIO_u8GetPinValue(u8 Copy_u8PortName, u8 Copy_u8PinNumber)
{
	u8 Local_u8PinValue;
	switch(Copy_u8PortName)
	{
		case PORTA:
			Local_u8PinValue = GET_BIT(DIO_PINA, Copy_u8PinNumber);
		break;
		
		case PORTB:
			Local_u8PinValue = GET_BIT(DIO_PINB, Copy_u8PinNumber);
		break;
		
		case PORTC:
			Local_u8PinValue = GET_BIT(DIO_PINC, Copy_u8PinNumber);
		break;
		
		case PORTD:
			Local_u8PinValue = GET_BIT(DIO_PIND, Copy_u8PinNumber);
		break;
		
		default:
			/* Error To Be Displayed */
		break;
	}
	
	return Local_u8PinValue;
}
