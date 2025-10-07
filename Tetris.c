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
int ny = 0;
int nx = 0;

void ApplyGravity() {
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        if (Board[i] == '%') {
            ny = i / COLUMNS;
            nx = i % COLUMNS;
            ny += 1;
            Board[i] = ' ';
        }
    }
}

void MovePiece() {
    Board[ny*COLUMNS + nx] = '%';
}

void FillTestPiece() {
    Board[2*COLUMNS + 5] = '%';
}

int main() {
    FillBoard();
    FillTestPiece();

    while (1) {
        ApplyGravity();
        printf("Before movepiece called: %d, %d", nx, ny);
        MovePiece();
        
        DrawBoard();
        usleep(1000000);
    }
    
    return 0;
}