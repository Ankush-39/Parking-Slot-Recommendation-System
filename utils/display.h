#ifndef DISPLAY_H
#define DISPLAY_H

#include "../data/data.h"
#include "../algorithm/bfs.h"

/* Print the parking grid with UI and colors */
void print_grid(char grid[ROWS][COLS]);

/* Display path from entry to selected slot */
void display_path(
    char grid[ROWS][COLS],
    Cell parent[ROWS][COLS],
    int start_row,
    int start_col,
    int end_row,
    int end_col
);

/* Print a formatted message */
void print_message(const char *msg);

#endif
