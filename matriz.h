//matriz do jogo
typedef struct {
    int linhas;   
    int colunas;  
    char **grade; 
} Mapa;

Mapa* criar_mapa(int linhas, int colunas);

void liberar_mapa(Mapa **mapa);