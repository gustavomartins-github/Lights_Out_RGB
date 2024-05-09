#include <stdio.h>
#include <stdlib.h>

char matrix[40][40];
int main(void) {
	int p = 0;
	while (scanf(" %s", matrix[p++]) == 1);
	FILE *problem = fopen("problem.pddl", "w"), *domain = fopen("domain.pddl", "w");
	fprintf(problem, "(define (problem luz)\n\t(:domain lightsout)\n\t(:objects");
	for (int i = 0; i < p; i++)
		for (int ii = 0; matrix[i][ii] != '\0'; ii++)
			fprintf(problem, " c%d-%d", i, ii);
	fprintf(problem, " - cell)\n\t(:init\n");	
	for (int i = 0; i < p; i++)
		for (int ii = 0; matrix[i][ii] != '\0'; ii++)
			if (matrix[i][ii] == 'L') fprintf(problem, "\t\t(on c%d-%d)\n", i, ii);
	for (int i = 0; i < p; i++)
		for (int ii = 0; matrix[i][ii] != '\0'; ii++) {
			if (matrix[i][ii+1] != 0) fprintf(problem, "\t\t(adj c%d-%d c%d-%d)\n", i, ii, i, ii+1);
			if (matrix[i+1][ii] != 0) fprintf(problem, "\t\t(adj c%d-%d c%d-%d)\n", i, ii, i+1, ii);
		}
	fprintf(problem, "\t)\n\t(:goal (and");
	for (int i = 0; i < p; i++)
		for (int ii = 0; matrix[i][ii] != '\0'; ii++)
			fprintf(problem, " (not (on c%d-%d))", i, ii);
	fprintf(problem, ")))\n");
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
	system("/home/software/planners/madagascar/M -Q domain.pddl problem.pddl");
	return 0;
}
