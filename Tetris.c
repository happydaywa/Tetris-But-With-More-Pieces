#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COLUMNS 12
#define ROWS 22

char Board[COLUMNS * ROWS];

void FillBoard() {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            if (x == 0 || y == 0 || y == ROWS - 1 || x == COLUMNS - 1)
                Board[y*COLUMNS + x] = 'W';
            else
                Board[y*COLUMNS + x] = 'E';
        }
    }
}

void DrawBoard() {
    printf("\033[H\033[J"); // clear terminal
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        if (i % COLUMNS == 0) putchar('\n');
        char c = Board[i];
        switch (c) {
            case 'A': putchar('%'); break;
            case 'S': putchar('%'); break;
            case 'W': putchar('#'); break;
            default:  putchar(' '); break;
        }
    }
    fflush(stdout);
}

void FillTestPiece() {
    Board[2*COLUMNS + 6] = 'A';
    Board[3*COLUMNS + 5] = 'A';
    Board[3*COLUMNS + 6] = 'A';
    Board[1*COLUMNS + 6] = 'A';
    Board[1*COLUMNS + 1] = 'A';
}

int MoveDown() {
    int canMove = 1;

    for (int y = ROWS - 2; y >= 1; y--) {
        for (int x = 1; x < COLUMNS - 1; x++) {
            if (Board[y*COLUMNS + x] == 'A') {
                char below = Board[(y+1)*COLUMNS + x];
                if (below == 'W' || below == 'S')
                    canMove = 0;
            }
        }
    }

    if (!canMove) {
        for (int i = 0; i < ROWS * COLUMNS; i++)
            if (Board[i] == 'A')
                Board[i] = 'S';
        return 0;
    }

    for (int y = ROWS - 2; y >= 1; y--) {
        for (int x = 1; x < COLUMNS - 1; x++) {
            if (Board[y*COLUMNS + x] == 'A') {
                Board[(y+1)*COLUMNS + x] = 'A';
                Board[y*COLUMNS + x] = 'E';
            }
        }
    }
    return 1;
}

int main() {
    FillBoard();
    FillTestPiece();

    while (1) {
        DrawBoard();
        MoveDown();
        usleep(300000);
    }

    return 0;
}
