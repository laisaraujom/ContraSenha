#ifndef MATRIZ_H
#define MATRIZ_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//matriz do jogo
typedef struct {
    int linhas;   
    int colunas;  
    char **grade; 
} Mapa;

typedef struct {
    int x;
    int y;
    int dir_x;
    int dir_y;
    char icone[10];
} Monstrinho;

Mapa* criar_mapa(int linhas, int colunas);

void liberar_mapa(Mapa **mapa);

void mover_monstrinho(Monstrinho *monstrinho, Mapa *mapa);

void desenha_senha(Mapa *mapa, const char *senha, Monstrinho *monstrinho);

void renderizar_mapa(Mapa *mapa);

void renderizar_terminal(Mapa *mapa, Monstrinho *monstrinho);

int checar_colisao_senha(Monstrinho *monstrinho, int linha_senha, int x_inicio_senha, int tamanho_senha);

void liberar_mapa(Mapa **mapa);

#endif