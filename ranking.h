#ifndef RANKING_H
#define RANKING_H

#define ARQUIVO_RANKING "ranking.txt"
#define MAX_RANKING 10
#define TAM_NOME 50

typedef struct Jogador {
    char nome[TAM_NOME];
    int tempo;
    struct Jogador *next;
} Jogador;

Jogador* carregar_ranking(void);
void inserir_ordenado(Jogador **lista, const char *nome, int tempo);
void salvar_ranking(Jogador *lista);
void liberar_ranking(Jogador **lista);
void exibir_ranking(void);
void registrar_no_ranking(const char *nome, int tempo);

#endif