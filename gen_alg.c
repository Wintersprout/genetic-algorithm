/*Genetic Algorithm Example
  Filename: gen_alg.c
  Author: Reno Facundo
  Date: 2020/3
  */

#include "gen_alg.h"

int main(void) {
	
	individual* population = NULL;
	unsigned int pop_size =	 200;
	int generations =		 800;
	int crossovers =		 10;
	int offspring =			 0;
	int mutants =			 0;
	
	//Memory allocation for the population. It could also be done directly. 
	population = malloc(sizeof(individual) * pop_size);
	if (!population) {
		puts("Not enough memory!");
		return EXIT_FAILURE;
	}
	puts("Initializing population ...");
	init(population, pop_size);
	//Calculate the Probability of Selection of its individuals.
	probability_calc(population, pop_size);
	//It is easier to pick the least fit individual on a sorted array.
	bubble_sort(population, pop_size);

	puts("\nInitial Population:");
	printf("\tSize:           %d\n", pop_size);
	printf("\tFittest: f(x) = %.4f, x = %.4f\n", population[pop_size - 1].fitness, linear_mapping(population[pop_size - 1].id));
	printf("\tMean:           %.4f\n", mean(population, pop_size));
	printf("\tVariance:       %.4f\n", variance(population, pop_size));
	printf("\tStandard Dev:   %.4f\n", sqrt(variance(population, pop_size)));
	puts("Press ENTER to continue.");
	getchar();

	puts("\nStarting crossovers ...");
	//Start Crossovers and Mutations
	for (unsigned int i = generations; i > 0; i--) {
		
		for (int j = 0; j < crossovers; j++) {
			//Crossover
			unsigned int father = tournament(population, pop_size, 10);
			unsigned int mother = tournament(population, pop_size, 10);
			unsigned int child = crossover(population[father].id, population[mother].id);
			float child_fitness = objective_function(linear_mapping(child));

			//Natural Selection
			if (child_fitness > population[0].fitness) {
				population[0].id = child;
				population[0].fitness = child_fitness;
				offspring++;
				//sort population
				bubble_sort(population, pop_size);
				//recalculates the Probability of Selection;
				probability_calc(population, pop_size);
			}
		}
		//Mutation 
		if (i % 2) {
			unsigned int mutant = mutation(population[rand() % pop_size].id);
			float mutant_fitness = objective_function(linear_mapping(mutant));
			if (mutant_fitness > population[0].fitness) {
				population[0].id = mutant;
				population[0].fitness = mutant_fitness;
				mutants++;
			}
		}
		//sort population
		bubble_sort(population, pop_size);
		//recalculates the Probability of Selection;
		probability_calc(population, pop_size);

		printf("\rGeneration %d, Fittest: %.4f", generations - i + 1, population[pop_size - 1].fitness);
		printf(", total of %d new offspring and %d mutants.", offspring, mutants);
	}
	puts("\nEvolved Population:");
	printf("\tFittest: f(x) = %.4f, x = %.4f\n", population[pop_size - 1].fitness, linear_mapping(population[pop_size - 1].id));
	printf("\tMean:           %.4f\n", mean(population, pop_size));
	printf("\tVariance:       %.4f\n", variance(population, pop_size));
	printf("\tStandard Dev:   %.4f\n", sqrt(variance(population, pop_size)));
	
	return EXIT_SUCCESS;
}