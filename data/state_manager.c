#include <stdio.h>
#include "state_manager.h"

/*
 Slot IDs:
 11 12 13 14 15
 21 22 23 24 25
 31 32 33 34 35
*/

/* Grid row positions for 15 slots */
int slot_rows[TOTAL_SLOTS] = {
    1, 1, 1, 1, 1,   // Slot row 1
    3, 3, 3, 3, 3,   // Slot row 2
    5, 5, 5, 5, 5    // Slot row 3
};

/* Grid column positions for 15 slots */
int slot_cols[TOTAL_SLOTS] = {
    0, 2, 4, 6, 8,   // Slot columns 1–5
    0, 2, 4, 6, 8,
    0, 2, 4, 6, 8
};

void load_parking_state(char grid[ROWS][COLS]) {

    FILE *fp = fopen("data/parking_state.txt", "r");

    /* Auto-create file if missing */
    if (fp == NULL) {
        fp = fopen("data/parking_state.txt", "w");
        for (int i = 0; i < TOTAL_SLOTS; i++) {
            fprintf(fp, "S ");
        }
        fclose(fp);
        fp = fopen("data/parking_state.txt", "r");
    }

    for (int i = 0; i < TOTAL_SLOTS; i++) {
        char state;
        fscanf(fp, " %c", &state);
        grid[slot_rows[i]][slot_cols[i]] = state;
    }

    fclose(fp);
}

void save_parking_state(char grid[ROWS][COLS]) {

    FILE *fp = fopen("data/parking_state.txt", "w");

    for (int i = 0; i < TOTAL_SLOTS; i++) {
        fprintf(fp, "%c ", grid[slot_rows[i]][slot_cols[i]]);
    }

    fclose(fp);
}
