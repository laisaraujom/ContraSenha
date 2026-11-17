#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "regras.h"

// estrutura principal do jogo
typedef struct {
    char *senha;
    int posicao_cursor;
    int tamanho_senha;
    int capacidade_senha;
    char *senha_confirmacao;
    int tamanho_confirmacao;
    int capacidade_confirmacao;
    int posicao_cursor_confirmacao;
    int fase_confirmacao;
    
    Regra *lista_regras;
    Mapa *mapa;
    Monstrinho monstrinho;
    int jogo_ativo;
    int pontuacao;
} EstadoJogo;


EstadoJogo* inicializar_jogo(int linhas_mapa, int colunas_mapa);
void inserir_caractere_na_posicao(EstadoJogo *jogo, char c);
void apagar_caractere_na_posicao(EstadoJogo *jogo);
void destruir_caractere_senha(EstadoJogo *jogo, int indice);
void inserir_caractere_confirmacao(EstadoJogo *jogo, char c);
void apagar_caractere_confirmacao(EstadoJogo *jogo);
void processar_rodada(EstadoJogo *jogo);
void finalizar_jogo(EstadoJogo **jogo);

#endif