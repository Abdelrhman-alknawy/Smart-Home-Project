/*

 * UART_Program.c
 *
 *  Created on: Apr 11, 2023
 *      Author: Abdelrhman Elknawy
 */
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"

#include"UART_Interface.h"
#include"UART_Private.h"
#include"Uart_Config.h"

void (*ptr)(void) = NULL;
void M_UART_voidInit(void)
{
	/*u8 Local_UCSRC = 0;
	SET_BIT(Local_UCSRC,7); //use UCSRC
	SET_BIT(Local_UCSRC,UCSRC_UCSZ1);//select 8 bits
	SET_BIT(Local_UCSRC,UCSRC_UCSZ0);//select 8 bits

	UCSRC_REG =Local_UCSRC;

	UBRRL_REG =51;//baud rate 9600

	//enable rx and tx
    SET_BIT(UCSRB_REG,UCSRB_TXEN);
    SET_BIT(UCSRB_REG,UCSRB_RXEN);*/
    /**AMGAD SAMIR **/

	u8 Local_UCSRC = 0;
	/*select UCSRC_REG */
	SET_BIT(Local_UCSRC,7);

	/*select async mode */
	CLR_BIT(Local_UCSRC,6);

	/*parity mode (disable)*/
    CLR_BIT(Local_UCSRC,5);
    CLR_BIT(Local_UCSRC,4);

    /*select one stop bit*/
    CLR_BIT(Local_UCSRC,3);

    /*character size 8 bits*/
    SET_BIT(Local_UCSRC,2);
    SET_BIT(Local_UCSRC,1);
    CLR_BIT(UCSRB_REG,UCSRB_UCSZ2);

    UCSRC_REG = Local_UCSRC;
    /*select baud rate register */
    CLR_BIT(UCSRC_REG,UCSRC_URSEL);

    SET_BIT(UCSRB_REG,6);
    /*select baud rate */
    UBRRL_REG = 51;
    /*UBRRH_REG = (u8)(BAUD_RATE>>8);
    UBRRL_REG = (u8)(BAUD_RATE);*/
    /*enable rx and tx */
    SET_BIT(UCSRB_REG,UCSRB_TXEN);
    SET_BIT(UCSRB_REG,UCSRB_RXEN);

}
void M_UART_voidSendData(u8 Copy_u8Data)
{
	/**AMGAD SAMIR**/
    /*polling*/
	//wait until transimtte data empty
	while((GET_BIT(UCSRA_REG,UCSRA_UDRE))==0);
		UDR_REG = Copy_u8Data;
}
u8 M_UART_voidRecieveData(void)
{
     /*POLLING*/
	while((GET_BIT(UCSRA_REG,UCSRA_RXC))==0);
		return UDR_REG;
}

void M_UART_voidSendString(u8 *ptr)
{
	u8 i =0;
	while(ptr[i] != '\0')
	{
		M_UART_voidSendData(ptr[i]);
		i++;
	}
}

void SetCallback(void (*pv)(void))
{
	if(pv != NULL)
	{
		ptr = pv;
	}
}

void __vector_15(void)     __attribute__((signal));
void __vector_15(void)
{
    if(ptr != NULL)
    {
    	ptr();
    }
}
