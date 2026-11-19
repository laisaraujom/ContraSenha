#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include "regras.h"
#include "jogo.h"
#include <time.h>
#include "ranking.h"

void ativar_modo_raw(struct termios *orig_termios) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    printf("\033[?25l");
}

void desativar_modo_raw(struct termios *orig_termios) {
    printf("\033[?25h");
    tcsetattr(STDIN_FILENO, TCSANOW, orig_termios);
}

void limpar_tela(void) {
    printf("\033[2J\033[1;1H");
}

void reposicionar_cursor(void){
    printf("\0333[H");
}

int kbhit(void) {
    struct timeval tv = {0, 20000};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

void desenhar_caixa(const char *texto, int cursor) {
    int tam = strlen(texto);
    int largura = 66;
    if (tam + 4 > 66) {
        largura = tam + 4;
    }

    printf("╭");
    for (int i = 0; i < largura; i++) {
        printf("─");
    }
    printf("╮\n");

    printf("│ ");
    for (int i = 0; i <= tam; i++) {
        if (i == cursor) {
            printf("|");
        }
        if (i < tam) {
            printf("%c", texto[i]);
        }
    }
    for (int i = tam + 1; i < largura - 1; i++) {
        printf(" ");
    }
    printf("│\n");

    printf("╰");
    for (int i = 0; i < largura; i++) {
        printf("─");
    }
    printf("╯\n");
}

int main(void) {
    EstadoJogo *jogo = inicializar_jogo(12, 68);
    if (jogo == NULL) {
        printf("Erro ao inicializar o jogo!\n");
        return 1;
    }

    char comando[100];
    int em_espera = 1;

    while (em_espera == 1 && jogo->jogo_ativo) {
        limpar_tela();
        printf("  * ContraSenha *\n\n");
        printf("  ╭──────────────────────────╮\n");
        printf("  │  [1] ─── INICIAR JOGO    │\n");
        printf("  │  [2] ─── RANKING         │\n");
        printf("  │  [3] ─── SAIR            │\n");
        printf("  ╰──────────────────────────╯\n\n");
        printf(" Escolha uma opção: ");

        if (fgets(comando, sizeof(comando), stdin) != NULL) {
            for (int i = 0; comando[i] != '\0'; i++) {
                if (comando[i] == '\n') {
                    comando[i] = '\0';
                    break;
                }
            }

            if (strcmp(comando, "1") == 0 || strcmp(comando, "iniciar") == 0) {
                em_espera = 0;
            } else if (strcmp(comando, "2") == 0 || strcmp(comando, "ranking") == 0) {
                limpar_tela();
                exibir_ranking();
                printf("\nPressione ENTER para voltar ao menu principal...");
                fgets(comando, sizeof(comando), stdin);
            } else if (strcmp(comando, "3") == 0 || strcmp(comando, "sair") == 0) {
                jogo->jogo_ativo = 0;
                em_espera = 0;
            } else if (strcmp(comando, "3") == 0 || strcmp(comando, "sair") == 0) {
                jogo->jogo_ativo = 0;
                em_espera = 0;
            }
        }
    }

    if (!jogo->jogo_ativo) {
        finalizar_jogo(&jogo);
        return 0;
    }

    struct termios orig_termios;
    ativar_modo_raw(&orig_termios);
    time_t inicio = time(NULL);
    int venceu = 0;
    int tempo_total = 0;

    printf("\033[H"); //pra limpar a tela

    while (jogo->jogo_ativo) {
        limpar_tela();
        printf("  * ContraSenha *\n\n");

        processar_rodada(jogo);

        if (jogo->fase_confirmacao) {
            printf("\nPor favor, confirme a sua senha:\n");
            desenhar_caixa(jogo->senha_confirmacao, jogo->posicao_cursor_confirmacao);
            printf("[Digite a senha igual | 'ver' = Revelar | TAB = Sair]\n");

            jogo->senha_confirmacao[jogo->tamanho_confirmacao] = '\0';

            if (strcmp(jogo->senha, jogo->senha_confirmacao) == 0 && jogo->tamanho_confirmacao > 0) {
                limpar_tela();
                printf("\nSenha alterada com sucesso! Agora seus dados estarao seguros\n\n");
                tempo_total = (int)(time(NULL) - inicio);
                printf("Seu tempo: %d segundos\n", tempo_total);
                fflush(stdout);
                sleep(3);
                venceu = 1;

                jogo->jogo_ativo = 0;
                continue;
            }

            if (kbhit()) {
                char c;
                if (read(STDIN_FILENO, &c, 1) == 1) {
                    if (c == 27) {
                        char seq[2];
                        if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                            if (seq[0] == '[' && seq[1] == 'D' && jogo->posicao_cursor_confirmacao > 0) {
                                jogo->posicao_cursor_confirmacao--;
                            } else if (seq[0] == '[' && seq[1] == 'C' && jogo->posicao_cursor_confirmacao < jogo->tamanho_confirmacao) {
                                jogo->posicao_cursor_confirmacao++;
                            }
                        }
                    } else if (c == '\n' || c == '\r') {
                        if (strcmp(jogo->senha_confirmacao, "ver") == 0) {
                            printf("\nSenha atual: %s\n", jogo->senha);
                            fflush(stdout);
                            sleep(3);
                            jogo->tamanho_confirmacao = 0;
                            jogo->posicao_cursor_confirmacao = 0;
                            jogo->senha_confirmacao[0] = '\0';
                        }
                    } else if (c == 9) {
                        jogo->jogo_ativo = 0;
                    } else if (c == 127 || c == '\b') {
                        apagar_caractere_confirmacao(jogo);
                    } else if (c >= 32 && c <= 126) {
                        inserir_caractere_confirmacao(jogo, c);
                    }
                }
            }
        } else {
            printf("\nEscolha uma senha:\n");
            desenhar_caixa(jogo->senha, jogo->posicao_cursor);
            printf("[Controles: Setas <-/-> movem | Backspace apaga | TAB = Sair]\n");

            if (kbhit()) {
                char c;
                if (read(STDIN_FILENO, &c, 1) == 1) {
                    if (c == 27) {
                        char seq[2];
                        if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                            if (seq[0] == '[' && seq[1] == 'D' && jogo->posicao_cursor > 0) {
                                jogo->posicao_cursor--;
                            } else if (seq[0] == '[' && seq[1] == 'C' && jogo->posicao_cursor < jogo->tamanho_senha) {
                                jogo->posicao_cursor++;
                            }
                        }
                    } else if (c == 9) {
                        jogo->jogo_ativo = 0;
                    } else if (c == 127 || c == '\b') {
                        apagar_caractere_na_posicao(jogo);
                    } else if (c >= 32 && c <= 126) {
                        inserir_caractere_na_posicao(jogo, c);
                    }
                }
            }
        }

        printf("\033[J"); //pra limpar a tela
        fflush(stdout);
        usleep(30000);
    }

    desativar_modo_raw(&orig_termios);
    if (venceu) {
    tcflush(STDIN_FILENO, TCIFLUSH);   // descarta teclas que sobraram do jogo
    char resp[10];
    printf("\nDeseja salvar seu tempo (%d s) no ranking? (s/n): ", tempo_total);
    if (fgets(resp, sizeof(resp), stdin) != NULL && (resp[0] == 's' || resp[0] == 'S')) {
        char nome[TAM_NOME];
        printf("Digite seu nome: ");
        if (fgets(nome, sizeof(nome), stdin) != NULL) {
            nome[strcspn(nome, "\n")] = '\0';
            for (int i = 0; nome[i]; i++) {
                if (nome[i] == ';') nome[i] = ' ';   // ';' quebraria o arquivo
            }
            if (nome[0] != '\0') {
                registrar_no_ranking(nome, tempo_total);
                printf("Tempo salvo no ranking!\n");
                }
            }
        }
    }
    finalizar_jogo(&jogo);

    return 0;
}