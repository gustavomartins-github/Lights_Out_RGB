#include <stdio.h>
#include <stdlib.h>

char matrix[40][40];
int main(void) {
    // lendo e armazenando a entrada (OK)
	int aux = 0;
	while (scanf(" %s", matrix[aux++]) == 1 and aux < 4);
    
    // criando os arquivos e o cabeçalho (OK)
	FILE *problem = fopen("problem.pddl", "w"), *domain = fopen("domain.pddl", "w");
	fprintf(problem, "(define (problem lightsout)\n\t(:domain lightsout_rgb)\n\t(:objects");
    
    // escrevendo os objetos (OK)
	for (int i = 0; i < aux; i++)
		for (int j = 1, k = 1; matrix[i][j] != '\0'; j=j+2, k++)
			fprintf(problem, " c%d%d", i, j-k);
	fprintf(problem, " - cell)\n\t(:init\n");

    //escreve a cor dos botões
	for (int i = 0; i < aux; i++)
		for (int j = 1, k = 1; matrix[i][j] != '\0'; j=j+2, k++)
			if (matrix[i][j] == 'W')
				fprintf(problem, "\t\t(W c%d%d)\n", i, j-k);
			else if (matrix[i][j] == 'R')
				fprintf(problem, "\t\t(R c%d%d)\n", i, j-k);
			else if (matrix[i][j] == 'G')
				fprintf(problem, "\t\t(G c%d%d)\n", i, j-k); 
			else if (matrix[i][j] == 'B')
				fprintf(problem, "\t\t(B c%d%d)\n", i, j-k);  
			else;
	
	//escreve o tipo dos botões
	for (int i = 0; i < aux; i++)
		for (int j = 1, k = 1; matrix[i][j] != '\0'; j=j+2, k++)
			if (matrix[i][j-1] == '-')
				fprintf(problem, "\t\t(tipo0 c%d%d)\n", i, j-k);
			else if (matrix[i][j-1] == '*')
				fprintf(problem, "\t\t(tipo1 c%d%d)\n", i, j-k);
			else if (matrix[i][j-1] == '_')
				fprintf(problem, "\t\t(tipo2 c%d%d)\n", i, j-k); 
			else if (matrix[i][j-1] == '|')
				fprintf(problem, "\t\t(tipo3 c%d%d)\n", i, j-k);
			else if (matrix[i][j-1] == '#')
				fprintf(problem, "\t\t(tipo4 c%d%d)\n", i, j-k);   
			else;

    /*
	//escreve as adjacências
	for (int i = 0; i < aux; i++)
		for (int j = 1, k = 1; matrix[i][j] != '\0'; j=j+2, k++) {
			if (matrix[i][j+2] != 0) 
				fprintf(problem, "\t\t(adj c%d%d c%d%d)\n", i, j-k, i, j-k+1);
			if (matrix[i+1][j] != 0) 
				fprintf(problem, "\t\t(adj c%d%d c%d%d)\n", i, j-k, i+1, j-k);
		}
	*/ 
    
	//escreve as celulas de mesma linha
	for (int i = 0; i < aux; i++)
		for (int j = 1, k = 1; matrix[i][j] != '\0'; j=j+2, k++) 
			if (matrix[i][j+2] != 0) 
				fprintf(problem, "\t\t(same_row c%d%d c%d%d)\n", i, j-k, i, j-k+1);

	//escreve as celulas de mesma coluna
	for (int i = 0; i < aux; i++)
		for (int j = 1, k = 1; matrix[i][j] != '\0'; j=j+2, k++) {
			if (matrix[i+1][j] != 0) 
				fprintf(problem, "\t\t(same_col c%d%d c%d%d)\n", i, j-k, i+1, j-k);
		}

    // escreve o objetivo
	fprintf(problem, "\t)\n\t(:goal (and");
	for (int i = 0; i < aux; i++)
		for (int j = 1, k = 1; matrix[i][j] != '\0'; j=j+2, k++)
			fprintf(problem, " (W c%d%d)", i, j-k);
	fprintf(problem, ")))\n");

    // escreve o arquivo de domínio
	fprintf(domain, 
	"(define (domain lightsout_rgb)\n"
    "(:types cell)\n"
    "(:predicates\n"
    "	(W ?c - cell)\n"
    "	(R ?c - cell)\n"
    "	(G ?c - cell)\n"
    "	(B ?c - cell)\n"
    "	(tipo0 ?c - cell)\n"
    "	(tipo1 ?c - cell)\n"
    "	(tipo2 ?c - cell)\n"
    "	(tipo3 ?c - cell)\n"
    "	(tipo4 ?c - cell)\n"
    "	(same_row ?c1 ?c2 - cell)\n"
    "	(same_col ?c1 ?c2 - cell)\n"
    ")\n"
    "(:action click\n"
    "	:parameters (?c - cell)\n"
    "	:effect\n"
    "		(and\n"
    "			(when (and (not (tipo1 ?c)) (W ?c)) (and (not (W ?c)) (R ?c)))\n"
    "			(when (and (not (tipo1 ?c)) (R ?c)) (and (not (R ?c)) (G ?c)))\n"
    "			(when (and (not (tipo1 ?c)) (G ?c)) (and (not (G ?c)) (B ?c)))\n"
    "			(when (and (not (tipo1 ?c)) (B ?c)) (and (not (B ?c)) (W ?c)))\n"
    "			(forall (?a - cell)\n"
    "				(and\n"
    "					(when (same_row ?c ?a)\n" 
    "						(and\n"
    "							(when (and (tipo0 ?a) (W ?a)) (and (not (W ?a)) (R ?a)))\n"
    "							(when (and (tipo0 ?a) (R ?a)) (and (not (R ?a)) (G ?a)))\n"
    "							(when (and (tipo0 ?a) (G ?a)) (and (not (G ?a)) (B ?a)))\n"
    "							(when (and (tipo0 ?a) (B ?a)) (and (not (B ?a)) (W ?a)))\n"
    "							(when (and (tipo1 ?a) (W ?a)) (and (not (W ?a)) (R ?a)))\n"
    "							(when (and (tipo1 ?a) (R ?a)) (and (not (R ?a)) (G ?a)))\n"
    "							(when (and (tipo1 ?a) (G ?a)) (and (not (G ?a)) (B ?a)))\n"
    "							(when (and (tipo1 ?a) (B ?a)) (and (not (B ?a)) (W ?a)))\n"
    "							(when (and (tipo2 ?a) (W ?a)) (and (not (W ?a)) (R ?a)))\n"
    "							(when (and (tipo2 ?a) (R ?a)) (and (not (R ?a)) (G ?a)))\n"
    "							(when (and (tipo2 ?a) (G ?a)) (and (not (G ?a)) (B ?a)))\n"
    "							(when (and (tipo2 ?a) (B ?a)) (and (not (B ?a)) (W ?a)))\n"
    "						)\n"
    "					)\n"
    "					(when (same_col ?c ?a) \n"
    "						(and\n"
    "							(when (and (tipo0 ?a) (W ?a)) (and (not (W ?a)) (R ?a)))\n"
    "							(when (and (tipo0 ?a) (R ?a)) (and (not (R ?a)) (G ?a)))\n"
    "							(when (and (tipo0 ?a) (G ?a)) (and (not (G ?a)) (B ?a)))\n"
    "							(when (and (tipo0 ?a) (B ?a)) (and (not (B ?a)) (W ?a)))\n"
    "							(when (and (tipo1 ?a) (W ?a)) (and (not (W ?a)) (R ?a)))\n"
    "							(when (and (tipo1 ?a) (R ?a)) (and (not (R ?a)) (G ?a)))\n"
    "							(when (and (tipo1 ?a) (G ?a)) (and (not (G ?a)) (B ?a)))\n"
    "							(when (and (tipo1 ?a) (B ?a)) (and (not (B ?a)) (W ?a)))\n"
    "							(when (and (tipo3 ?a) (W ?a)) (and (not (W ?a)) (R ?a)))\n"
    "							(when (and (tipo3 ?a) (R ?a)) (and (not (R ?a)) (G ?a)))\n"
    "							(when (and (tipo3 ?a) (G ?a)) (and (not (G ?a)) (B ?a)))\n"
    "							(when (and (tipo3 ?a) (B ?a)) (and (not (B ?a)) (W ?a)))\n"
    "                        )\n"
    "                    )\n"
    "                )\n"
    "            )\n"
    "        )\n"  
    "	)\n"
	")\n"
	);

	// fecha os arquivos
	fclose(domain), fclose(problem);
	//system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl");
	return 0;
}
