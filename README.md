# ContraSenha

<p align="center">
  <img src="contrasenha-logo.png" alt="Logo do jogo" width="100%">
</p>

Repositório destinado ao desenvolvimento do jogo ContraSenha, na linguagem C, como requisito para obtenção de nota na disciplina de Programação Imperativa e Funcional (PIF).

### Requisitos:
Usar obrigatoriamente:
- Estruturas (structs);
- Ponteiros;
- Alocação dinâmica de memória;
- Listas encadeadas;
- Matrizes
- Escrita e leitura em arquivo;

### Descrição do jogo:
O jogador deve inserir uma senha e, com o andamento do jogo, regras aparecerão e este deverá alterá-la para que cumpra todos os requisitos.

"Hoje em dia, as senhas são utilizadas para tudo no nosso cotidiano. Quanto mais difíceis de serem adivinhadas, mais seguras estão nossas informações. ContraSenha é um jogo onde você tem que obedecer todas as nossas regras para criar sua senha segura e manter seus dados a salvo. Será que você consegue cumprir todos os requisitos?"

### Como compilar e executar:
O jogo roda em **Linux** ou **macOS** (no Windows, é preciso usar o WSL com Ubuntu), pois utiliza a biblioteca cli-lib, que depende do `termios.h`. É necessário ter o **gcc** e o **make** instalados.

1. Clonar o repositório:
`git clone https://github.com/laisaraujom/ContraSenha`

2. Entrar na pasta:
`cd ContraSenha`

3. Compilar:
`make`

4. Executar:
`./contrasenha`

Ou, para compilar e executar de uma vez: `make run`. Para apagar o executável: `make clean`.

Recomendamos abrir o terminal em **tela cheia**, para que o mapa e as regras apareçam inteiros na tela.

**Controles:** digite a senha normalmente · setas ← → movem o cursor · Backspace apaga · TAB sai do jogo · na confirmação, digite `ver` + Enter para revelar a senha.

### Biblioteca utilizada:
- [**cli-lib**](https://github.com/tgfb/cli-lib), de Tiago Barros, distribuída sob a licença **BSD 3-Clause**. Ela é usada para controlar o **teclado** (leitura de teclas sem precisar de Enter), a **tela** (posicionamento do cursor) e o **timer** (ritmo de atualização do jogo). A biblioteca está na pasta `cli-lib/`, sem modificações, junto com o seu README e a sua licença originais.

1. Clonar o repositório:
### Links Úteis:
- [Vídeo de demonstração e breve explicação do jogo](https://www.youtube.com/watch?v=TUTJDmAcIT4)
- [Slides de apresentação](https://canva.link/13s5dd9gfzm1kks)

### Membros:
| Nome | E-mail |
|---|---|
| Eraldo Carneiro Leão Neto | [ecln@cesar.school](https://mail.google.com/mail/?view=cm&amp;fs=1&amp;to=ecln@cesar.school&amp;su=Contato%20sobre%20o%20projeto%20de%20pif) |
| Gabriella de Lima Albuquerque | [gla3@cesar.school](https://mail.google.com/mail/?view=cm&amp;fs=1&amp;to=gla3@cesar.school&amp;su=Contato%20sobre%20o%20projeto%20de%20pif) |
| Laís Araújo Moura | [lam2@cesar.school](https://mail.google.com/mail/?view=cm&amp;fs=1&amp;to=lam2@cesar.school&amp;su=Contato%20sobre%20o%20projeto%20de%20pif) |
