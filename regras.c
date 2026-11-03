// estrutura basica do no de regra
typedef struct Regra {
    int id; // pra salvar o número da regra
    char descricao[150]; // pra salvar a descrição da regra
    int cumprida;               // verificação de cumprimento: 0 = nao, 1 = sim 
    struct Regra *next;      // Ponteiro para o proximo no da lista de regras
} Regra;

// função pra alocar e preencher ID e descrição das regras
Regra* criar_regra(int id, const char *descricao) {
    Regra *nova = (Regra *) malloc(sizeof(Regra));
    if (nova == NULL) return NULL;

    nova->id = id;
    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';
    nova->cumprida = 0;
    nova->next = NULL;

    return nova;
}


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