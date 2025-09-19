/*
 * Games_interface.h
 *
 *  Created on: Sep 10, 2025
 *      Author: Nour
 */

#ifndef GAMES_INTERFACE_H_
#define GAMES_INTERFACE_H_


// === Games prototypes ===
//Snake game
void playSnake(void);

//DINO game
void playDino(void);

void playReactionGame(void);
u8 CheckWin(u8 player);
void TicTacToe(void);
void JumpButtonPressed(void);

void Draw_OBS();


////HTFT HELPERS
void HTFT_voidDrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void HTFT_voidDrawCircle(u16 x0, u16 y0, u16 radius, u16 color);
void HTFT_voidDrawX(u16 centerX, u16 centerY, u16 size, u16 color);
void HTFT_voidDrawO(u16 centerX, u16 centerY, u16 radius, u16 color);
void HTFT_DrawBoard(void);
void HTFT_DrawSymbol(u8 row, u8 col, u8 player);
void HTFT_HighlightCell(u8 index);


#endif /* GAMES_INTERFACE_H_ */
