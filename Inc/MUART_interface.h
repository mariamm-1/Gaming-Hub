/*
 * UART_interface.h
 *
 *  Created on: Sep 6, 2025
 *      Author: Nour
 */

#ifndef MUART_INTERFACE_H_
#define MUART_INTERFACE_H_

void MUART_voidInit();
void MUART_voidSendData(u8 Copy_u8Data);
u8  MUART_u8Recieve();
void MUART_voidSendString(u8*Copy_pu8Str);
void MUART_voidRecieveString(u8 * Copy_pu8Str);
void MUART_voidSendNumber(u8 number);

#endif /* MUART_INTERFACE_H_ */
