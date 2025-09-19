/*
 * SPI_program.c
 *
 *  Created on: Sep 3, 2025
 *      Author: Nour
 */
#include "bit_math.h"
#include "std_types.h"

#include "MSPI_private.h"
#include "MSPI_interface.h"
#include "MSPI_config.h"

void MSPI_voidMasterInit()
{
	//Hardware or Software (SSM/SSI)
	//SET BITS
	SPI1->CR1|=(1<<SSM);
	SPI1->CR1|=(1<<SSI);
	//Master Mode
	SPI1->CR1|=(1<<MSTR);
	//Direction (Full Duplex)
	SPI1->CR1&=~(1<<BIDIMODE);
	//Data (8-bit or 16-bit)
	SPI1->CR1&=~(1<<DFF);
	//MSB or LSB
	SPI1->CR1&=~(1<<LSBFIRST);
	//CPOL
	SPI1->CR1|=(1<<CPOL);
	//CPHA
	SPI1->CR1&=~(1<<CPHA);
	//Clock
//	SPI1->CR1&=~(CLK_MASK<<BR0);
	//SPE Enable
	SPI1->CR1|=(1<<SPE);
}
void MSPI_voidSlaveInit()
{
	//Hardware Select (SSM is cleared by default)
	//Slave Mode
	SPI1->CR1&=~(1<<MSTR);
	//Direction (Full Duplex)
	SPI1->CR1&=~(1<<BIDIMODE);
	//Data (8-bit or 16-bit)
	SPI1->CR1&=~(1<<DFF);
	//MSB or LSB
	SPI1->CR1&=~(1<<LSBFIRST);
	//CPOL
	SPI1->CR1|=(1<<CPOL);
	//CPHA
	SPI1->CR1&=~(1<<CPHA);
	//Clock
	//SPI1->CR1&=~(CLK_MASK<<BR0);
	//SPE Enable
	SPI1->CR1|=(1<<SPE);
}
u16 MSPI_u16Transcieve(u16 Copy_u16Data)
{
	//wait on TX flag
	while(!GET_BIT(SPI1->SR,TXE));
	SPI1->DR=Copy_u16Data;
	//wait on RX flag
	while(!GET_BIT(SPI1->SR,RXNE));

	return (u16)SPI1->DR; //typecast cause reg. is 32
}
