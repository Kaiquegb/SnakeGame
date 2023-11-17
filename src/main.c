#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// struct para representar a cobra
typedef struct {
  int x, y;
} Ponto;

struct Snake {
  Ponto cabeca;
};

// struct global para representar a cobra
struct Snake cobra;

int incX = 1, incY = 1;
int x = 3, y = 2;

// declaração da função drawSnake
void drawSnake();
void screenPutChar(char ch){
     printf("%c", ch);
}

void NomeJogo(int nextX, int nextY) {
    screenGotoxy(x, y);
    x = nextX;
    y = nextY;
    screenSetColor(WHITE, BLACK);
    printf("SNAKE GAME");
}

int main() {
    static int ch = 0;

    // inicializa a cobra
    cobra.cabeca.x = 0;
    cobra.cabeca.y = 0;

    screenInit(1);
    keyboardInit();

    NomeJogo(x, y);
    screenUpdate();

    while (ch != 10) // Enter
    {
        // Handle user input
        if (keyhit()) {
            ch = readch();
            screenUpdate();
        }

        // Atualiza a posição da cobra
        if (ch == 'W') {
            cobra.cabeca.y -= incY;
        } else if (ch == 'S') {
            cobra.cabeca.y += incY;
        } else if (ch == 'A') {
            cobra.cabeca.x -= incX;
        } else if (ch == 'D') {
            cobra.cabeca.x += incX;
        }

        drawSnake();
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}

// implementação da função drawSnake
void drawSnake() {
    // desenha a cobra na tela usando a biblioteca
    screenGotoxy(cobra.cabeca.x, cobra.cabeca.y);
    screenPutChar('*');
}
