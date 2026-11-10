// lista das regras que a gente tem que validar

#include <stdio.h> //caso precise
#include <stdlib.h> //caso precise
#include <string.h> //caso precise
//importar a lista de regras

OK Regra 1: "Sua senha deve conter todas as vogais"; //lembrar de olhar maiusculas e minusculas (ver se vale usar lower na verificação)
OK Regra 2: "Sua senha deve conter pelo menos um numero"; //verificação dos digitos 0 a 9
OK Regra 3: "Sua senha deve conter ao menos um caracter especial (!, @, #...)"    
OK Regra 4: "Sua senha deve conter ao menos uma letra maiúscula"; //verificação de letras maiusculas
OK Regra 5: "espelhar os últimos dois caracteres"; 
OK Regra 6: "Sua senha deve conter o nome da cidade dos programadores do jogo"; //verificar Recife RECIFE e derivados. De novo, ver se vale usar lower
OK Regra 7: "Sua senha deve conter o dia da entrega em algarismos romanos"; //resposta: XIX
OK Regra 8: "Sua senha deve conter o nome da melhor materia de CC"; //resposta: PIF ou pif
OK Regra 9: "A soma dos algarismos da sua senha deve ser igual a 25"; 
OK Regra 10: "Sua senha deve conter a senha da wifi do CESAR"; //bemvindoaocesar
OK Regra 11: "Sua senha deve conter um pais que comeca com 'M'"; //lista abaixo:
//Lista de países com M: México, Moçambique, Malásia, Marrocos, Madagascar, Maldivas, 
//Mianmar, Moldávia, Mauritânia, Micronésia, Montenegro, Malta, Mônaco, Mongólia
OK Regra 12: "Ops! Sua senha deve ter, no maximo, 50 caracteres"; //if len(senha) < 50 aí dá o OK
