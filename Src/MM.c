/*
 * mm.c  (Memory Match Game with buttons)
 *
 * Simple 4x4 memory match game for TFT using HTFT driver and 3 push buttons.
 *
 * Controls:
 *   PC13 -> LEFT
 *   PC14 -> RIGHT
 *   PC15 -> SELECT
 *
 * Author: Mm
 */

#include "std_types.h"
#include "bit_math.h"
#include "mmss.h"
#include "mmgo.h"
#include "mmws.h"

#include "MM.h"
#include "HTFT_interface.h"   // TFT drawing functions
#include "MSTK_interface.h"   // Delay and SysTick
#include "MGPIO_interface.h"  // GPIO for buttons


static const u16 pair_colors[NUM_PAIRS] = {
    COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW,
    COLOR_CYAN, COLOR_MAGENTA, COLOR_WHITE, COLOR_BLACK
};

static u16 card_colors[NUM_CARDS];



static u16 memory_play_count = 0;
/* Card states */
typedef enum {
    CARD_FACE_DOWN = 0,
    CARD_REVEALED,
    CARD_MATCHED
} card_state_t;

/* Game data */
static u8 cards[NUM_CARDS];
static card_state_t state[NUM_CARDS];
static u8 cursor_col=0, cursor_row=0;

/* --- Random generator --- */
static u16 lfsr = 0xACE1;

static u16 lfsr_next(void) {
    u16 bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
    lfsr = (lfsr >> 1) | (bit << 15);
    return lfsr;
}


/* Utility: index from row/col */
static inline u8 idx(u8 r, u8 c) { return r*GRID_COLS + c; }

/* --- Button Input ---
 * PC13 = LEFT
 * PC14 = RIGHT
 * PC15 = SELECT
 */
static u8 handle_input_once(void)
{
	// UP (C13)
	    if(MGPIO_u8GetPinValue(PORTC, PIN13) == 0) {  // active low
	        if(cursor_row <GRID_ROWS-1) {cursor_row++;
	        MSTK_voidDelayms(200);}
	        else if (cursor_row >=GRID_ROWS-1) {cursor_row=0;
	        MSTK_voidDelayms(200);}
	        return 0;
	    }

	// LEFT(C15)
	if(MGPIO_u8GetPinValue(PORTC, PIN15) == 0) {

	     if(cursor_col < GRID_COLS-1) {cursor_col++;
	     MSTK_voidDelayms(200);}
	     else if(cursor_col >= GRID_COLS-1){cursor_col=0;
	     MSTK_voidDelayms(200);}
	    return 0;
	}
	if(MGPIO_u8GetPinValue(PORTC, PIN14) == 0) { // SELECT
	    MSTK_voidDelayms(200);
	    return 1;
	}
    return 0;
}

/* Draw a single card */
static void draw_card(u8 r, u8 c)
{
    u8 i = idx(r,c);
    u16 x = GRID_START_X + c * (CARD_W + CARD_SPACING_X);
    u16 y = GRID_START_Y + r * (CARD_H + CARD_SPACING_Y);

    if(state[i] == CARD_FACE_DOWN) {
        // Back side
        HTFT_voidFillRect(x, y, x + CARD_W - 1, y + CARD_H - 1, COLOR_CARD_BG);
        HTFT_voidFillRect(x+3, y+3, x+CARD_W-4, y+CARD_H-4, COLOR_BLUE);
    } else {
        // Face-up: show color
        HTFT_voidFillRect(x, y, x + CARD_W - 1, y + CARD_H - 1, card_colors[i]);
    }

    // Cursor highlight
    if(cursor_row == r && cursor_col == c) {
        HTFT_voidFillRect(x, y, x + CARD_W - 1, y + 2, COLOR_YELLOW);
        HTFT_voidFillRect(x, y + CARD_H - 3, x + CARD_W - 1, y + CARD_H - 1, COLOR_YELLOW);
        HTFT_voidFillRect(x, y, x + 2, y + CARD_H - 1, COLOR_YELLOW);
        HTFT_voidFillRect(x + CARD_W - 3, y, x + CARD_W - 1, y + CARD_H - 1, COLOR_YELLOW);
    }
}


/* Draw grid */
static void draw_grid(void)
{
    HTFT_voidFillRect(0, 0, TFT_WIDTH-1, TFT_HEIGHT-1, COLOR_GRAY);

    for(u8 r=0; r<GRID_ROWS; r++) {
        for(u8 c=0; c<GRID_COLS; c++) {
            draw_card(r,c);
        }
    }
}

/* Shuffle cards */
static void shuffle_cards(void)
{
    // Fill pairs with colors
    for(u8 i=0; i<NUM_PAIRS; i++) {
        cards[2*i]   = i;
        cards[2*i+1] = i;
    }

    // Shuffle
    u32 seed = MSTK_u32GetRemainingTickSingleShot();
    if(seed == 0) seed = 0xACE1;
    lfsr = (u16)(seed & 0xFFFF);

    for(int i = NUM_CARDS - 1; i > 0; --i) {
        u16 r = lfsr_next();
        int j = r % (i + 1);
        u8 t = cards[i];
        cards[i] = cards[j];
        cards[j] = t;
    }

    // Assign colors based on card index
    for(u8 i=0; i<NUM_CARDS; i++) {
        card_colors[i] = pair_colors[cards[i]];
    }
}
void MemoryGame_Run(void)
{
    // PC13, PC14, PC15 as input pull-up
    MGPIO_voidSetMode(PORTC, PIN13, INPUT);
    MGPIO_voidSetInputConfig(PORTC, PIN13, PULLUP);

    MGPIO_voidSetMode(PORTC, PIN14, INPUT);
    MGPIO_voidSetInputConfig(PORTC, PIN14, PULLUP);

    MGPIO_voidSetMode(PORTC, PIN15, INPUT);
    MGPIO_voidSetInputConfig(PORTC, PIN15, PULLUP);

    HTFT_voidDisplay(mmss_ARR);
    MSTK_voidDelayms(1000);

    shuffle_cards();

    for(u8 i=0; i<NUM_CARDS; i++) state[i] = CARD_FACE_DOWN;
    draw_grid();

    u8 first_idx = 0xFF;
    u8 matches = 0;

    // Software timer counter in milliseconds
    u32 timer_counter = 0;
    const u32 TIMER_MAX = 60000; // 60 seconds

    while(1) {
        draw_grid();

        u8 selected = 0;
        while(!selected) {
            // Increment software timer
            MSTK_voidDelayms(50);  // base loop delay
            timer_counter += 50;

            // Check timer
            if(timer_counter >= TIMER_MAX) {
                // TIME UP
               HTFT_voidDisplay(mmgo_ARR);
                // Wait for SELECT to restart
                while(handle_input_once() != 1) {
                    MSTK_voidDelayms(50);
                }

                // Restart game
                shuffle_cards();
                for(u8 i=0; i<NUM_CARDS; i++) state[i] = CARD_FACE_DOWN;
                matches = 0;
                first_idx = 0xFF;
                cursor_col = 0;
                cursor_row = 0;
                draw_grid();

                // Reset timer
                timer_counter = 0;
            }

            // Handle input
            if(handle_input_once()) {
                selected = 1;
                break;
            }
        }

        // Process selected card
        u8 sidx = idx(cursor_row, cursor_col);

        if(state[sidx] != CARD_FACE_DOWN) continue;

        state[sidx] = CARD_REVEALED;
        draw_grid();

        if(first_idx == 0xFF) {
            first_idx = sidx;
        } else {
            if(cards[first_idx] == cards[sidx]) {
                state[first_idx] = CARD_MATCHED;
                state[sidx] = CARD_MATCHED;
                matches++;
            } else {
                MSTK_voidDelayms(800);
                state[first_idx] = CARD_FACE_DOWN;
                state[sidx] = CARD_FACE_DOWN;
            }
            first_idx = 0xFF;
        }

        // Check win condition
        if(matches == NUM_PAIRS) {
            HTFT_voidDisplay(mmws_ARR);

            while(handle_input_once() != 1) {
                MSTK_voidDelayms(50);
            }

            shuffle_cards();
            for(u8 i=0; i<NUM_CARDS; i++) state[i] = CARD_FACE_DOWN;
            matches = 0;
            first_idx = 0xFF;
            cursor_col = 0;
            cursor_row = 0;
            draw_grid();

            // Reset timer after win
            timer_counter = 0;
        }
    }
    //akher memory
    memory_play_count++;
    SendGameReport("MEMORY", matches, memory_play_count);
}

