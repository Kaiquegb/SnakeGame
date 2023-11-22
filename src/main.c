#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEGMENTS 100
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

typedef struct {
  int x, y;
} fragmento;

typedef struct {
  fragmento *fragmentos;
  int tamanho;
} Cobra;

Cobra cobra;

typedef struct {
  int x, y;
} Comida;

Comida comida;

void screenPutChar(char ch) { printf("%c", ch); }

char espaco[SCREEN_HEIGHT][SCREEN_WIDTH];

void bordas() {
  // Desenha bordas superiores e inferiores
  for (int i = 0; i < SCREEN_WIDTH; ++i) {
    screenGotoxy(i, 0);
    screenPutChar('_');
    screenGotoxy(i, SCREEN_HEIGHT - 1);
    screenPutChar('_');
  }

  // Desenha bordas laterais
  for (int i = 0; i < SCREEN_HEIGHT; ++i) {
    screenGotoxy(0, i);
    screenPutChar('|');
    screenGotoxy(SCREEN_WIDTH - 1, i);
    screenPutChar('|');
  }
}

void limpaedesenha() {
  for (int i = 0; i < SCREEN_HEIGHT; ++i) {
    for (int j = 0; j < SCREEN_WIDTH; ++j) {
      if (espaco[i][j] == '@' || espaco[i][j] == '*') {
        espaco[i][j] = ' '; // Limpa a posição anterior da cobra
      }
    }
  }

  // Desenha a cobra na matriz campo
  for (int i = 0; i < cobra.tamanho; ++i) {
    int x = cobra.fragmentos[i].x;
    int y = cobra.fragmentos[i].y;
    if (i == 0) {
      espaco[y][x] = '@'; // Cabeça da cobra
    } else {
      espaco[y][x] = '*'; // Corpo da cobra
    }
  }

  // Desenha a comida na matriz campo
  espaco[comida.y][comida.x] = 'O';
}

void moverCobra(int incX, int incY) {
  for (int i = cobra.tamanho - 1; i > 0; --i) {
    cobra.fragmentos[i].x = cobra.fragmentos[i - 1].x;
    cobra.fragmentos[i].y = cobra.fragmentos[i - 1].y;
  }

  cobra.fragmentos[0].x += incX;
  cobra.fragmentos[0].y += incY;

  for (int i = 1; i < cobra.tamanho; ++i) {
    if (cobra.fragmentos[0].x == cobra.fragmentos[i].x &&
        cobra.fragmentos[0].y == cobra.fragmentos[i].y) {
      // Game over - colidiu consigo mesma
      screenGotoxy(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2);
      printf("GAME OVER!");
      screenUpdate();
      exit(0);
    }
  }
}

void geracomida() {
  comida.x = 1 + rand() % (SCREEN_WIDTH - 2);
  comida.y = 1 + rand() % (SCREEN_HEIGHT - 2);
}

int score = 0;
void alimentaCobra() {
  if (cobra.fragmentos[0].x == comida.x && cobra.fragmentos[0].y == comida.y) {
    cobra.tamanho++;
    score = score + 10;
    geracomida();
  }
}

int main() {

  static int ch = 0;

  cobra.fragmentos = (fragmento *)malloc(MAX_SEGMENTS * sizeof(fragmento));
  cobra.tamanho = 2;                         // Inicializa com cabeça e corpo
  cobra.fragmentos[0].x = SCREEN_WIDTH / 2;  // Meio horizontal da tela
  cobra.fragmentos[0].y = SCREEN_HEIGHT / 2; // Meio vertical da tela
  cobra.fragmentos[1].x = SCREEN_WIDTH / 2 - 1; // Corpo
  cobra.fragmentos[1].y = SCREEN_HEIGHT / 2;    // Corpo

  screenInit(0);
  bordas();
  geracomida();
  keyboardInit();
  screenUpdate();

  while (ch != 'P') {
    if (keyhit()) {
      ch = readch();
    }

    if (ch == 'w' || ch == 'W') {
      moverCobra(0, -1);
    } else if (ch == 's' || ch == 'S') {
      moverCobra(0, 1);
    } else if (ch == 'a' || ch == 'A') {
      moverCobra(-1, 0);
    } else if (ch == 'd' || ch == 'D') {
      moverCobra(1, 0);
    }

    alimentaCobra();
    screenGotoxy(2, 2); // Posição para exibir o score
    printf("Score: %d", score);
    limpaedesenha();

    if (cobra.fragmentos[0].x >= SCREEN_WIDTH || cobra.fragmentos[0].x < 0 ||
        cobra.fragmentos[0].y >= SCREEN_HEIGHT || cobra.fragmentos[0].y < 0) {
      // Game over - colidiu com as paredes
      screenGotoxy(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2);
      printf("GAME OVER!");
      screenUpdate();
      exit(0);
    }

    // Desenha o campo na tela
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
      for (int j = 0; j < SCREEN_WIDTH; ++j) {
        screenGotoxy(j, i);
        screenPutChar(espaco[i][j]);
      }
    }
    screenUpdate();

    timerInit(10);

    while (!timerTimeOver()) {
      // Espera até que o tempo seja atingido
    }
  }

  keyboardDestroy();
  screenDestroy();
  timerDestroy();

  return 0;
}