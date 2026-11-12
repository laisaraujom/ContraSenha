#include "matriz.h"

Mapa* criar_mapa(int linhas, int colunas) {
    Mapa *mapa = (Mapa *) malloc(sizeof(Mapa));
    if (mapa == NULL) return NULL;

    mapa->linhas = linhas;
    mapa->colunas = colunas;

    mapa->grade = (char **) malloc(linhas * sizeof(char *));
    if (mapa->grade == NULL) {
        free(mapa);
        return NULL;
    }

    for (int i = 0; i < linhas; i++) {
        mapa->grade[i] = (char *) malloc(colunas * sizeof(char));
        if (mapa->grade[i] == NULL) {
            for (int j = 0; j < i; j++) free(mapa->grade[j]);
            free(mapa->grade);
            free(mapa);
            return NULL;
        }
    }

    return mapa;
}
void liberar_mapa(Mapa **mapa) {
    if (mapa == NULL || *mapa == NULL) return;

    for (int i = 0; i < (*mapa)->linhas; i++) {
        free((*mapa)->grade[i]);
    }

    free((*mapa)->grade);
    free(*mapa);
    *mapa = NULL;
}

void limpar_mapa(Mapa *mapa) {
    for (int i = 0; i < mapa->linhas; i++) {
        for (int j = 0; j < mapa->colunas; j++) {
            mapa->grade[i][j] = ' ';
        }
    }
}

void mover_monstrinho(Monstrinho *monstrinho, Mapa *mapa) {
    int prox_x = monstrinho->x + monstrinho->dir_x;
    int prox_y = monstrinho->y + monstrinho->dir_y;

    if (prox_x <= 0 || prox_x >= mapa->colunas - 1) {
        monstrinho->dir_x *= -1;
    }
    if (prox_y <= 0 || prox_y >= mapa->linhas - 1) {
        monstrinho->dir_y *= -1;
    }

    monstrinho->x += monstrinho->dir_x;
    monstrinho->y += monstrinho->dir_y;
}

int checar_colisao_senha(Monstrinho *monstrinho, int linha_senha, int x_inicio_senha, int tamanho_senha) {
    if (monstrinho->y == linha_senha) { //primeiro ve se ele ta na msm linha da senha
        if (monstrinho->x >= x_inicio_senha && monstrinho->x < (x_inicio_senha + tamanho_senha)) { // se tiver, ele entra aqui e vê se o lugar q ele ta coincide com algum caractere da senha
            return monstrinho->x - x_inicio_senha; // dá um return do índice atingido
        }
    }
    return -1; // retorna -1 se n atingir nada (pq se retornasse 0 ia ser a posição 0 da senha)
}