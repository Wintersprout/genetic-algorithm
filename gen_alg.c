/*Genetic Algorithm Example
  Filename: gen_alg.c
  Author: Reno Facundo
  Date: 2020/3
  */

#include "gen_alg.h"

int main(void) {
	
	individual* population = NULL;
	unsigned int pop_size = 10;
	
	//Memory allocation for the population. It could also be done directly. 
	population = malloc(sizeof(individual) * pop_size);
	if (!population) {
		printf("Not enough memory!");
		return EXIT_FAILURE;
	}

	//Initialize the Population.
	init(population, pop_size);
	//Calculate the Probability of Selection of its individuals.
	probability_calc(population, pop_size);
	//It is easier to pick the least fit individual on a sorted array.
	bubble_sort(population, pop_size);

	printf("Individual	f(x)		x\n");
	for (unsigned int i = 0; i < pop_size; i++) {
		printf("%u		%f	%f\n", population[i].id, population[i].fitness, linear_mapping(population[i].id));
	}

	//Start Crossovers and Mutations
	for (unsigned int i = 1000; i > 0; i--) {

		//Crossover
		unsigned int father = roulette_wheel(population, pop_size);
		unsigned int mother = roulette_wheel(population, pop_size);
		unsigned int child = crossover(population[father].id, population[mother].id);
		float child_fitness = objective_function(linear_mapping(child));

		if (child_fitness > population[0].fitness) {
			population[0].id = child;
			population[0].fitness = child_fitness;
			//sort population
			bubble_sort(population, pop_size);
			//recalculates the Probability of Selection;
			probability_calc(population, pop_size);
		}

		//Mutation 
		if (i % 2) {
			unsigned int mutant = mutation(population[rand() % pop_size].id);
			float mutant_fitness = objective_function(linear_mapping(mutant));
			if (mutant_fitness > population[0].fitness) {
				population[0].id = mutant;
				population[0].fitness = mutant_fitness;
				//sort population
				bubble_sort(population, pop_size);
				//recalculates the Probability of Selection;
				probability_calc(population, pop_size);
			}
		}

	}
	printf("Individual	f(x)		x\n");
	for (unsigned int i = 0; i < pop_size; i++) {
		printf("%u		%f	%f\n", population[i].id, population[i].fitness, linear_mapping(population[i].id));
	}
	return EXIT_SUCCESS;
}