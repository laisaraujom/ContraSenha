CC = gcc
CFLAGS = -Wall
ARQUIVOS = main.c jogo.c regras.c matriz.c ranking.c
EXEC = contrasenha

all:
	$(CC) $(CFLAGS) $(ARQUIVOS) -o $(EXEC)

run: all
	./$(EXEC)

clean:
	rm -f $(EXEC)