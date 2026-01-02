#ifndef BFS_H
#define BFS_H

#include "../data/data.h"

/* Structure to store a cell position */
typedef struct {
    int row;
    int col;
} Cell;

/* BFS function:
   - Computes distance from entry to all reachable cells
   - Stores parent for path reconstruction
*/
void bfs(
    char grid[ROWS][COLS],
    int start_row,
    int start_col,
    int dist[ROWS][COLS],
    Cell parent[ROWS][COLS]
);

#endif
