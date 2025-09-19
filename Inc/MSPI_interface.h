/*
 * MSPI_interface.h
 *
 *  Created on: Sep 3, 2025
 *      Author: Nour
 */

#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

void MSPI_voidMasterInit();
void MSPI_voidSlaveInit();
u16 MSPI_u16Transcieve(u16 Copy_u16Data);

#endif /* MSPI_INTERFACE_H_ */
