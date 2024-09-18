#include <stdio.h>
#include <stdlib.h>

#define EMPTY 2
#define PLAYER_X 1
#define PLAYER_O 3

char converter(int numero)
{
    char letra;
    switch(numero)
    {
        case PLAYER_X: letra = 'X'; break;
        case PLAYER_O: letra = 'O'; break;
        default: letra = ' '; break;
    }
    return letra;
}

void mostrarTabuleiro(int matriz[4][5])
{
    printf("%c|%c|%c\n", converter(matriz[1][1]), converter(matriz[1][2]), converter(matriz[1][3]));
    printf("-----\n");
    printf("%c|%c|%c\n", converter(matriz[2][1]), converter(matriz[2][2]), converter(matriz[2][3]));
    printf("-----\n");
    printf("%c|%c|%c\n", converter(matriz[3][1]), converter(matriz[3][2]), converter(matriz[3][3]));
    
}

int verificaVitoria(int matriz[4][5])
{
    // Verificar linhas e colunas
    for (int i = 1; i <= 3; i++) {
        if (matriz[i][1] * matriz[i][2] * matriz[i][3] == 1) return PLAYER_X;
        if (matriz[i][1] * matriz[i][2] * matriz[i][3] == 27) return PLAYER_O;
        if (matriz[1][i] * matriz[2][i] * matriz[3][i] == 1) return PLAYER_X;
        if (matriz[1][i] * matriz[2][i] * matriz[3][i] == 27) return PLAYER_O;
    }

    // Verificar diagonais
    if (matriz[1][1] * matriz[2][2] * matriz[3][3] == 1) return PLAYER_X;
    if (matriz[1][1] * matriz[2][2] * matriz[3][3] == 27) return PLAYER_O;
    if (matriz[1][3] * matriz[2][2] * matriz[3][1] == 1) return PLAYER_X;
    if (matriz[1][3] * matriz[2][2] * matriz[3][1] == 27) return PLAYER_O;

    return EMPTY;
}

void usuarioJoga(int matriz[4][5], int jogador)
{
    int linha, coluna;
    printf("Jogador %c, por favor, escolha a linha e a coluna para fazer a sua jogada (1-3 1-3): ", converter(jogador));
    scanf("%d %d", &linha, &coluna);

    if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || matriz[linha][coluna] != EMPTY) {
        printf("Jogada inválida. Tente novamente.\n");
        usuarioJoga(matriz, jogador);
    } else {
        matriz[linha][coluna] = jogador;
    }
    //Limpa a tela da jogada anterior pra ficar mais organizado
    getchar();
    system("clear");
    
}

void maquinaJoga(int matriz[4][5])
{
    // Verifica se há uma oportunidade de vitória imediata
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (matriz[i][j] == EMPTY) {
                matriz[i][j] = PLAYER_O;  // Tenta jogar para ganhar
                if (verificaVitoria(matriz) == PLAYER_O) return;
                matriz[i][j] = EMPTY;  // Desfaz a jogada
            }
        }
        
    }

    // Verifica se precisa bloquear o adversário
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (matriz[i][j] == EMPTY) {
                matriz[i][j] = PLAYER_X;  // Tenta bloquear a vitória do adversário
                if (verificaVitoria(matriz) == PLAYER_X) {
                    matriz[i][j] = PLAYER_O;  // Se bloqueou a vitória, faz a jogada
                    return;
                }
                matriz[i][j] = EMPTY;  // Desfaz a jogada
            }
        }
        
    }

    // Se não há oportunidade de vitória imediata ou bloqueio, joga em qualquer célula vazia
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (matriz[i][j] == EMPTY) {
                matriz[i][j] = PLAYER_O;
                return;
            }
        }
        
    }
   
}

int main()
{
    int matriz[4][5] = {
        {2, EMPTY, EMPTY, EMPTY, 2},
        {2, EMPTY, EMPTY, EMPTY, 2},
        {2, EMPTY, EMPTY, EMPTY, 2},
        {2, 2, 2, 2, 2}
    };

    mostrarTabuleiro(matriz);

    int jogador_atual = PLAYER_X;
    int vencedor = verificaVitoria(matriz);

    while (vencedor == EMPTY) {
        if (jogador_atual == PLAYER_X) {
            usuarioJoga(matriz, jogador_atual);
        } else {
            maquinaJoga(matriz);
        }
        mostrarTabuleiro(matriz);
        jogador_atual = (jogador_atual == PLAYER_X) ? PLAYER_O : PLAYER_X;
        vencedor = verificaVitoria(matriz);
        printf("\n");
    }

    if (vencedor == PLAYER_X) {
        printf("O jogador X venceu!\n");
    } else if (vencedor == PLAYER_O) {
        printf("O jogador O venceu!\n");
    } else {
        printf("Empate!\n");
    }

    return 0;
}
