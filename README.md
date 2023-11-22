# SnakeGame

##Jogo da Cobra em C
Este é um simples jogo da cobra criado em C. O jogador controla uma cobra que deve se mover pelo campo, comer comida e evitar colisões consigo mesma ou com as bordas do campo.

# Como Jogar
## Compilação:
Certifique-se de ter um compilador C instalado (como GCC).
Compile o código-fonte com o seguinte comando:

gcc main.c screen.c keyboard.c timer.c -o snake_game

Execução:
Após compilar, execute o jogo com:
./snake_game

## Controles:

Utilize as teclas 'W', 'A', 'S' e 'D' para movimentar a cobra para cima, esquerda, baixo e direita, respectivamente.
Para sair do jogo, pressione a tecla 'P'.

## Funcionalidades
- A cobra inicia no centro da tela.
- A comida aparece aleatoriamente no campo.
- A cobra cresce ao comer a comida.
- O jogo termina se a cobra colidir consigo mesma ou com as bordas do campo.

## Dependências
O jogo depende das seguintes bibliotecas:

stdio.h
stdlib.h
string.h
screen.h
keyboard.h
timer.h

