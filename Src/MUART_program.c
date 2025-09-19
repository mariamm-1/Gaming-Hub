/*
 * UART_program.c
 *
 *  Created on: Sep 6, 2025
 *      Author: Nour
 */

#include "std_types.h"
#include "bit_math.h"
#include "MGPIO_private.h"
#include "MGPIO_interface.h"
#include "MUART_Private.h"
#include "MUART_interface.h"

void MUART_voidInit(void)
{

	//Oversampling=16
	UART1->CR1.OVER8=0;
	//Baudrate=9600
	UART1->BRR = 0x683; /*16MHZ/9600=1667*/
//	UART1->BRR = 0x8B;  // for 115200 baud at 16MHz

	//Word length=8 bit
	UART1->CR1.M=0;
	//Disable parity
	UART1->CR1.PCE=0;
	//Enable transmitter
	UART1->CR1.TE=1;
	//Enable reciever
	UART1->CR1.RE=1;
	//Enable UART
	UART1->CR1.UE=1;
}


void MUART_voidSendData(u8 Copy_u8Data)
{
    // Wait until TXE (Transmit Data Register Empty)
    while(!(UART1->SR & (1 << 7)));

    UART1->DR = Copy_u8Data;
}

u8 MUART_u8Recieve(void)
{
    // Wait until RXNE (Read Data Register Not Empty)
    while(!(UART1->SR & (1 << 5)));

    return (u8)(UART1->DR & 0xFF);
}

void MUART_voidSendString(u8* Copy_pu8Str)
{
    while(*Copy_pu8Str != '\0')
    {
        MUART_voidSendData(*Copy_pu8Str);
        Copy_pu8Str++;
    }
}

void MUART_voidRecieveString(u8* Copy_pu8Str)
{
    u8 Local_u8Char;
    do {
        Local_u8Char = MUART_u8Recieve();
        *Copy_pu8Str = Local_u8Char;
        Copy_pu8Str++;
    } while(Local_u8Char != '\r' && Local_u8Char != '\n'); // stop on Enter key

    *Copy_pu8Str = '\0';  // Null-terminate string
}

void MUART_voidSendNumber(u8 number)
{
    char buffer[5];   // enough for 3 digits + \r\n
    u8 i = 0;

    // convert number to string (manual itoa)
    if(number == 0)
    {
        MUART_voidSendData('0');
    }
    else
    {
        char temp[5];
        while(number > 0)
        {
            temp[i++] = (number % 10) + '0';
            number /= 10;
        }
        while(i > 0)
        {
            MUART_voidSendData(temp[--i]);
        }
    }

    MUART_voidSendData('\r'); // new line
    MUART_voidSendData('\n');
}
