#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "data.h"

/* Total number of parking slots */
#define TOTAL_SLOTS 15

/* Slot grid mappings */
extern int slot_rows[TOTAL_SLOTS];
extern int slot_cols[TOTAL_SLOTS];

/* Load slot states from file */
void load_parking_state(char grid[ROWS][COLS]);

/* Save slot states to file */
void save_parking_state(char grid[ROWS][COLS]);

#endif
