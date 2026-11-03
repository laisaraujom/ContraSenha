// estrutura basica do no de regra
typedef struct Regra {
    int id; // pra salvar o número da regra
    char descricao[150]; // pra salvar a descrição da regra
    int cumprida;               // verificação de cumprimento: 0 = nao, 1 = sim 
    struct Regra *proximo;      // Ponteiro para o proximo no da lista de regras
} Regra;

