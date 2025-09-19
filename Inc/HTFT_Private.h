/*
 * HTFT_Private.h
 *
 *  Created on: Sep 3, 2025
 *      Author: Nour
 */

#ifndef HTFT_PRIVATE_H_
#define HTFT_PRIVATE_H_

static void HTFT_voidWriteData(u8 Copy_u8Data);
static void HTFT_voidWriteCommand(u8 Copy_u8CMD);

#define SLEEP_OUT        0x11
#define COLOR_MODE       0x3A
#define DISPLAY_ON       0x29
#define X_DIRECTION      0x2A
#define Y_DIRECTION      0x2B
#define SCREEN_WRITE     0x2C


//IMAGE SIZE
#define IMAGE_SIZE       20480

//RGB565
#define RGB565           0x05


#endif /* HTFT_PRIVATE_H_ */
