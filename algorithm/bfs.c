#include <stdio.h>
#include "bfs.h"
#include "../data/data.h"

/* Directions: up, down, left, right */
int drow[4] = {-1, 1, 0, 0};
int dcol[4] = {0, 0, -1, 1};

void bfs(
    char grid[ROWS][COLS],
    int start_row,
    int start_col,
    int dist[ROWS][COLS],
    Cell parent[ROWS][COLS]
) {
    Cell queue[ROWS * COLS];
    int front = 0, rear = 0;

    /* Initialize distance and parent */
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            dist[i][j] = -1;            // -1 means unvisited
            parent[i][j].row = -1;
            parent[i][j].col = -1;
        }
    }

    /* Start BFS from entry point */
    queue[rear++] = (Cell){start_row, start_col};
    dist[start_row][start_col] = 0;

    while (front < rear) {
        Cell current = queue[front++];

        for (int k = 0; k < 4; k++) {
            int new_row = current.row + drow[k];
            int new_col = current.col + dcol[k];

            /* Check boundaries */
            if (new_row < 0 || new_row >= ROWS ||
                new_col < 0 || new_col >= COLS)
                continue;

            /* Skip blocked or occupied cells */
            if (grid[new_row][new_col] == 'X' ||
                grid[new_row][new_col] == 'O')
                continue;

            /* If not visited */
            if (dist[new_row][new_col] == -1) {
                dist[new_row][new_col] = dist[current.row][current.col] + 1;
                parent[new_row][new_col] = current;
                queue[rear++] = (Cell){new_row, new_col};
            }
        }
    }
}
