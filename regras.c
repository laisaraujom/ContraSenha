// includes
#include "regras.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//INÍCIO DO CÓDIGO:

// função pra alocar e preencher ID e descrição das regras
Regra* criar_regra(int id, const char *descricao, FuncaoValidadora funcao) {
    Regra *nova = (Regra *) malloc(sizeof(Regra));
    if (nova == NULL) return NULL;

    nova->id = id;
    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';
    nova->cumprida = 0;
    nova->ativa = (id == 1) ? 1 : 0;
    nova->validar = funcao;
    nova->next = NULL;

    return nova;
}

//REGRAS:

//FALTA FAZER: 3, 4, 5, 9, 10, 11, 12

// quando virar 1, ele entende qeu a vogal fpi digitada!!
int validar_regra_1(const char *senha) {
    int a = 0, e = 0, i = 0, o = 0, u = 0;
    for (int idx = 0; senha[idx] != '\0'; idx++) { 
        char c = senha[idx];
        if (c == 'a' || c == 'A') a = 1;
        if (c == 'e' || c == 'E') e = 1;
        if (c == 'i' || c == 'I') i = 1;
        if (c == 'o' || c == 'O') o = 1;
        if (c == 'u' || c == 'U') u = 1;
    }
    return (a && e && i && o && u);
}

// quando identificar um numero, vira 1
int validar_regra_2(const char *senha) {
    for (int idx = 0; senha[idx] != '\0'; idx++) {
        char c = senha[idx];
        if (c == '1') return 1;
        if (c == '2') return 1;
        if (c == '3') return 1;
        if (c == '4') return 1;
        if (c == '5') return 1;
        if (c == '6') return 1;
        if (c == '7') return 1;
        if (c == '8') return 1;
        if (c == '9') return 1;
        if (c == '0') return 1;
    }
    return 0;
}

//!! ver se tem um jeito mais simples !! (depois ne, vale pra a 7 e 8 tb)
int validar_regra_6(const char *senha) {
    int len = strlen(senha);
    for (int i = 0; i + 5 < len; i++) {
        if ((senha[i] == 'r' || senha[i] == 'R') &&
            (senha[i + 1] == 'e' || senha[i + 1] == 'E') &&
            (senha[i + 2] == 'c' || senha[i + 2] == 'C') &&
            (senha[i + 3] == 'i' || senha[i + 3] == 'I') &&
            (senha[i + 4] == 'f' || senha[i + 4] == 'F') &&
            (senha[i + 5] == 'e' || senha[i + 5] == 'E')) {
            return 1;
        }
    }
    return 0;
}

int validar_regra_7(const char *senha) {
    int len = strlen(senha);
    for (int i = 0; i + 2 < len; i++) {
        if (senha[i] == 'X' && senha[i + 1] == 'I' && senha[i + 2] == 'X') {
            return 1;
        }
        if (senha[i] == 'x' && senha[i + 1] == 'i' && senha[i + 2] == 'x') {
            return 1;
        }
    }
    return 0;
}

int validar_regra_8(const char *senha) {
    int len = strlen(senha);
    for (int i = 0; i + 2 < len; i++) {
        if ((senha[i] == 'p' || senha[i] == 'P') &&
            (senha[i + 1] == 'i' || senha[i + 1] == 'I') &&
            (senha[i + 2] == 'f' || senha[i + 2] == 'F')) {
            return 1;
        }
    }
    return 0;
}

//CARREGAR REGRAS:

Regra* carregar_todas_as_regras() {
    Regra *head = criar_regra(1, "Sua senha deve conter todas as vogais");
    Regra *atual = head;

    // conectando os nós adicionando todas as outras regras 

    atual->next = criar_regra(2, "Sua senha deve conter pelo menos um numero");
    atual = atual->next;

    atual->next = criar_regra(3, "Sua senha deve conter ao menos dois caracteres especiais (!, @, #...)");
    atual = atual->next;

    atual->next = criar_regra(4, "Ops! A senha não pode ter dois caracteres especiais iguais");
    atual = atual->next;

    atual->next = criar_regra(5, "Fazer o foguinho para destruir a senha"); //mudar esse nome depois
    atual = atual->next;

    atual->next = criar_regra(6, "Sua senha deve conter o nome da cidade dos programadores do jogo");
    atual = atual->next;

    atual->next = criar_regra(7, "Sua senha deve conter o dia da entrega em algarismos romanos");
    atual = atual->next;

    atual->next = criar_regra(8, "Sua senha deve conter o nome da melhor materia de CC");
    atual = atual->next;

    atual->next = criar_regra(9, "A soma dos algarismos da sua senha deve ser igual a 25");
    atual = atual->next;

    atual->next = criar_regra(10, "Sua senha deve conter a senha da wifi do CESAR");
    atual = atual->next;

    atual->next = criar_regra(11, "Sua senha deve conter um pais que comeca com 'M'");
    atual = atual->next;

    atual->next = criar_regra(12, "Ops! Sua senha deve ter, no maximo, 50 caracteres");
    atual = atual->next;

    return head;
}