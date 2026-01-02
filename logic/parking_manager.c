#include <stdio.h>
#include "parking_manager.h"

/* Get all free parking slots */
int get_free_slots(
    char grid[ROWS][COLS],
    SlotInfo slots[]
) {
    int count = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == 'S') {
                slots[count].row = i;
                slots[count].col = j;
                slots[count].distance = -1; // to be filled later
                count++;
            }
        }
    }
    return count;
}

/* Recommend nearest slot based on distance */
int recommend_nearest_slot(
    SlotInfo slots[],
    int slot_count
) {
    if (slot_count == 0)
        return -1;

    int best_index = 0;

    for (int i = 1; i < slot_count; i++) {
        if (slots[i].distance < slots[best_index].distance) {
            best_index = i;
        }
    }
    return best_index;
}

/* Mark slot as occupied */
void occupy_slot(
    char grid[ROWS][COLS],
    int row,
    int col
) {
    grid[row][col] = 'O';
}

/* Free slot when vehicle exits */
void free_slot(
    char grid[ROWS][COLS],
    int row,
    int col
) {
    grid[row][col] = 'S';
}
