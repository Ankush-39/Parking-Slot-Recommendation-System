#include <stdio.h>

#include "data/data.h"
#include "data/state_manager.h"
#include "layout/parking_layout.h"
#include "algorithm/bfs.h"
#include "logic/parking_manager.h"
#include "utils/display.h"

/*
 Slot ID format:
   Slot ID = (slotRow)(slotCol)
   Examples: 11, 16, 23, 36

 Mapping rules:
   Grid slot rows: 1 -> slotRow 1
                   3 -> slotRow 2
                   5 -> slotRow 3

   Grid slot cols: 0 -> slotCol 1
                   2 -> slotCol 2
                   4 -> slotCol 3
                   6 -> slotCol 4
                   8 -> slotCol 5
                   (6 slots per row total)
*/

/* Convert grid row to logical slot row (1,2,3) */
int gridRowToSlotRow(int r)
{
    if (r == 1)
        return 1;
    if (r == 3)
        return 2;
    if (r == 5)
        return 3;
    return -1;
}

/* Convert grid col to logical slot column (1..6) */
int gridColToSlotCol(int c)
{
    if (c == 0)
        return 1;
    if (c == 2)
        return 2;
    if (c == 4)
        return 3;
    if (c == 6)
        return 4;
    if (c == 8)
        return 5;
    return -1;
}

/* Convert slot ID to index in state_manager arrays */
int slotIdToIndex(int slotId)
{
    int slotRow = slotId / 10;
    int slotCol = slotId % 10;

    for (int i = 0; i < TOTAL_SLOTS; i++)
    {

        int r = slot_rows[i];
        int c = slot_cols[i];

        int logicalRow = (r == 1) ? 1 : (r == 3) ? 2
                                    : (r == 5)   ? 3
                                                 : -1;
        int logicalCol =
            (c == 0) ? 1 : (c == 2) ? 2
                       : (c == 4)   ? 3
                       : (c == 6)   ? 4
                       : (c == 8)   ? 5
                                    : -1;

        int currentSlotId = logicalRow * 10 + logicalCol;

        if (currentSlotId == slotId)
            return i;
    }

    return -1; // slot not found
}

int min_distance_to_slot(int slot_r, int slot_c, int dist[ROWS][COLS])
{

    int min = 99999;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++)
    {
        int nr = slot_r + dr[i];
        int nc = slot_c + dc[i];

        if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS)
        {
            if (parking_grid[nr][nc] == '.' && dist[nr][nc] != -1)
            {
                if (dist[nr][nc] < min)
                    min = dist[nr][nc];
            }
        }
    }

    return (min == 99999) ? -1 : min;
}

int main()
{

    int choice;

    while (1)
    {

        /* Initialize layout and load saved state */
        initialize_parking_layout();
        load_parking_state(parking_grid);

        print_message("SMART PARKING SLOT RECOMMENDATION SYSTEM");
        print_grid(parking_grid);

        printf("Menu:\n");
        printf("1. Park Vehicle\n");
        printf("2. Free a Slot\n");
        printf("3. Exit System\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        /* ================= PARK VEHICLE ================= */
        if (choice == 1)
        {

            /* Run BFS once from entry road */
            int dist[ROWS][COLS];
            Cell parent[ROWS][COLS];
            bfs(parking_grid, entry_row, entry_col, dist, parent);

            /* List all slots with status */
            printf("\nAvailable Slots:\n");
            for (int i = 0; i < TOTAL_SLOTS; i++)
            {

                int r = slot_rows[i];
                int c = slot_cols[i];

                int slotRow = gridRowToSlotRow(r);
                int slotCol = gridColToSlotCol(c);

                int slotId = slotRow * 10 + slotCol;

                printf("Slot %d : %s\n",
                       slotId,
                       (parking_grid[r][c] == 'S') ? "FREE" : "OCCUPIED");
            }

            /* Recommend nearest free slot */
            int bestIndex = -1;
            int bestDist = 99999;

            for (int i = 0; i < TOTAL_SLOTS; i++)
            {
                int r = slot_rows[i];
                int c = slot_cols[i];

                int d = min_distance_to_slot(r, c, dist);

                if (parking_grid[r][c] == 'S' && d != -1)
                {
                    if (d < bestDist)
                    {
                        bestDist = d;
                        bestIndex = i;
                    }
                }
            }

            if (bestIndex == -1)
            {
                print_message("PARKING FULL OR NO REACHABLE SLOT!");
                continue;
            }

            int recRow = gridRowToSlotRow(slot_rows[bestIndex]);
            int recCol = gridColToSlotCol(slot_cols[bestIndex]);
            int recSlotId = recRow * 10 + recCol;

            printf("\nRecommended Slot ID: %d\n", recSlotId);

            int chosenId;
            printf("Enter Slot ID to park: ");
            scanf("%d", &chosenId);

            int index = slotIdToIndex(chosenId);
            if (index == -1)
            {
                print_message("INVALID SLOT ID!");
                continue;
            }

            if (parking_grid[slot_rows[index]][slot_cols[index]] == 'O')
            {
                print_message("SLOT ALREADY OCCUPIED!");
                continue;
            }

            /* Show path ONLY after user selection */
            display_path(
                parking_grid,
                parent,
                entry_row,
                entry_col,
                slot_rows[index],
                slot_cols[index]);

            print_message("PATH TO SELECTED SLOT");
            print_grid(parking_grid);

            /* Park vehicle */
            occupy_slot(
                parking_grid,
                slot_rows[index],
                slot_cols[index]);

            save_parking_state(parking_grid);

            print_message("VEHICLE PARKED SUCCESSFULLY");
            print_grid(parking_grid);
        }

        /* ================= FREE SLOT ================= */
        else if (choice == 2)
        {

            int freeId;
            printf("Enter Slot ID to free (e.g., 23): ");
            scanf("%d", &freeId);

            int index = slotIdToIndex(freeId);
            if (index == -1 ||
                parking_grid[slot_rows[index]][slot_cols[index]] == 'S')
            {
                print_message("INVALID SLOT OR SLOT ALREADY FREE!");
                continue;
            }

            free_slot(
                parking_grid,
                slot_rows[index],
                slot_cols[index]);

            save_parking_state(parking_grid);

            print_message("SLOT FREED SUCCESSFULLY");
            print_grid(parking_grid);
        }

        /* ================= EXIT ================= */
        else if (choice == 3)
        {
            print_message("EXITING SYSTEM. THANK YOU!");
            break;
        }

        else
        {
            print_message("INVALID MENU OPTION!");
        }
    }

    return 0;
}
