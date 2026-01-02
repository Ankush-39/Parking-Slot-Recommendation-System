#include <stdio.h>
#include "display.h"

/* ANSI color codes (PowerShell & modern CMD supported) */
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define BLUE    "\033[1;34m"
#define WHITE   "\033[1;37m"

/* Print formatted message */
void print_message(const char *msg) {
    printf("\n========================================\n");
    printf("%s\n", msg);
    printf("========================================\n");
}

/* Print parking grid with legend, indices, and colors */
void print_grid(char grid[ROWS][COLS]) {

    printf("\nLegend:\n");
    printf(GREEN "E " RESET "- Entry   ");
    printf(CYAN "L " RESET "- Exit   ");
    printf(YELLOW "S " RESET "- Free Slot   ");
    printf(RED "O " RESET "- Occupied Slot\n");
    printf(BLUE "* " RESET "- Path   ");
    printf(WHITE "X " RESET "- Blocked\n\n");

    /* Column indices */
    printf("    ");
    for (int j = 0; j < COLS; j++)
        printf("%d ", j);
    printf("\n");

    printf("  ----------------\n");

    /* Grid with row indices */
    for (int i = 0; i < ROWS; i++) {
        printf("%d | ", i);
        for (int j = 0; j < COLS; j++) {

            char cell = grid[i][j];

            switch (cell) {
                case 'E': printf(GREEN "E " RESET); break;
                case 'L': printf(CYAN "L " RESET); break;
                case 'S': printf(YELLOW "S " RESET); break;
                case 'O': printf(RED "O " RESET); break;
                case '*': printf(BLUE "* " RESET); break;
                case 'X': printf(WHITE "X " RESET); break;
                default:  printf(". "); break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

/* Mark the BFS path */
void display_path(
    char grid[ROWS][COLS],
    Cell parent[ROWS][COLS],
    int start_row,
    int start_col,
    int end_row,
    int end_col
) {
    int r = end_row;
    int c = end_col;

    while (!(r == start_row && c == start_col)) {
        Cell p = parent[r][c];
        if (p.row == -1 && p.col == -1)
            break;

        if (grid[r][c] == '.')
            grid[r][c] = '*';

        r = p.row;
        c = p.col;
    }
}
