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

// quando virar 1, ele entende que a vogal foi digitada!!
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


int validar_regra_3(const char *senha) {
    for (int idx = 0; senha[idx] != '\0'; idx++) {
        if (isalnum(senha[idx]) == 0 && senha[idx] != ' ') {
            return 1;
        }
    }
    return 0;
}

int validar_regra_4(const char *senha) {
    for (int idx = 0; senha[idx] != '\0'; idx++) {
        if (isupper(senha[idx]) != 0) {
            return 1;
        }
    }
    return 0;
}

int validar_regra_5(const char *senha) {
    int len = strlen(senha);

    if (len < 2) {
        return 0;
    }

    if (senha[0] == senha[len - 1] && senha[1] == senha[len - 2]) {
        return 1;
    } else {
        return 0;
    }
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

int validar_regra_9(const char *senha) {
    int soma = 0;
    for (int i = 0; senha[i] != '\0'; i++) {
        char c = senha[i];
        if (c >= '0' && c <= '9') {
            soma = soma + (c - '0');
        }
    }
    if (soma == 25) {
        return 1;
    }
    return 0;
}
// vale para a 10 e 11
int tem_palavra(const char *senha, const char *palavra) {
    int len_senha = strlen(senha);
    int len_palavra = strlen(palavra);
    for (int i = 0; i + len_palavra <= len_senha; i++) {
        int igual = 1;
        for (int j = 0; j < len_palavra; j++) {
            char c = senha[i + j];
            if (c >= 'A' && c <= 'Z') {
                c = c + 32;
            }
            if (c != palavra[j]) {
                igual = 0;
                break;
            }
        }
        if (igual == 1) {
            return 1;
        }
    }
    return 0;
}

int validar_regra_10(const char *senha) {
    if (tem_palavra(senha, "bemvindoaocesar")) {
        return 1;
    }
    return 0;
}

int validar_regra_11(const char *senha) {
    if (tem_palavra(senha, "mexico") || tem_palavra(senha, "marrocos") ||
        tem_palavra(senha, "madagascar") || tem_palavra(senha, "malasia") ||
        tem_palavra(senha, "maldivas") || tem_palavra(senha, "malaui") ||
        tem_palavra(senha, "mali") || tem_palavra(senha, "malta") ||
        tem_palavra(senha, "mauricio") || tem_palavra(senha, "mauritania") ||
        tem_palavra(senha, "micronesia") || tem_palavra(senha, "mianmar") ||
        tem_palavra(senha, "monaco") || tem_palavra(senha, "mongolia") ||
        tem_palavra(senha, "montenegro") || tem_palavra(senha, "mozambique") ||
        tem_palavra(senha, "mocambique") || tem_palavra(senha, "macedonia")) {
        return 1;
    }
    return 0;
}

int validar_regra_12(const char *senha) {
    int tam = 0;
    while (senha[tam] != '\0') {
        tam++;
    }
    if (tam > 0 && tam <= 50) {
        return 1;
    }
    return 0;
}

// Aloca dinamicamente um novo nó de regra para a lista encadeada
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
// Insere um novo nó de regra no final da lista encadeada
void adicionar_regra(Regra **head, int id, const char *descricao, FuncaoValidadora funcao) {
    Regra *nova = criar_regra(id, descricao, funcao); 
    if (nova == NULL) return; 

    if (*head == NULL) { 
        *head = nova; 
    } else { 
        Regra *atual = *head; 
        while (atual->next != NULL) atual = atual->next; 
        atual->next = nova;
    }
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
    atual->next = criar_regra(5, "Os dois primeiros caracteres da senha devem ser iguais aos dois últimos, mas em ordem invertida."); 
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
// verifica se todoas a regras ativias estao sendo executadas corretamente 
int validar_regras_ativas(Regra *head, const char *senha) {
    Regra *atual = head;
    int todas_ok = 1;
    while (atual != NULL && atual->ativa == 1) {
        if (atual->validar != NULL) {
            atual->cumprida = atual->validar(senha);
        }
        if (atual->cumprida == 0) {
            todas_ok = 0;
        }
        atual = atual->next;
    }
    return todas_ok;
}

void desbloquear_proxima_regra(Regra *head) {
    Regra *atual = head;
    while (atual != NULL && atual->ativa == 1) {
        if (atual->next != NULL && atual->next->ativa == 0) { 
            atual->next->ativa = 1;
            break;
        }
        atual = atual->next;
    }
}