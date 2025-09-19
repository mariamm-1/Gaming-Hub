/*
 * MSPI_private.h
 *
 *  Created on: Sep 3, 2025
 *      Author: Nour
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

//SPI_CR1 B3DIH SPI_CR2 bs hwa nesih fel register map

#define MSPI_BASE_ADDRESS       (0x40013000)

typedef struct{

	u32 CR1;
	u32 CR2;
	u32 SR;
	u32 DR;
	u32 CRCPR;
	u32 RXCRCR;
	u32 TXCRCR;
	u32 I2SCFGR;
	u32 I2SPR;

}MSPI_t;


#define SPI1 ((volatile MSPI_t*)MSPI_BASE_ADDRESS)

#define BIDIMODE       15
#define DFF            11
#define SSM            9
#define SSI            8
#define LSBFIRST       7
#define SPE            6
#define MSTR           2
#define CPOL           1
#define CPHA           0

#define BR0            3

#define TXE            1
#define RXNE           0

#define CLK_MASK       7

#endif /* SPI_PRIVATE_H_ */
