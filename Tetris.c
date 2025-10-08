#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define COLUMNS 12
#define ROWS 22

char Board[COLUMNS * ROWS];

// W = Border Wall
// E = Empty Cell
// A = Active Cell
// S = Settled Cell

void FillBoard() {
    for (int x = 0; x < COLUMNS; x++) {
        for (int y = 0; y < ROWS; y++) {
            if (x == 0 || y == 0 || y == ROWS - 1 || x == COLUMNS - 1) {
                Board[y*COLUMNS + x] = 'W';
            } else {
                Board[y*COLUMNS + x] = 'E';
            }
        }
    }
}

void DrawBoard() {
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        if (i % COLUMNS == 0) putchar('\n');
        if (Board[i] == 'A' || Board[i] == 'S') {
            putchar('%');
        }
        else if (Board[i] == 'W') {
            putchar('#');
        }
        else if (Board[i] == 'E') {
            putchar(' ');
        }
    }
}
int ny = 0;
int nx = 0;

void ApplyGravity() {
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        if (Board[i] == 'A') {
            ny = i / COLUMNS;
            nx = i % COLUMNS;
            ny += 1;
            Board[i] = 'E';
        }
    }
}

void MovePiece() {
    if (Board[ny*COLUMNS + nx] == 'E' ||  Board[ny*COLUMNS + nx] == 'A') {
        Board[ny*COLUMNS + nx] = 'A';
    } else {
        Board[(ny-1)*COLUMNS + (nx)] = 'A';
    }
}

void FillTestPiece() {
    Board[2*COLUMNS + 5] = 'A';
}

int main() {
    FillBoard();
    FillTestPiece();

    while (1) {
        ApplyGravity();
        MovePiece();
        
        DrawBoard();
        usleep(1000000);
    }
    
    return 0;
}