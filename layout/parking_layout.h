#ifndef PARKING_LAYOUT_H
#define PARKING_LAYOUT_H

#include "../data/data.h"

extern char parking_grid[ROWS][COLS];

extern int entry_row, entry_col;
extern int exit_row, exit_col;

void initialize_parking_layout();

#endif
