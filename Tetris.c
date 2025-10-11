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
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        if (i % COLUMNS == 0) putchar('\n');
        char c = Board[i];
        switch (c) {
            case 'A': putchar('A'); break;
            case 'S': putchar('S'); break;
            case 'W': putchar('#'); break;
            default:  putchar(' '); break;
        }
    }
    fflush(stdout);
}


int MoveDown() {
    int CanMove = 1;

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            if (Board[y*COLUMNS+x] == 'A') {
                char Below = Board[(y+1)*COLUMNS+x];
                printf("%c", Below);
                if (Below == 'W' || Below == 'S') {
                    CanMove = 0;
                }
            }
        }
    }   

    if (!CanMove) {
        for (int i = 0; i < ROWS*COLUMNS; i++) {
            if (Board[i] == 'A') {
                Board[i] = 'S';
            } 
        }
        return 0;
    }

    for (int y = ROWS; y > 0; y--) {
        for (int x = COLUMNS; x > 0; x--) {
            if (Board[y*COLUMNS+x] == 'A') {
                Board[(y+1)*COLUMNS+x] = 'A';
                Board[y*COLUMNS+x] = 'E';
            }
        }
    }
    return 1;
}

void BuildPiece() {
    Board[2*COLUMNS + 6] = 'A';
    Board[3*COLUMNS + 5] = 'A';
    Board[3*COLUMNS + 6] = 'A';
    Board[1*COLUMNS + 6] = 'A';
}

int main() {
    FillBoard();

    while (1) {
        DrawBoard();
        if (!MoveDown()) {
            BuildPiece();
        }
        
        usleep(300000);
    }

    return 0;
}