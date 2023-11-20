#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define WIDTH 50
#define HEIGHT 20

// Struct para representar a cobra
typedef struct {
    int x, y;
} Ponto;

struct Snake {
    Ponto *corpo;
    int tamanho;
    int direcaoX, direcaoY;
};

// Struct global para representar a cobra
struct Snake cobra;

Ponto comida;
int comidaEaten = 1;

void screenPutChar(char ch) {
    printf("%c", ch);
}

void drawSnake() {
    // Desenha a cabeça da cobra
    screenGotoxy(cobra.corpo[0].x, cobra.corpo[0].y);
    screenPutChar('*');
}

void drawFood() {
    screenGotoxy(comida.x, comida.y);
    screenPutChar('#');
}

void updateSnake() {
    // Verifica se a cobra "comeu" a comida
    if (cobra.corpo[0].x == comida.x && cobra.corpo[0].y == comida.y) {
        // Aumenta o tamanho da cobra
        cobra.tamanho++;
        cobra.corpo = realloc(cobra.corpo, cobra.tamanho * sizeof(Ponto));
        cobra.corpo[cobra.tamanho - 1] = comida;
        comidaEaten = 1;
    } else {
        // Move o corpo da cobra
        for (int i = cobra.tamanho - 1; i > 0; i--) {
            cobra.corpo[i] = cobra.corpo[i - 1];
        }
    }

    // Atualiza a posição da cabeça da cobra
    cobra.corpo[0].x += cobra.direcaoX;
    cobra.corpo[0].y += cobra.direcaoY;

    // Verifica colisões com as paredes e ajusta a posição
    if (cobra.corpo[0].x >= WIDTH - 1) {
        cobra.corpo[0].x = 1;
    } else if (cobra.corpo[0].x <= 0) {
        cobra.corpo[0].x = WIDTH - 2;
    } else if (cobra.corpo[0].y >= HEIGHT - 1) {
        cobra.corpo[0].y = 1;
    } else if (cobra.corpo[0].y <= 0) {
        cobra.corpo[0].y = HEIGHT - 2;
    }
}

void placeFood() {
    if (comidaEaten) {
        do {
            comida.x = rand() % (WIDTH - 2) + 1;  // Evita gerar comida nas bordas
            comida.y = rand() % (HEIGHT - 2) + 1;
        } while (comida.x == cobra.corpo[0].x && comida.y == cobra.corpo[0].y);

        comidaEaten = 0;
    }
    drawFood();
}

int main() {
    screenInit(1);
    keyboardInit();

    screenDrawBorders(); // Desenha a borda
    screenUpdate();

    // Inicializa a cobra
    cobra.corpo = malloc(sizeof(Ponto));
    cobra.corpo[0].x = WIDTH / 2;
    cobra.corpo[0].y = HEIGHT / 2;
    cobra.tamanho = 1;
    cobra.direcaoX = 1;
    cobra.direcaoY = 0;

    while (1) {
        if (keyhit()) {
            char ch = readch();
            if (ch == 'w' && cobra.direcaoY != 1) {
                cobra.direcaoX = 0;
                cobra.direcaoY = -1;
            } else if (ch == 's' && cobra.direcaoY != -1) {
                cobra.direcaoX = 0;
                cobra.direcaoY = 1;
            } else if (ch == 'a' && cobra.direcaoX != 1) {
                cobra.direcaoX = -1;
                cobra.direcaoY = 0;
            } else if (ch == 'd' && cobra.direcaoX != -1) {
                cobra.direcaoX = 1;
                cobra.direcaoY = 0;
            }
           drawSnake();
        }

        screenClear();
        screenDrawBorders(); // Desenha a borda
        placeFood();
        screenUpdate();

        updateSnake();

        // Ajuste de velocidade do jogo
        timerInit(100); // Valor em milissegundos
        while (!timerTimeOver()) {}
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
