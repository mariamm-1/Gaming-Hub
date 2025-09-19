/*
 * UART_Private.h
 *
 *  Created on: Sep 6, 2025
 *      Author: Nour
 */

#ifndef MUART_PRIVATE_H_
#define MUART_PRIVATE_H_


#define UART1_BASE_ADDRESS  (0x40011000)


typedef struct{
	u32 SBK:1;
	u32 RWU:1;
	u32 RE:1;
	u32 TE:1;
	u32 IDLETE:1;
	u32 RXNDIE:1;
	u32 TCIE:1;
	u32 TXEIE:1;
	u32 PEIE:1;
	u32 PS:1;
	u32 PCE:1;
	u32 WAKE:1;
	u32 M:1;
	u32 UE:1;
	u32 Reserved1:1;
	u32 OVER8:1;
	u32 Reserved2:16;
}MUART_CR1;


typedef struct{

	u32 SR;
	u32 DR;
	u32 BRR;
	MUART_CR1 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;

}MUART_t;

#define UART1 ((volatile MUART_t*)UART1_BASE_ADDRESS)


#endif /* MUART_PRIVATE_H_ */
