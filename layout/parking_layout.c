#include "parking_layout.h"

/*
 Symbols:
 . -> Road / Lane
 S -> Free parking slot
 O -> Occupied parking slot
*/

char parking_grid[ROWS][COLS];

/* Logical entry & exit points (outside grid) */
int entry_row = 0, entry_col = 0;   // top road
int exit_row  = 8, exit_col  = 8;   // bottom road

void initialize_parking_layout() {

    char temp[ROWS][COLS] = {
        /* 0 */ {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
        /* 1 */ {'S', '.', 'S', '.', 'S', '.', 'S', '.', 'S'},
        /* 2 */ {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
        /* 3 */ {'S', '.', 'S', '.', 'S', '.', 'S', '.', 'S'},
        /* 4 */ {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
        /* 5 */ {'S', '.', 'S', '.', 'S', '.', 'S', '.', 'S'},
        /* 6 */ {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
        /* 7 */ {'.', '.', '.', '.', '.', '.', '.', '.', '.'},
        /* 8 */ {'.', '.', '.', '.', '.', '.', '.', '.', '.'}
    };

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            parking_grid[i][j] = temp[i][j];
        }
    }
}
