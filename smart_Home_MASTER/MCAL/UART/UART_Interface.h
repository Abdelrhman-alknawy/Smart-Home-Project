/*
 * UART_Interface.h
 *
 *  Created on: Apr 11, 2023
 *      Author: Dell
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

void M_UART_voidInit(void);
void M_UART_voidSendData(u8 Copy_u8Data);
u8 M_UART_voidRecieveData(void);
void M_UART_voidSendString(u8 *ptr);
void SetCallback(void (*pv)(void));
#endif /* MCAL_UART_UART_INTERFACE_H_ */
