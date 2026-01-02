# Parking Slot Recommendation System (C)

## Overview
This project is a console-based Parking Slot Recommendation System developed in C.  
It recommends the nearest available parking slot to a user based on the entry point using Breadth First Search (BFS).

The system models a realistic parking layout with roads and parking slots and maintains slot status across executions using file handling.

---

## Key Features
- Nearest parking slot recommendation
- User-controlled slot selection
- Realistic slot IDs (row–column based, e.g., 11, 23, 35)
- Clear separation of roads and parking slots
- Persistent parking state using file handling
- Modular and well-structured C code

---

## Data Structures & Algorithms
- 2D Arrays – parking layout
- Queue – BFS traversal
- Graph (implicit grid graph)
- File handling – slot persistence
- Algorithm used: Breadth First Search (BFS)

---

## Parking Model
- Grid size: 9 × 9
- Total slots: 15
- Entry point: top-left corner
- Exit point: bottom-right corner
- Slots placed beside driving lanes

---

## Project Structure


```text
Parking-Slot-Recommendation-System/
│
├── main.c                     # Main driver program
│
├── algorithm/
│   └── bfs.c                  # BFS pathfinding algorithm
│
├── data/
│   ├── data.h                 # Common definitions and constants
│   ├── state_manager.c        # Load/save parking slot state
│   ├── state_manager.h
│   └── parking_state.txt      # Persistent slot data
│
├── layout/
│   ├── parking_layout.c       # Parking grid layout & entry/exit
│   └── parking_layout.h
│
├── logic/
│   └── parking_manager.c      # Slot recommendation & management
│
├── utils/
│   └── display.c              # UI display functions
│
└── README.md



---

## Compile & Run
```bash
gcc main.c layout/parking_layout.c algorithm/bfs.c logic/parking_manager.c utils/display.c data/state_manager.c -o parking

run: .\parking
