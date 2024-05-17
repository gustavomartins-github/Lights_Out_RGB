#include <stdio.h>
#include <stdlib.h>

/*

	~ mapa do jogo (max 40 por 40) ~

	Obs.: uma matrix é um vetor cujo cada elemento é um outro vetor

	Obs.: cada elemento da matriz principal (linha horizontal da matriz) receberá uma string (linha de entrada)

*/ 
char map[40][40];

// função principal para modelagem do problema (arquivo problema + domínio)
int main(void){

	// ------------------------------------------------- Montando o Mapa do Jogo ------------------------------------------------

	/*

		~ Criando uma variável auxiliar ~

		Obs.: essa variável será responsável por posicionar as linhas da matriz.
		obs.: começa da linha 0 e vai até a linha N, conforme o número de linhas a serem forneceidas pela entrada padrão.

	*/
	int aux = 0;
	
	/*

		~ Montando o mapa ~

		Obs.: "enquanto tiver linhas (strings) para ler, armazene-as, incrementando de 1 em 1,  na posição 0 até N"
		Obs.: linha 1 da matriz = linha 1 da entrada de dados, e assim por diante

	*/
	while (scanf(" %s", map[aux++]) == 1 && aux < 4);

	/*

		~ Criando os arquivos de "problema" e "domínio" no modo escrita ~
		
		--> Arquivo de Problema: responsável pelos aspectos “globais" do problema (mudam de acordo com a situação específicada)
			- Define os objetos existentes
			- Define o que é verdade sobre os objetos
			- Define o(s) objetivo(s) final(is)

		--> Arquivo de Domínio: responsável pelos aspectos "universais" do problema (não mudam independentemente da situação específicada)
			- Define os tipos de objetos que podem existir no modelo
			- Define os tipos de predicados que podem existir no modelo
			- Define os tipos de ações que podem existir no modelo

		Obs.: a função fopen(file_name, "w") cria ou lê um arquivo texto de nome file_name no modo de escrita.

	*/
	FILE *problem = fopen("problem.pddl", "w");
	FILE *domain = fopen("domain.pddl", "w");

	// --------------------------------------------- Montando o Arquivo de Problema ---------------------------------------------

	// escrevendo o cabeçalho para receber os objetos ~
	fprintf(problem, "(define (problem luz)\n\t(:domain lightsout)\n\t(:objects\n\t\t");

	// Calculando sentinela (usada para saber a dimensão da nova matriz)
	int size = 0;
	for (int i = 0; i < aux; i++)
		for (int j = 0; map[i][j] != '\0'; j++)
			size = j;
	size = (size+1)/2;
	
	// Escrevendo os objetos (Células, Tipos e Cores, respectivamente)
	for (int i = 0; i < aux; i++)
		for (int j = 0; j < size; j++)
			fprintf(problem, "%dx%d ", i, j);
	fprintf(problem, "- cell\n\t\t- * _ | # - type\n\t\tW R G B - color\n\t)\n\t(:init");

	// Escrevendo a cor de cada botão (considere W como Desligado)
	for (int i = 0; i < aux; i++)
		for (int j = 0; map[i][j] != '\0'; j++)
			if (map[i][j] == 'R' ||  map[i][j] == 'G' ||  map[i][j] == 'B' || map[i][j] == 'W')
				fprintf(problem, "\n\t\t(cor %c %dx%d)", map[i][j], i, j/2);

	// Escrevendo o tipo de cada botão
	for (int i = 0; i < aux; i++)
		for (int j = 0; map[i][j] != '\0'; j++)
			if (map[i][j] == 'R' ||  map[i][j] == 'G' ||  map[i][j] == 'B' || map[i][j] == 'W')
				fprintf(problem, "\n\t\t(tipo %c %dx%d)", map[i][j-1], i, j/2);

    // Escrevendo as adjacências de cada botão
	for (int i = 0; i < aux; i++)
		for (int j = 0; j < size; j++)
			if (i == aux - 1)
				fprintf(problem, "\n\t\t(adj %dx%d %dx%d)", i, j, i, j+1);
			else
				fprintf(problem, "\n\t\t(adj %dx%d %dx%d)\n\t\t(adj %dx%d %dx%d)", i, j, i, j+1, i, j, i+1, j );
				

	// Escrevendo o objetivo final: todas as células desligadas (cor = W)
	fprintf(problem, "\n\t)\n\t(:goal\n\t\t(and");
	for (int i = 0; i < aux; i++)
		for (int j = 0; j < size; j++)
			fprintf(problem, "\n\t\t\t(cor W %dx%d)", i, j);
	fprintf(problem, "\n\t\t)\n\t)\n)\n");

	// --------------------------------------------- Montando o Arquivo de Domínio ---------------------------------------------
	
	fprintf(domain, "(define (domain lightsout)\n"
					"	(:types cell)\n"
					"	(:predicates\n"
					"		(on ?c - cell)\n"
					"		(adj ?c0 ?c1 - cell))\n"
					"	(:action CLICK\n"
					"		:parameters (?c - cell)\n"
					"		:precondition (and)\n"
					"		:effect (and\n"
					"			(when (on ?c) (not (on ?c)))\n"
					"			(when (not (on ?c)) (on ?c))\n"
					"			(forall (?w - cell)\n"
					"				(when (or (adj ?c ?w) (adj ?w ?c))\n"
					"					(and (when (on ?w) (not (on ?w)))\n"
					"					(when (not (on ?w)) (on ?w))))))))");
	fclose(domain), fclose(problem);
	return 0;
}