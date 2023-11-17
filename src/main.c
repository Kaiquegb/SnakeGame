#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

Cobrinha cobra;

int incX = 1, incY = 1;
int x = 3, y = 2;


void NomeJogo(int nextX, int nextY)
{
    screenGotoxy(x, y);
    x = nextX;
    y = nextY;
    screenSetColor(WHITE, BLACK);
    printf("SNAKE GAME");
}

void drawSnake() {
    // desenha a cobra na tela
    screenGotoxy(cobra.cabeca.x, cobra.cabeca.y);
    screenPutChar('*');
}

int main()
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();

    NomeJogo(x, y);
    screenUpdate();

    while (ch != 10) //enter
    {
        // Handle user input
        if (keyhit())
        {
            ch = readch();
            screenUpdate();
        }

    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}