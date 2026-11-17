#include "jogo.h"
#include <sys/time.h>

void renderizar_mapa_com_emoji(Mapa *mapa, Monstrinho *monstrinho);

long long obter_tempo_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

EstadoJogo* inicializar_jogo(int linhas_mapa, int colunas_mapa) {
    EstadoJogo *jogo = malloc(sizeof(EstadoJogo));
    if (jogo == NULL) {
        return NULL;
    }

    jogo->capacidade_senha = 200;
    jogo->tamanho_senha = 0;
    jogo->posicao_cursor = 0;
    jogo->senha = malloc(jogo->capacidade_senha);
    if (jogo->senha == NULL) {
        free(jogo);
        return NULL;
    }
    jogo->senha[0] = '\0';

    jogo->capacidade_confirmacao = 200;
    jogo->tamanho_confirmacao = 0;
    jogo->posicao_cursor_confirmacao = 0;
    jogo->senha_confirmacao = malloc(jogo->capacidade_confirmacao);
    if (jogo->senha_confirmacao == NULL) {
        free(jogo->senha);
        free(jogo);
        return NULL;
    }
    jogo->senha_confirmacao[0] = '\0';
    jogo->fase_confirmacao = 0;

    jogo->mapa = criar_mapa(linhas_mapa, colunas_mapa);
    jogo->lista_regras = carregar_todas_as_regras();

    jogo->monstrinho.x = 2;
    jogo->monstrinho.y = 2;
    jogo->monstrinho.dir_x = 1;
    jogo->monstrinho.dir_y = 1;
    strcpy(jogo->monstrinho.icone, "🚀");

    jogo->jogo_ativo = 1;
    jogo->pontuacao = 0;

    return jogo;
}

void finalizar_jogo(EstadoJogo **jogo) {
    if (jogo == NULL || *jogo == NULL) {
        return;
    }

    free((*jogo)->senha);
    free((*jogo)->senha_confirmacao);

    liberar_mapa(&((*jogo)->mapa));
    liberar_lista_regras(&((*jogo)->lista_regras));

    free(*jogo);
    *jogo = NULL;
}

void inserir_caractere_na_posicao(EstadoJogo *jogo, char c) {
    if (jogo->tamanho_senha + 1 >= jogo->capacidade_senha) {
        jogo->capacidade_senha = jogo->capacidade_senha + 20;
        char *temp = realloc(jogo->senha, jogo->capacidade_senha);
        if (temp == NULL) {
            return;
        }
        jogo->senha = temp;
    }

    for (int i = jogo->tamanho_senha; i >= jogo->posicao_cursor; i--) {
        jogo->senha[i + 1] = jogo->senha[i];
    }

    jogo->senha[jogo->posicao_cursor] = c;
    jogo->tamanho_senha++;
    jogo->posicao_cursor++;
    jogo->senha[jogo->tamanho_senha] = '\0';
}

void apagar_caractere_na_posicao(EstadoJogo *jogo) {
    if (jogo->posicao_cursor <= 0 || jogo->tamanho_senha <= 0) {
        return;
    }

    for (int i = jogo->posicao_cursor - 1; i < jogo->tamanho_senha; i++) {
        jogo->senha[i] = jogo->senha[i + 1];
    }

    jogo->tamanho_senha--;
    jogo->posicao_cursor--;
    jogo->senha[jogo->tamanho_senha] = '\0';
}

void inserir_caractere_confirmacao(EstadoJogo *jogo, char c) {
    if (jogo->tamanho_confirmacao + 1 >= jogo->capacidade_confirmacao) {
        jogo->capacidade_confirmacao = jogo->capacidade_confirmacao + 20;
        char *temp = realloc(jogo->senha_confirmacao, jogo->capacidade_confirmacao);
        if (temp == NULL) {
            return;
        }
        jogo->senha_confirmacao = temp;
    }

    for (int i = jogo->tamanho_confirmacao; i >= jogo->posicao_cursor_confirmacao; i--) {
        jogo->senha_confirmacao[i + 1] = jogo->senha_confirmacao[i];
    }

    jogo->senha_confirmacao[jogo->posicao_cursor_confirmacao] = c;
    jogo->tamanho_confirmacao++;
    jogo->posicao_cursor_confirmacao++;
    jogo->senha_confirmacao[jogo->tamanho_confirmacao] = '\0';
}

void apagar_caractere_confirmacao(EstadoJogo *jogo) {
    if (jogo->posicao_cursor_confirmacao <= 0 || jogo->tamanho_confirmacao <= 0) {
        return;
    }

    for (int i = jogo->posicao_cursor_confirmacao - 1; i < jogo->tamanho_confirmacao; i++) {
        jogo->senha_confirmacao[i] = jogo->senha_confirmacao[i + 1];
    }

    jogo->tamanho_confirmacao--;
    jogo->posicao_cursor_confirmacao--;
    jogo->senha_confirmacao[jogo->tamanho_confirmacao] = '\0';
}

void destruir_caractere_senha(EstadoJogo *jogo, int indice) {
    if (indice < 0 || indice >= jogo->tamanho_senha) {
        return;
    }

    for (int i = indice; i < jogo->tamanho_senha - 1; i++) {
        jogo->senha[i] = jogo->senha[i + 1];
    }

    jogo->tamanho_senha--;
    jogo->senha[jogo->tamanho_senha] = '\0';

    if (jogo->posicao_cursor > jogo->tamanho_senha) {
        jogo->posicao_cursor = jogo->tamanho_senha;
    }
}

void processar_rodada(EstadoJogo *jogo) {
    static long long ultimo_movimento_ms = 0;
    static int ja_colidiu = 0;
    long long tempo_atual_ms = obter_tempo_ms();

    int total_regras = 0;
    Regra *r = jogo->lista_regras;
    while (r != NULL) {
        total_regras++;
        r = r->next;
    }

    int desbloqueou = 1;
    while (desbloqueou == 1) {
        desbloqueou = 0;
        if (validar_regras_ativas(jogo->lista_regras, jogo->senha)) {
            Regra *atual = jogo->lista_regras;
            while (atual != NULL) {
                if (atual->ativa && atual->next != NULL && !atual->next->ativa) {
                    atual->next->ativa = 1;
                    desbloqueou = 1;
                    break;
                }
                atual = atual->next;
            }
        }
    }

    int regras_cumpridas = 0;
    r = jogo->lista_regras;
    while (r != NULL && r->ativa) {
        if (r->cumprida) {
            regras_cumpridas++;
        }
        r = r->next;
    }

    int linha_senha = jogo->mapa->linhas / 2;

    if (regras_cumpridas == total_regras && total_regras == 12) {
        jogo->fase_confirmacao = 1;
    } else {
        if (ultimo_movimento_ms == 0) {
            ultimo_movimento_ms = tempo_atual_ms;
        } else if (tempo_atual_ms - ultimo_movimento_ms >= 500) {
            mover_monstrinho(&(jogo->monstrinho), jogo->mapa);
            ultimo_movimento_ms = tempo_atual_ms;

            if (jogo->monstrinho.y != linha_senha) {
                ja_colidiu = 0;
                strcpy(jogo->monstrinho.icone, "🚀");
            }
        }

        if (jogo->tamanho_senha > 0) {
            int x_inicio = (jogo->mapa->colunas - jogo->tamanho_senha) / 2;
            if (x_inicio < 1) {
                x_inicio = 1;
            }

            int atingido = checar_colisao_senha(&(jogo->monstrinho), linha_senha, x_inicio, jogo->tamanho_senha);

            if (atingido >= 0 && atingido < jogo->tamanho_senha && ja_colidiu == 0) {
                strcpy(jogo->monstrinho.icone, "💥");
                destruir_caractere_senha(jogo, atingido);
                ja_colidiu = 1;
            }
        }
    }

    if (jogo->fase_confirmacao) {
        char senha_escondida[200];
        int len = strlen(jogo->senha);
        if (len > 199) {
            len = 199;
        }
        for (int i = 0; i < len; i++) {
            senha_escondida[i] = '*';
        }
        senha_escondida[len] = '\0';
        desenhar_elementos(jogo->mapa, senha_escondida, &(jogo->monstrinho));
    } else {
        desenhar_elementos(jogo->mapa, jogo->senha, &(jogo->monstrinho));
    }

    renderizar_mapa_com_emoji(jogo->mapa, &(jogo->monstrinho));
    exibir_regras(jogo->lista_regras);

    jogo->pontuacao++;
}