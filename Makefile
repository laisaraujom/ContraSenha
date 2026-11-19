CC = gcc
CFLAGS = -Wall -Icli-lib/include
LIB = cli-lib/src/screen.c cli-lib/src/keyboard.c cli-lib/src/timer.c
ARQUIVOS = main.c jogo.c regras.c matriz.c ranking.c $(LIB)
EXEC = contrasenha

all:
	$(CC) $(CFLAGS) $(ARQUIVOS) -o $(EXEC)

run: all
	./$(EXEC)

clean:
	rm -f $(EXEC)
