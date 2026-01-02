#ifndef PARKING_MANAGER_H
#define PARKING_MANAGER_H

#include "../data/data.h"
#include "../algorithm/bfs.h"

/* Structure to store slot information */
typedef struct {
    int row;
    int col;
    int distance;
} SlotInfo;

/* Find all free slots */
int get_free_slots(
    char grid[ROWS][COLS],
    SlotInfo slots[]
);

/* Recommend nearest slot */
int recommend_nearest_slot(
    SlotInfo slots[],
    int slot_count
);

/* Park vehicle at selected slot (AUTO) */
void occupy_slot(
    char grid[ROWS][COLS],
    int row,
    int col
);

/* Free a slot when vehicle exits */
void free_slot(
    char grid[ROWS][COLS],
    int row,
    int col
);

#endif
