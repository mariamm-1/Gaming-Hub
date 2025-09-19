/*
 * HLedMatrix_program.c
 *
 *  Created on: Aug 31, 2025
 *      Author: Nour
 */

#include <stdlib.h>
#include "std_types.h"
#include "bit_math.h"

#include "MRCC_Interface.h"
#include "MGPIO_interface.h"
#include "MSTK_interface.h"
#include "HLedMatrix_interface.h"

static const u8 columnPins[8] = {0, 1, 2, 8, 9, 10, 12, 13}; // fixed: PB12 instead of PB11



void HLedMatrix_voidInit()
{
	//ROWS
	for(u8 pin=2; pin<=4; pin++)
	{
		MGPIO_voidSetMode(PORTA, pin, OUTPUT);
		MGPIO_voidSetOutputConfig(PORTA, pin, Push_Pull, Low_Speed);
	}

	for(u8 pin=8; pin<=12; pin++)
	{
		MGPIO_voidSetMode(PORTA, pin, OUTPUT);
		MGPIO_voidSetOutputConfig(PORTA, pin, Push_Pull, Low_Speed);
	}

	//COLUMNS
	for(u8 pin=0; pin<=2; pin++)
	{
		MGPIO_voidSetMode(PORTB, pin, OUTPUT);
		MGPIO_voidSetOutputConfig(PORTB, pin, Push_Pull, Low_Speed);
	}

	for(u8 pin=8; pin<=13; pin++)
	{
		MGPIO_voidSetMode(PORTB, pin, OUTPUT);
		MGPIO_voidSetOutputConfig(PORTB, pin, Push_Pull, Low_Speed);
	}
}


static void HLedMatrix_voidSetRowValue(u8 Copy_u8Row)
{
    // Rows PA2–PA4 (bits 0–2)
    for (u8 i = 0; i <= 2; i++) {
        u8 bit = GET_BIT(Copy_u8Row, i);
        MGPIO_voidSetPinValue(PORTA, (u8)(i + 2), bit);
    }

    // Rows PA8–PA12 (bits 3–7)
    for (u8 i = 0; i < 5; i++) {
        u8 bit = GET_BIT(Copy_u8Row, (u8)(i + 3));
        MGPIO_voidSetPinValue(PORTA, (u8)(i + 8), bit);
    }
}

/* Deactivate all columns (make them HIGH = OFF) */
static void HLedMatrix_voidDeactivateAllColumns(void)
{
    for (u8 i = 0; i < 8; i++) {
        MGPIO_voidSetPinValue(PORTB, columnPins[i], PIN_High);
    }
}



void HLedMatrix_voidDisplay(u8 *Copy_pu8Frame)
{
    for (u8 col = 0; col < 8; col++)
    {
        // 1) Ensure all columns are OFF before changing row outputs
        HLedMatrix_voidDeactivateAllColumns();

        // 2) Set row values for this column
        HLedMatrix_voidSetRowValue(Copy_pu8Frame[col]);

        // 3) Activate the current column only
        MGPIO_voidSetPinValue(PORTB, columnPins[col], PIN_Low);

        // 4) Short hold for persistence (tune this: 200..1500 us)
        MSTK_voidDelayus(600);

        // 5) Turn this column off before next iteration
        MGPIO_voidSetPinValue(PORTB, columnPins[col], PIN_High);
    }
}




void HLEDMATRIX_voidSlidingText(void)
{

	u8 Name[4][8] = {
				{0, 126, 4, 8, 16, 32, 126, 0},   // N
				{0, 126, 66, 66, 66, 66, 126, 0}, // O
				{0, 126, 64, 64, 64, 64, 126, 0}, // U
				{0, 126, 18, 18, 58, 110, 0, 0}   // R
		};
	// Build long message buffer (columns)
	u8 fullMessage[50] = {0}; // 4 letters * 8 + spacing
	u8 totalCols = 0;

	for(u8 letter=0; letter<4; letter++)
	{
		for(u8 col=0; col<8; col++)
		{
			fullMessage[totalCols++] = Name[letter][col];
		}
		fullMessage[totalCols++] = 0x00; // 1 column spacing
	}

	u8 frame[8]; // temporary 8x8 display window

	while(1)
	{
		// Slide window over fullMessage
		for(u8 shift=0; shift <= totalCols-8; shift++)
		{
			for(u8 refresh=0; refresh<10; refresh++) // persistence
			{
				for(u8 col=0; col<8; col++)
				{
					frame[col] = fullMessage[shift+col];
				}
				HLedMatrix_voidDisplay(frame);
			}
		}
	}
}

void HLEDMATRIX_voidBlinkMatrix(u8 times, u32 delayMs)
{
    // Frame for a completely lit-up matrix
    u8 allOnFrame[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    // Frame for a completely black matrix
    u8 allOffFrame[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    // Blink the matrix 'times' number of times
    for (u8 i = 0; i < times; i++) {
        // Turn all LEDs ON
        HLedMatrix_voidDisplay(allOnFrame);
        MSTK_voidDelayms(delayMs);

        // Turn all LEDs OFF
        HLedMatrix_voidDisplay(allOffFrame);
        MSTK_voidDelayms(delayMs);
    }
}
/*

void HLEDMATRIX_voidSlidingText(const u8* message, u8 messageCols)
{
	u8 frame[8]; // temporary 8x8 display window

    // The loop condition now depends on messageCols
	for(u8 shift = 0; shift <= messageCols - 8; shift++)
	{
		for(u8 refresh = 0; refresh < 10; refresh++) // persistence
		{
			for(u8 col = 0; col < 8; col++)
			{
				frame[col] = message[shift + col];
			}
			HLedMatrix_voidDisplay(frame);
		}
	}
}


*/
