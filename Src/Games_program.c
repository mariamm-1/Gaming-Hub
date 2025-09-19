/*
 * Games_program.c
 *
 *  Created on: Sep 10, 2025
 *      Author: Nour
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#include "bit_math.h"
#include "start_image.h"

#include "MRCC_Interface.h"
#include "MSTK_interface.h"
#include "MGPIO_interface.h"
#include "MSPI_interface.h"
#include "MUART_interface.h"
#include "HLedMatrix_interface.h"
#include "HTFT_interface.h"
#include "Games_interface.h"
#include "Games_config.h"
#include "Games_private.h"


u8 jumping,jump_counter;
s16 obstacle_x;
volatile u8 dino_jumping = 0;
const int jump_strength = -14;
volatile int dino_y = GROUND_Y;
s16 dino_velocity = 0;
int ground_offset = 0;
s16 obstacle_speed = 6;
u16 color=0;
u16 jump_timer = 0;
u8 score=0;
u8 obstacle_scored=0;
u8 score_snake=0;
extern u8 Global_u8Button;
// -------- Board State --------
u8 board[3][3];   // 0=empty,1=X,2=O
u8 currentPlayer = 1;
u8 cursorIndex = 0;
u8 X_score = 0;
u8 O_score = 0;
u8 roundCount = 0;

//////////////////////////////
void GameOverScreen(int score);
void ShowFinalWinner(void);
void ShowRoundResult(u8 winner);
u8 isResetPressed(void);
void ResetHandler(void);


/************SNAKE GAME*************/
void playSnake(void)
{
	HTFT_voidInit();
    Pos snake[MAX_SNAKE_LEN];
    u8 snake_len = 3;
    u8 dir = 1; // 0=UP,1=RIGHT,2=DOWN,3=LEFT
    Pos food = {3, 3};

    // Init snake
    snake[0].x = 4; snake[0].y = 4;
    snake[1].x = 3; snake[1].y = 4;
    snake[2].x = 2; snake[2].y = 4;

    // Configure buttons
    MGPIO_voidSetMode(PORTC, PIN15, INPUT); //right
    MGPIO_voidSetInputConfig(PORTC, PIN15, PULLUP);

    MGPIO_voidSetMode(PORTC, PIN14, INPUT); //left
    MGPIO_voidSetInputConfig(PORTC, PIN14, PULLUP);

    // Button state tracking
    u8 left_was_pressed = 0;
    u8 right_was_pressed = 0;

    // Initial display of score

    while (1)
    {

        // === Move Snake (walls, no wrap) ===
        Pos newHead = snake[0];
        if (dir == 0) newHead.y--;      // UP
        else if (dir == 1) newHead.x++; // RIGHT
        else if (dir == 2) newHead.y++; // DOWN
        else newHead.x--;               // LEFT

        // === Wall collision ===
        if (newHead.x <= 0 || newHead.x >= 7 ||
            newHead.y <= 0 || newHead.y >= 7) {
        	HLEDMATRIX_voidBlinkMatrix(5,100);
        	GameOverScreen(score_snake);
            return;
        }


//Dies only if collides with itself
        // Check collision with body
        for (u8 i = 0; i < snake_len; i++) {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
            	HLEDMATRIX_voidBlinkMatrix(5,100);
            	GameOverScreen(score_snake);
                return; // Game over
            }
        }

        // === Shift body ===
               for (s8 i = snake_len; i > 0; i--)
            	   {
            	   snake[i] = snake[i-1];
            	   snake[0] = newHead;
            	   }


       // === Food check ===
               if (newHead.x == food.x && newHead.y == food.y) {
                   if (snake_len < MAX_SNAKE_LEN) snake_len++;
                   // place food only inside 1–6
                   food.x = 1 + (rand() % 6);
                   food.y = 1 + (rand() % 6);

                   score_snake++;

               }

       // === Draw frame ===
         u8 cols[8] = {0};

         // Draw walls ON
         for (u8 i = 0; i < 8; i++) {
             cols[0]  |= (1 << i);
             cols[7]  |= (1 << i);
             cols[i]  |= (1 << 0);
             cols[i]  |= (1 << 7);
         }

         // Draw snake
         for (u8 i = 0; i < snake_len; i++)
             cols[snake[i].x] |= (1 << snake[i].y);
         // Draw food
         cols[food.x] |= (1 << food.y);

         // === Build Frame ===

         // === Refresh Matrix for GAME_TICK_MS ===
         u32 elapsed = 0;
         while (elapsed < GAME_TICK_MS)
         {
             HLedMatrix_voidDisplay(cols);
             MSTK_voidDelayus(20);
             elapsed += 2;

             // Button check (edge detection)
             u8 left_now = (MGPIO_u8GetPinValue(PORTA, PIN6) == 0);
             u8 right_now = (MGPIO_u8GetPinValue(PORTC, PIN14) == 0);

             if (left_now && !left_was_pressed) {
                 dir = (dir + 3) & 3; // left turn
             }
             if (right_now && !right_was_pressed) {
                 dir = (dir + 1) & 3; // right turn
             }

             left_was_pressed = left_now;
             right_was_pressed = right_now;
         }
        }

    //akher snake
 }


/****************DINO GAME************************/
//======== Jump Button ISR ========
void JumpButtonPressed(void)
{
	if(MGPIO_u8GetPinValue(PORTC, PIN14)==0)
	{
		dino_jumping=1;
	}
}

void DINO_DOWN(u16 color)
{
	switch(color)
	{
	case (DINO_COLOR):
	HTFT_voidFillRect(DINO_X,  GROUND_Y, DINO_X +DINO_WIDTH, GROUND_Y+ DINO_HEIGHT,color);
	//Draw Eye
	HTFT_voidFillRect(DINO_X+2, GROUND_Y+DINO_HEIGHT-5, DINO_X +7, GROUND_Y+ DINO_HEIGHT-2,0x0000);
	//Draw teeth
	HTFT_voidFillRect(DINO_X, GROUND_Y+5, DINO_X +10,  GROUND_Y+ 8,0xFFFF);
	break;
	case(BG_COLOR):
	HTFT_voidFillRect(DINO_X,  GROUND_Y, DINO_X +DINO_WIDTH, GROUND_Y +DINO_HEIGHT,color);
	//Draw Eye
	HTFT_voidFillRect(DINO_X+2, GROUND_Y+DINO_HEIGHT-5, DINO_X +7, GROUND_Y+ DINO_HEIGHT-2,BG_COLOR);
	//Draw teeth
	HTFT_voidFillRect(DINO_X, GROUND_Y+5, DINO_X +10,  GROUND_Y+ 8,BG_COLOR);
	break;
	default:
		break;

	}
}

void DINO_UP(u16 color)
{
	switch(color)
	{
	case(DINO_COLOR):
	HTFT_voidFillRect(DINO_X,  JUMP_BUTTON, DINO_X +DINO_WIDTH,JUMP_TOP,color);
	//Draw Eye
	HTFT_voidFillRect(DINO_X+2, JUMP_TOP-5, DINO_X +7, JUMP_TOP-2,0x0000);
	//Draw teeth
	HTFT_voidFillRect(DINO_X, JUMP_BUTTON+5, DINO_X +10,  JUMP_BUTTON+ 8,0xFFFF);
	MSTK_voidDelayms(300);
	break;
	case (BG_COLOR):
	HTFT_voidFillRect(DINO_X,  JUMP_BUTTON, DINO_X +DINO_WIDTH,JUMP_TOP,color);
	//Draw Eye
	HTFT_voidFillRect(DINO_X+2, JUMP_TOP-5, DINO_X +7, JUMP_TOP-2,BG_COLOR);
	//Draw teeth
	HTFT_voidFillRect(DINO_X, JUMP_BUTTON+5, DINO_X +10,  JUMP_BUTTON+ 8,BG_COLOR);
	break;
	default:
		break;
	}
}
void Draw_OBS()

{
	//Draw obstacle
	HTFT_voidFillRect(obstacle_x, GROUND_Y, obstacle_x+OBS_WIDTH, GROUND_Y+OBS_HEIGHT, 0xF800);
	MSTK_voidDelayms(50);
	//Erase the old obstacle
	HTFT_voidFillRect(obstacle_x, GROUND_Y, obstacle_x+OBS_WIDTH, GROUND_Y+OBS_HEIGHT, BG_COLOR);
	//Update obstacle position
	obstacle_x += obstacle_speed;    // move right (or -= obstacle_speed to move left)
	if (obstacle_x >= TFT_WIDTH)
			{
			    obstacle_x = -OBS_WIDTH;
			    obstacle_scored = 0;   // reset flag for new obstacle
			}
	//Draw the obstacle at the new position
	HTFT_voidFillRect(obstacle_x, GROUND_Y , obstacle_x + OBS_WIDTH, GROUND_Y+OBS_HEIGHT, 0xF800);
	MSTK_voidDelayms(20);
}

void CLR_OBS()
{
	HTFT_voidFillRect(obstacle_x, GROUND_Y, obstacle_x+OBS_WIDTH, GROUND_Y+OBS_HEIGHT, BG_COLOR);
}
//////////
void GameOverScreen(int score)
{
    HTFT_voidfillColor(BG_COLOR);

    HTFT_voidPrintText8x8("GAME OVER", 0, 40, 0xF800, BG_COLOR);
    HTFT_voidPrintText8x8("SCORE=",   0, 60, DINO_COLOR, BG_COLOR);

    // convert score to string
    char buf[10]; int i=0;
    if(score==0) buf[i++]='0';
    else {
        char rev[10]; int r=0;
        while(score>0 && r<10){ rev[r++] = (score%10)+'0'; score/=10; }
        while(r>0) buf[i++]=rev[--r];
    }
    buf[i]=0;

    HTFT_voidPrintText8x8(buf, 0, 80, DINO_COLOR, BG_COLOR);
}

void playDino(void)
{
	//======== Intiallzation ========

	MGPIO_voidSetMode(PORTC, PIN14, INPUT);
	MGPIO_voidSetInputConfig(PORTC, PIN14, PULLUP);

	// Clear background
	HTFT_voidfillColor(BG_COLOR);

	while(1)
	{
		// Draw ground, dino, obstacle
		HTFT_voidFillRect(0, 0, TFT_WIDTH, GROUND_Y, GROUND_COLOR);

		if (dino_jumping == 1)
		{
			DINO_DOWN(BG_COLOR);
			DINO_UP(DINO_COLOR);

			if (jump_timer > 0)
			{
				jump_timer--;
			}
			else
			{
				// End jump
				DINO_UP(BG_COLOR);
				DINO_DOWN(DINO_COLOR);
				dino_jumping = 0;
			}
		}
		else
		{
			DINO_DOWN(DINO_COLOR);
			DINO_UP(BG_COLOR);
		}

		Draw_OBS();  // obstacle moves every loop

		JumpButtonPressed();

		// If jump button pressed and not already jumping, start jump
		if (dino_jumping == 0 && MGPIO_u8GetPinValue(PORTC, PIN14) == 0)
		{
			dino_jumping = 1;
			jump_timer = JUMP_DURATION;
		}

		//======== Collision Detection ========
		int dinoRight  = DINO_X ;
		int dinoLeft   =DINO_X+DINO_WIDTH;
		int obsLeft    = obstacle_x;
		int obsRight   = obstacle_x + OBS_WIDTH;

		int collide =  ((dino_jumping==0)&&(dinoRight<=obsLeft));

		if (collide)
		{
			GameOverScreen(score-1);
			while(1);
		}
		// If obstacle passed Dino and not yet scored → add score
		if (obsRight < dinoRight && obstacle_scored == 0) {
		    score++;
		    obstacle_scored = 1;   // mark as scored
		}
		// If obstacle has completely passed the Dino
		if ((obstacle_x + OBS_WIDTH) < DINO_X && obstacle_scored == 0)
		{
		    score++;
		    obstacle_scored = 1;  // mark this obstacle as already scored
		}


		else if ((dino_jumping==1)&&(dinoRight<=obsLeft)&&(dinoLeft>=obsRight))
		{
			CLR_OBS();
		}
	}


	MSTK_voidDelayms(30);
}

/*************************XO GAME******************************/

u8 CheckWin(u8 player)
{
    for(int i=0; i<3; i++)
    {
        if(board[i][0]==player && board[i][1]==player && board[i][2]==player) return 1; // صف
        if(board[0][i]==player && board[1][i]==player && board[2][i]==player) return 1; // عمود
    }
    if(board[0][0]==player && board[1][1]==player && board[2][2]==player) return 1; // قطر
    if(board[0][2]==player && board[1][1]==player && board[2][0]==player) return 1; // قطر تاني
    return 0;
}

static u8 BoardFull(void)
{
    for(int r=0; r<3; r++)
        for(int c=0; c<3; c++)
            if(board[r][c]==0) return 0;
    return 1;
}

// -------- Buttons --------
u8 ButtonPressed(u8 port, u8 pin)
{
    static u8 lastState[48] = {1}; // كل الـ pins assume HIGH بالبداية
    u8 idx = port*16 + pin;        // unique index لكل pin

    u8 current = MGPIO_u8GetPinValue(port, pin);

    u8 pressed = 0;
    if(lastState[idx] == 1 && current == 0) // transition: HIGH -> LOW
    {
        pressed = 1;  // ضغطة جديدة
    }

    lastState[idx] = current;
    return pressed;
}

void TicTacToe(void)
{

	MGPIO_voidSetMode(BTN_MOVE_PORT, BTN_MOVE_PIN, INPUT);
	MGPIO_voidSetInputConfig(BTN_MOVE_PORT, BTN_MOVE_PIN, PULLUP);

	MGPIO_voidSetMode(BTN_SELECT_PORT, BTN_SELECT_PIN, INPUT);
	MGPIO_voidSetInputConfig(BTN_SELECT_PORT, BTN_SELECT_PIN, PULLUP);



    while(roundCount < 3)
    {
        // reset board
        for(int r=0; r<3; r++)
            for(int c=0; c<3; c++)
                board[r][c] = 0;

        currentPlayer = 1;
        cursorIndex = 0;

        HTFT_voidDisplay(Image);
        MSTK_voidDelayms(3000);
        HTFT_DrawBoard();
        HTFT_HighlightCell(cursorIndex);

        u8 roundWinner = 0;


        while(1)
        {
            if(ButtonPressed(BTN_MOVE_PORT, BTN_MOVE_PIN))
            {
                cursorIndex = (cursorIndex + 1) % 9;
                HTFT_HighlightCell(cursorIndex);
            }

            if(ButtonPressed(BTN_SELECT_PORT, BTN_SELECT_PIN))
            {
                u8 row = cursorIndex / 3;
                u8 col = cursorIndex % 3;

                if(board[row][col] == 0)
                {
                    board[row][col] = currentPlayer;
                    HTFT_DrawSymbol(row, col, currentPlayer);

                    if(CheckWin(currentPlayer))
                    {
                        roundWinner = currentPlayer;
                        break;
                    }
                    else if(BoardFull())
                    {
                        roundWinner = 0; // draw
                        break;
                    }
                    else
                    {
                        currentPlayer = (currentPlayer==1) ? 2 : 1;
                    }
                }
            }
        }

        roundCount++;
        HTFT_voidfillColor(COLOR_BG); // fill with background color

        ShowRoundResult(roundWinner);

        if(roundCount == 3) {
        	HTFT_voidfillColor(COLOR_BG); // fill with background color

            ShowFinalWinner();
        }
    }
}


/////////////////////////////

// ---------------- Draw Line (simple, horizontal/vertical only) ----------------
void HTFT_voidDrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    if(y1 == y2) // horizontal
    {
        HTFT_voidFillRect(x1, y1, x2, y1, color);
    }
    else if(x1 == x2) // vertical
    {
        HTFT_voidFillRect(x1, y1, x1, y2, color);
    }

}

// ---------------- Draw Circle (Bresenham) ----------------

void HTFT_voidDrawCircle(u16 x0, u16 y0, u16 radius, u16 color)
{
    for(int y = -radius; y <= radius; y++)
    {
        for(int x = -radius; x <= radius; x++)
        {
            int dist2 = x*x + y*y;
            if(dist2 >= (radius-1)*(radius-1) && dist2 <= (radius+1)*(radius+1))
            {
                HTFT_voidFillRect(x0+x, y0+y, x0+x, y0+y, color);
            }
        }
    }
}


// ---------------- Draw 'X' Symbol ----------------
void HTFT_voidDrawX(u16 centerX, u16 centerY, u16 size, u16 color)
{
    for(s8 i=-size; i<=size; i++)
    {
        HTFT_voidFillRect(centerX+i, centerY+i, centerX+i, centerY+i, color);
        HTFT_voidFillRect(centerX+i, centerY-i, centerX+i, centerY-i, color);
    }
}


// ---------------- Draw 'O' Symbol ----------------
void HTFT_voidDrawO(u16 centerX, u16 centerY, u16 radius, u16 color)
{
    HTFT_voidDrawCircle(centerX, centerY, radius, color);
}

void HTFT_DrawBoard(void)
{
//	HTFT_voidDrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
    HTFT_voidfillColor(0xFFFF); // white background
    // Vertical dividers
    HTFT_voidFillRect(42, 0, 44, 159, 0x0000);
    HTFT_voidFillRect(84, 0, 86, 159, 0x0000);

    // Horizontal dividers
    HTFT_voidFillRect(0, 53, 127, 55, 0x0000);
    HTFT_voidFillRect(0, 106, 127, 108, 0x0000);
}

// -------- Draw Symbol in Cell --------
void HTFT_DrawSymbol(u8 row, u8 col, u8 player)
{
    u16 centerX = col*42 + 21;
    u16 centerY = row*53 + 26;

    if(player == 1)
        HTFT_voidDrawX(centerX, centerY, 12, COLOR_X);
    else if(player == 2)
        HTFT_voidDrawO(centerX, centerY, 12, COLOR_O);
}

// -------- Highlight Current Cell --------


void HTFT_HighlightCell(u8 index)
{
    static u8 lastCursorIndex = 255; // invalid at start

    if(lastCursorIndex == index) return;


    if(lastCursorIndex != 255)
    {
        u8 oldRow = lastCursorIndex / 3;
        u8 oldCol = lastCursorIndex % 3;

        u16 x1 = oldCol*42;
        u16 y1 = oldRow*53;
        u16 x2 = x1 + 42;
        u16 y2 = y1 + 53;


        HTFT_voidFillRect(x1, y1, x2, y1+2, COLOR_GRID); // top
        HTFT_voidFillRect(x1, y2-2, x2, y2, COLOR_GRID); // bottom
        HTFT_voidFillRect(x1, y1, x1+2, y2, COLOR_GRID); // left
        HTFT_voidFillRect(x2-2, y1, x2, y2, COLOR_GRID); // right
    }


    u8 row = index / 3;
    u8 col = index % 3;

    u16 x1 = col*42;
    u16 y1 = row*53;
    u16 x2 = x1 + 42;
    u16 y2 = y1 + 53;

    HTFT_voidFillRect(x1, y1, x2, y1+2, COLOR_CURSOR); // top
    HTFT_voidFillRect(x1, y2-2, x2, y2, COLOR_CURSOR); // bottom
    HTFT_voidFillRect(x1, y1, x1+2, y2, COLOR_CURSOR); // left
    HTFT_voidFillRect(x2-2, y1, x2, y2, COLOR_CURSOR); // right

    lastCursorIndex = index;
}

void ShowRoundResult(u8 winner)
{
    HTFT_voidfillColor(COLOR_BG); // clear screen

    if(winner == 1) {
        X_score++;
        HTFT_voidPrintText8x8("X WINS ", 10, 60, COLOR_X, COLOR_BG);
    }
    else if(winner == 2) {
        O_score++;
        HTFT_voidPrintText8x8("O WINS ", 10, 60, COLOR_O, COLOR_BG);
    }
    else {
        HTFT_voidPrintText8x8("ROUND DRAW", 30, 60, COLOR_GRID, COLOR_BG);
    }
//////////////
    // Clear score area
    HTFT_voidFillRect(0, 90, 127, 120, COLOR_BG);

    char scoreText[20];
    sprintf(scoreText, "X:%d   O:%d", X_score, O_score);
    HTFT_voidPrintText8x8(scoreText, 30, 100, COLOR_CURSOR, COLOR_BG);

    while(!ButtonPressed(BTN_SELECT_PORT, BTN_SELECT_PIN));
}

void ShowFinalWinner(void)
{
    HTFT_voidfillColor(COLOR_BG);

    if(X_score > O_score) {
        HTFT_voidPrintText8x8("X WON!", 20, 80, COLOR_X, COLOR_BG);
    }
    else if(O_score > X_score) {
        HTFT_voidPrintText8x8("O WON!", 20, 80, COLOR_O, COLOR_BG);
    }
    else {
        HTFT_voidPrintText8x8("MATCH DRAW!", 30, 80, COLOR_GRID, COLOR_BG);
    }
}

