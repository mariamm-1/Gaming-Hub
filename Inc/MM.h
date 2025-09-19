/*
 * MM.h
 *
 *  Created on: Sep 14, 2025
 *      Author: Nour
 */

#ifndef MM_H_
#define MM_H_

/* --- Display/grid geometry --- */
#define TFT_WIDTH   128
#define TFT_HEIGHT  160

#define GRID_COLS 4
#define GRID_ROWS 4
#define CARD_W  28
#define CARD_H  34
#define CARD_SPACING_X 4
#define CARD_SPACING_Y 4

#define GRID_TOTAL_W (GRID_COLS*CARD_W + (GRID_COLS-1)*CARD_SPACING_X)
#define GRID_TOTAL_H (GRID_ROWS*CARD_H + (GRID_ROWS-1)*CARD_SPACING_Y)
#define GRID_START_X ((TFT_WIDTH - GRID_TOTAL_W)/2)
#define GRID_START_Y ((TFT_HEIGHT - GRID_TOTAL_H)/2)

/* Colors (RGB565) */
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_GRAY    0x8410
#define COLOR_CARD_BG 0x3996

/* Game constants */
#define NUM_PAIRS ((GRID_COLS*GRID_ROWS)/2)
#define NUM_CARDS (GRID_COLS*GRID_ROWS)



#endif /* MM_H_ */
