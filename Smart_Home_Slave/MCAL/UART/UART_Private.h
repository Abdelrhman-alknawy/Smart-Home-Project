/*
 * UART_Private.h
 *
 *  Created on: Apr 11, 2023
 *      Author: Abdelrhman Elknawy
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#define UDR_REG          *((volatile u8*)0x2C)/*send and recieve from it*/

#define UCSRA_REG        *((volatile u8*)0x2B)//control register
#define UCSRA_RXC        7
#define UCSRA_TXC        6
#define UCSRA_UDRE       5
#define UCSRA_FE         4
#define UCSRA_DOR        3
#define UCSRA_PE         2
#define UCSRA_U2X        1
#define UCSRA_MPCM       0


#define UCSRB_REG        *((volatile u8*)0x2A) /*control register*/
#define UCSRB_RXCIE       7
#define UCSRB_TXCIE       6
#define UCSRB_UDRIE       5
#define UCSRB_RXEN        4
#define UCSRB_TXEN        3
#define UCSRB_UCSZ2       2
#define UCSRB_RXB8        1
#define UCSRB_TXB8        0

#define UCSRC_REG        *((volatile u8*)0x40)/*status register*/
#define UCSRC_URSEL        7
#define UCSRC_UMSEL        6
#define UCSRC_UPM1         5
#define UCSRC_UPM0         4
#define UCSRC_USBS         3
#define UCSRC_UCSZ1        2
#define UCSRC_UCSZ0        1
#define UCSRC_UCPOL        0
#define UBRRH_REG        *((volatile u8*)0x40)/*high*/ /*baud rate*/
#define UBRRH_URSEL        7

#define UBRRL_REG        *((volatile u8*)0x29)/*low*/ /*baud rate*/



#endif /* MCAL_UART_UART_PRIVATE_H_ */
