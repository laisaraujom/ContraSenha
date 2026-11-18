#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

// insere mantendo a lista ordenada pelo menor tempo
void inserir_ordenado(Jogador **lista, const char *nome, int tempo) {
    Jogador *novo = malloc(sizeof(Jogador));
    if (novo == NULL) return;

    strncpy(novo->nome, nome, TAM_NOME - 1);
    novo->nome[TAM_NOME - 1] = '\0';
    novo->tempo = tempo;
    novo->next = NULL;

    if (*lista == NULL || tempo < (*lista)->tempo) {
        novo->next = *lista;
        *lista = novo;
        return;
    }

    Jogador *atual = *lista;
    while (atual->next != NULL && atual->next->tempo <= tempo) {
        atual = atual->next;
    }
    novo->next = atual->next;
    atual->next = novo;
}

Jogador* carregar_ranking(void) {
    Jogador *lista = NULL;
    FILE *arq = fopen(ARQUIVO_RANKING, "r");
    if (arq == NULL) return NULL;   // arquivo ainda não existe

    char nome[TAM_NOME];
    int tempo;
    while (fscanf(arq, " %49[^;];%d", nome, &tempo) == 2) {
        inserir_ordenado(&lista, nome, tempo);
    }
    fclose(arq);
    return lista;
}

// grava só os 10 primeiros
void salvar_ranking(Jogador *lista) {
    FILE *arq = fopen(ARQUIVO_RANKING, "w");
    if (arq == NULL) return;

    int cont = 0;
    while (lista != NULL && cont < MAX_RANKING) {
        fprintf(arq, "%s;%d\n", lista->nome, lista->tempo);
        lista = lista->next;
        cont++;
    }
    fclose(arq);
}

void liberar_ranking(Jogador **lista) {
    while (*lista != NULL) {
        Jogador *temp = *lista;
        *lista = (*lista)->next;
        free(temp);
    }
}

void exibir_ranking(void) {
    Jogador *lista = carregar_ranking();

    printf("\n\n  ---------- TOP %d CONTRASENHA ----------\n\n", MAX_RANKING);
    if (lista == NULL) {
        printf("  Nenhum jogador no ranking ainda.\n");
    } else {
        int pos = 1;
        for (Jogador *j = lista; j != NULL && pos <= MAX_RANKING; j = j->next, pos++) {
            printf("  %2d. %-25s %5d s\n", pos, j->nome, j->tempo);
        }
    }
    liberar_ranking(&lista);
}

void registrar_no_ranking(const char *nome, int tempo) {
    Jogador *lista = carregar_ranking();
    inserir_ordenado(&lista, nome, tempo);
    salvar_ranking(lista);
    liberar_ranking(&lista);
}