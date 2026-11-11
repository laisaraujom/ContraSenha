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

Regra* criar_regra(int id, const char *descricao, FuncaoValidadora funcao);

void adicionar_regra(Regra **head, int id, const char *descricao, FuncaoValidadora funcao);

Regra* carregar_todas_as_regras(void);

int validar_regras_ativas(Regra *head, const char *senha);

void desbloquear_proxima_regra(Regra *head); 

void exibir_regras(Regra *head);

void liberar_lista_regras(Regra **head);