/*
 * HTFT_program.c
 *
 *  Created on: Sep 3, 2025
 *      Author: Nour
 */
#include "std_types.h"
#include "bit_math.h"

#include "MGPIO_interface.h"
#include "MSTK_interface.h"
#include "MSPI_interface.h"

#include "HTFT_interface.h"
#include "HTFT_Private.h"
#include "HTFT_Config.h"


static void HTFT_voidWriteData(u8 Copy_u8Data)
{
	MGPIO_voidSetPinValue(TFT_PORT,CONTROL_PIN,PIN_High);
	(void)MSPI_u16Transcieve(Copy_u8Data);
}
static void HTFT_voidWriteCommand(u8 Copy_u8CMD)
{
    MGPIO_voidSetPinValue(TFT_PORT,CONTROL_PIN,PIN_Low);
	(void)MSPI_u16Transcieve(Copy_u8CMD);
}
void HTFT_voidDisplay(const u16*Copy_pu16PTR)
{

	u16 Local_u16Iterator;
	u8 Local_u8HighPart,Local_u8LowPart;

	//Set X
	HTFT_voidWriteCommand(X_DIRECTION);
	HTFT_voidWriteData(START_X_B0);
	HTFT_voidWriteData(START_X_B1);
	HTFT_voidWriteData(END_X_B0);
	HTFT_voidWriteData(END_X_B1);

   //Set Y
	HTFT_voidWriteCommand(Y_DIRECTION);
	HTFT_voidWriteData(START_Y_B0);
	HTFT_voidWriteData(START_Y_B1);
	HTFT_voidWriteData(END_Y_B0);
	HTFT_voidWriteData(END_Y_B1);

	//Write on the screen
	HTFT_voidWriteCommand(SCREEN_WRITE);

	for(Local_u16Iterator=0;Local_u16Iterator<IMAGE_SIZE;Local_u16Iterator++)
	{
		Local_u8LowPart=(u8)Copy_pu16PTR[Local_u16Iterator];
		Local_u8HighPart=(u8)(Copy_pu16PTR[Local_u16Iterator]>>8);

		HTFT_voidWriteData(Local_u8HighPart);
		HTFT_voidWriteData(Local_u8LowPart);
	}
}

void HTFT_voidReset()
{
    MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,PIN_High);
	MSTK_voidDelayus(100);
	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,PIN_Low);
	MSTK_voidDelayus(1);
	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,PIN_High);
	MSTK_voidDelayus(100);
	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,PIN_Low);
	MSTK_voidDelayus(100);
	MGPIO_voidSetPinValue(TFT_PORT,RST_PIN,PIN_High);
	MSTK_voidDelayms(120);
}

void HTFT_voidInit()
{
	MGPIO_voidSetMode(TFT_PORT,CONTROL_PIN,OUTPUT);
	MGPIO_voidSetOutputConfig(TFT_PORT,CONTROL_PIN,Push_Pull,Low_Speed);
	MGPIO_voidSetMode(TFT_PORT,RST_PIN,OUTPUT);
	MGPIO_voidSetOutputConfig(TFT_PORT,RST_PIN,Push_Pull,Low_Speed);

	HTFT_voidReset();
	HTFT_voidWriteCommand(SLEEP_OUT);
	MSTK_voidDelayms(10);
	HTFT_voidWriteCommand(COLOR_MODE);
	HTFT_voidWriteData(RGB565);
	HTFT_voidWriteCommand(DISPLAY_ON);

}

void HTFT_voidfillColor(u16 color)
{
    // Set column range (0 -> 127 for 128px width)
	HTFT_voidWriteCommand(0x2A);   // Column address set
	HTFT_voidWriteData(0x00);
    HTFT_voidWriteData(0);         // Start column
    HTFT_voidWriteData(0x00);
    HTFT_voidWriteData(127);       // End column

    // Set row range (0 -> 159 for 160px height)
    HTFT_voidWriteCommand(0x2B);   // Row address set
    HTFT_voidWriteData(0x00);
    HTFT_voidWriteData(0);         // Start row
    HTFT_voidWriteData(0x00);
    HTFT_voidWriteData(159);       // End row

    // Memory write
    HTFT_voidWriteCommand(0x2C);

    // Send pixel data
    for (u16 i = 0; i < 128 * 160; i++)
    {
        HTFT_voidWriteData(color >> 8);   // High byte
        HTFT_voidWriteData(color & 0xFF); // Low byte
    }
}


// ---------------- Set Window ----------------
static void HTFT_voidSetWindow(u16 x1, u16 y1, u16 x2, u16 y2)
{
    // X direction
    HTFT_voidWriteCommand(X_DIRECTION);
    HTFT_voidWriteData(x1 >> 8);
    HTFT_voidWriteData(x1 & 0xFF);
    HTFT_voidWriteData(x2 >> 8);
    HTFT_voidWriteData(x2 & 0xFF);

    // Y direction
    HTFT_voidWriteCommand(Y_DIRECTION);
    HTFT_voidWriteData(y1 >> 8);
    HTFT_voidWriteData(y1 & 0xFF);
    HTFT_voidWriteData(y2 >> 8);
    HTFT_voidWriteData(y2 & 0xFF);

    // Prepare to write
    HTFT_voidWriteCommand(SCREEN_WRITE);
}



// ---------------- Fill Rectangle ----------------

void HTFT_voidFillRect(u8 x1, u8 y1, u8 x2, u8 y2, u16 color)
{
    HTFT_voidWriteCommand(0x2A);
    HTFT_voidWriteData(0x00); HTFT_voidWriteData(x1);
    HTFT_voidWriteData(0x00); HTFT_voidWriteData(x2);

    HTFT_voidWriteCommand(0x2B);
    HTFT_voidWriteData(0x00); HTFT_voidWriteData(y1);
    HTFT_voidWriteData(0x00); HTFT_voidWriteData(y2);

    HTFT_voidWriteCommand(0x2C);

    for (u16 i = 0; i < (x2-x1+1)*(y2-y1+1); i++) {
        HTFT_voidWriteData(color >> 8);
        HTFT_voidWriteData(color & 0xFF);
    }
}

// --- 8x8 font (only 0-9, A-Z, = ) ---
static const u8 font8x8[][8] = {
		// '0'
		{0x3C,0x42,0x62,0x52,0x4A,0x46,0x42,0x3C},
		// '1'
		{0x10, 0x30, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x00},
		// Digit '2'
		{0x7C, 0x02, 0x02, 0x3C, 0x40, 0x40, 0x7E, 0x00},
		// Digit '3'
		{0x7C, 0x02, 0x02, 0x3C, 0x02, 0x02, 0x7C, 0x00},
		// Digit '4'
		{0x08, 0x18, 0x28, 0x48, 0x7E, 0x08, 0x08, 0x00},
		// Digit '5'
		{0x7E, 0x40, 0x40, 0x7C, 0x02, 0x02, 0x7C, 0x00},
		// Digit '6'
		{0x3C, 0x40, 0x40, 0x7C, 0x42, 0x42, 0x3C, 0x00},
		// Digit '7'
		{0x7E, 0x02, 0x04, 0x08, 0x10, 0x10, 0x10, 0x00},
		// Digit '8'
		{0x3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x3C, 0x00},
		// Digit '9'
		{0x3C, 0x42, 0x42, 0x3E, 0x02, 0x02, 0x3C, 0x00},
		// 'A'
		{0x3C,0x42,0x42,0x7E,0x42,0x42,0x42,0x00},
		// 'B'
		{0x7C,0x42,0x42,0x7C,0x42,0x42,0x7C,0x00},
		// 'C'
		{0x3C,0x42,0x40,0x40,0x40,0x42,0x3C,0x00},
		// 'D'
		{0x78,0x44,0x42,0x42,0x42,0x44,0x78,0x00},
		// 'E'
		{0x7E,0x40,0x40,0x7C,0x40,0x40,0x7E,0x00},
		// 'F'
		{0x7E,0x40,0x40,0x7C,0x40,0x40,0x40,0x00},
		// 'G'
		{0x3C,0x42,0x40,0x4E,0x42,0x42,0x3E,0x00},
		// 'H'
		{0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x00},
		// 'I'
		{0x3C,0x08,0x08,0x08,0x08,0x08,0x3C,0x00},
		// 'J'
		{0x1E,0x04,0x04,0x04,0x04,0x44,0x38,0x00},
		// 'K'
		{0x42,0x44,0x48,0x70,0x48,0x44,0x42,0x00},
		// 'L'
		{0x40,0x40,0x40,0x40,0x40,0x40,0x7E,0x00},
		// 'M'
		{0x81, 0xC3, 0xA5, 0x99, 0x81, 0x81, 0x81, 0x00},
		// 'N'
		{0x42,0x62,0x52,0x4A,0x46,0x42,0x42,0x00},
		// 'O'
		{0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00},
		// 'P'
		{0x7C,0x42,0x42,0x7C,0x40,0x40,0x40,0x00},
		// 'Q'
		{0x3C,0x42,0x42,0x42,0x4A,0x44,0x3A,0x00},
		// 'R'
		{0x7C,0x42,0x42,0x7C,0x48,0x44,0x42,0x00},
		// 'S'
		{0x3C,0x42,0x40,0x3C,0x02,0x42,0x3C,0x00},
		// 'T'
		{0x7F,0x08,0x08,0x08,0x08,0x08,0x08,0x00},
		// 'U'
		{0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00},
		// 'V'
		{0x42,0x42,0x42,0x42,0x24,0x24,0x18,0x00},
		// 'W'
		{0x81,0x81,0x81,0x99,0xA5,0xC3,0x81,0x00},
		// 'X'
		{0x42,0x24,0x18,0x18,0x18,0x24,0x42,0x00},
		// 'Y'
		{0x42,0x24,0x18,0x08,0x08,0x08,0x08,0x00},
		// 'Z'
		{0x7E,0x02,0x04,0x08,0x10,0x20,0x7E,0x00},
		// '='
		{0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x00},
};


void HTFT_voidPrintText8x8(char *str, u16 x, u16 y, u16 textColor, u16 bgColor)
{
    u8 highText = textColor >> 8;
    u8 lowText  = textColor & 0xFF;
    u8 highBg   = bgColor >> 8;
    u8 lowBg    = bgColor & 0xFF;

    // calculate string length
    int len = 0; char *p = str;
    while(*p++) len++;

    // each char is 9px wide (8 + 1 spacing)
    u16 totalWidth = len * 9;
    u16 startX = (128 - totalWidth) / 2;   // center horizontally

    // draw each character
    for(int idx=0; idx<len; idx++)
    {
        char c = str[idx];
        const u8 *bitmap = NULL;


        // Digits '0' - '9' are at indices 0-9
        if(c >= '0' && c <= '9') {
            bitmap = font8x8[c - '0'];
        }
        // Uppercase letters 'A' - 'Z' are at indices 10-35
        else if(c >= 'A' && c <= 'Z') {
            bitmap = font8x8[10 + (c - 'A')];
        }
        // '=' is at index 36
        else if(c == '=') {
            bitmap = font8x8[36];
        }
        // Unknown characters are skipped
        else continue;


        for(int row=0; row<8; row++)          // normal Y
        {
            for(int col=0; col<8; col++)      // X mirrored
            {
               u16 px = 127 - (startX + idx*9 + col);
               u16 py = 127 - (y + row);

                HTFT_voidWriteCommand(X_DIRECTION);
                HTFT_voidWriteData((px>>8)&0xFF);
                HTFT_voidWriteData(px&0xFF);
                HTFT_voidWriteData((px>>8)&0xFF);
                HTFT_voidWriteData(px&0xFF);

                HTFT_voidWriteCommand(Y_DIRECTION);
                HTFT_voidWriteData((py>>8)&0xFF);
                HTFT_voidWriteData(py&0xFF);
                HTFT_voidWriteData((py>>8)&0xFF);
                HTFT_voidWriteData(py&0xFF);

                HTFT_voidWriteCommand(SCREEN_WRITE);

                if(bitmap[row] & (1 << (7 - col)))   // flip bits so digits are not mirrored
                {
                    HTFT_voidWriteData(highText);
                    HTFT_voidWriteData(lowText);
                }
                else
                {
                    HTFT_voidWriteData(highBg);
                    HTFT_voidWriteData(lowBg);
                }
            }
        }
    }
}
