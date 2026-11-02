#ifndef JOGO_H
#define JOGO_H

#define MAX_SENHA 100

// estrutura principal do jogo
typedef struct {
    char senha[MAX_SENHA];
    int pos_cursor;
    int fase_confirmacao;
} EstadoJogo;

#endif