/*
 * Games_config.h
 *
 *  Created on: Sep 10, 2025
 *      Author: Nour
 */

#ifndef GAMES_CONFIG_H_
#define GAMES_CONFIG_H_

// Buttons (active low)
#define BTN_LEFT_PORT   PORTC
#define BTN_LEFT_PIN    PIN14

#define BTN_RIGHT_PORT  PORTC
#define BTN_RIGHT_PIN   PIN13

//configurable constants
#define GAME_TICK_MS   300    // snake update rate (ms)
#define MAX_SNAKE_LEN  32

// ===== TFT Dimensions =====
#define TFT_WIDTH    128
#define TFT_HEIGHT   160
// -------- Buttons --------
#define BTN_MOVE_PORT   PORTC
#define BTN_MOVE_PIN    PIN13

#define BTN_SELECT_PORT PORTC
#define BTN_SELECT_PIN  PIN14


#endif /* GAMES_CONFIG_H_ */
