#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define COLUMNS 12
#define ROWS 22

char Board[COLUMNS * ROWS];

void FillBoard() {
    for (int x = 0; x < COLUMNS; x++) {
        for (int y = 0; y < ROWS; y++) {
            if (x == 0 || y == 0 || y == ROWS - 1 || x == COLUMNS - 1) {
                Board[y*COLUMNS + x] = '#';
            } else {
                Board[y*COLUMNS + x] = ' ';
            }
        }
    }
}

void DrawBoard() {
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        if (i % COLUMNS == 0) putchar('\n');
        putchar(Board[i]);
    }
}

int main() {
    FillBoard();
    DrawBoard();
    return 0;
}