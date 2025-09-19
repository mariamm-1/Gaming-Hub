/*
 * Games_private.h
 *
 *  Created on: Sep 10, 2025
 *      Author: Nour
 */

#ifndef GAMES_PRIVATE_H_
#define GAMES_PRIVATE_H_

// ---------- Types ----------
/****SNAKE GAME****/
typedef struct {
    u8 x;
    u8 y;
} Pos;

// ===== Ground =====
#define GROUND_Y       20   // ground line Y position

#define GROUND_COLOR   0x07E0 // green
#define BG_COLOR       0x5F9F // white background
#define DINO_COLOR     0x03E0

// ===== Dino =====
#define DINO_X       100
#define DINO_WIDTH   20
#define DINO_HEIGHT  20

// ===== Obstacle =====
#define OBS_WIDTH    10
#define OBS_HEIGHT   15

// ===== JUMP =====
#define JUMP_DURATION 3000  // number of loops jump lasts (e.g., 50 * 20ms = 1 second)


// Ground scrolling

#define GROUND_HEIGHT  20
#define GROUND_COLOR 0x07E0
#define BG_COLOR 0x5F9F

#define JUMP_TOP 62
#define JUMP_BUTTON 42

// Colors
#define COLOR_BG   0xFFFF  // White
#define COLOR_X    0xF800  // Red
#define COLOR_O    0x001F  // Blue
#define COLOR_GRID 0x0000
#define COLOR_CURSOR 0x07E0



#endif /* GAMES_PRIVATE_H_ */
