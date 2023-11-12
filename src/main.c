#include <string.h>
#include <stdlib.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int incX = 1, incY = 1;
int x = 3, y = 2;


void printHello(int nextX, int nextY)
{
    screenGotoxy(x, y);
    x = nextX;
    y = nextY;
    screenSetColor(WHITE, BLACK);
    printf("SNAKE GAME");
}

int main()
{
    static int ch = 0;

    screenInit(1);
    keyboardInit();

    printHello(x, y);
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