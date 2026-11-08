// estrutura basica do no de regra

typedef int (*FuncaoValidadora)(const char *senha);

typedef struct Regra {
    int id; // pra salvar o número da regra
    char descricao[150]; // pra salvar a descrição da regra
    int cumprida; // verificação de cumprimento: 0 = nao, 1 = sim 
    int ativa;
    FuncaoValidadora validar;
    struct Regra *next;      // Ponteiro para o proximo no da lista de regras
} Regra;