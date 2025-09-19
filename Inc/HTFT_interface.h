/*
 * HTFT_interface.h
 *
 *  Created on: Sep 3, 2025
 *      Author: Nour
 */

#ifndef HTFT_INTERFACE_H_
#define HTFT_INTERFACE_H_

void HTFT_voidInit();
void HTFT_voidDisplay(const u16*Copy_pu16PTR);
void HTFT_voidReset();

void HTFT_voidfillColor(u16 color);
void HTFT_voidFillRect(u8 x1, u8 y1, u8 x2, u8 y2, u16 color);
void HTFT_voidPrintText8x8(char *str, u16 x, u16 y, u16 textColor, u16 bgColor);


#endif /* HTFT_INTERFACE_H_ */
