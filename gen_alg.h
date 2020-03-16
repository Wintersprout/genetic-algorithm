#pragma once

/*Genetic Algorithm Example
  Filename: gen_alg.h
  Author: Reno Facundo
  Date: 2020/3
  */

#include <string.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592654
#define PRECISION 16 //Maximum value must not be higher than the size of unsigned int in bits (4 bytes = 32 bits)
#define TRUE 1
#define FALSE 0

typedef struct {
    unsigned int id;    //Integer representing an individual of the population.
    float fitness;      //Output of the objective function.
    float probability;  //Probability of selection for crossover (relative to its population).
}individual;



//swap() swaps the values of its arguments.
void swap(float* a, float* b) {
    float aux;

    aux = *a;
    *a = *b;
    *b = aux;
}
//bubble_sort sorts an array of individuals of size 'size' in ascending order in respect to their fitness attribute.
void bubble_sort(individual* pop, unsigned int size) {
    unsigned int i = 0, j = 0, mark = size - 1;
    unsigned short swaped = TRUE;

    while (swaped)
    {
        swaped = FALSE;
        for (i = 0; i < mark; i++)
        {
            if (pop[i].fitness > pop[i + 1].fitness)
            {
                swap(&pop[i].fitness, &pop[i + 1].fitness);
                //Swaping the id directly, since swap function was implemented for float
                unsigned int temp = pop[i].id;
                pop[i].id = pop[i + 1].id;
                pop[i + 1].id = temp;

                swap(&pop[i].probability, &pop[i + 1].probability);
                j = i;
                swaped = TRUE;
            }
        }
        mark = j;
    }
}
//bin2dec() receives a string of 0's and 1's and converts it in to a positive decimal number.
unsigned int bin2dec(char* bin) {
    unsigned int i, dec = 0;

    for (i = 0; i < strlen(bin); i++)
        dec += (bin[i] - 48) * ((unsigned int)pow((unsigned int)2, (unsigned int)(strlen(bin) - 1 - i)));
    return dec;
}
//dec2bin() returns a string of 0's and 1's of lenght 'len' converted from a decimal 'val'.
char* dec2bin(unsigned int dec, unsigned int len) {
    char* bin = NULL;

    bin = (char*)malloc(sizeof(char) * (len + 1));
    if (!bin)
        return NULL;

    *(bin + len) = '\0';

    /*Generates the binary form*/
    do {
        *(bin + len - 1) = (dec % 2) + 48;
        dec = (dec) / 2;
        len--;
    } while (len > 0);

    return bin;
}
//linear_mapping() returns a value in the range of [-1, 2] mapped from a PRECISION bit number 'x' within [0, 2^PRECISION].
float linear_mapping(unsigned int x) {
    /*f(x) = B * x - C, where:
    B = ((max_x - min_x) / (max_f(x) - min_f(x)))
    C = f(0) */
    return -1 + ((2 + 1) * ((float)x)) / ((float)pow(2, PRECISION) - 1);
}
//objective_function() returns 1+x*sen(10*pi*x), which is the function used to determine the fitness of the population.
float objective_function(float x) {
    return 1 + x * (float)sin(10.0 * PI * x);
}
//init() generates 'size' amount of individuals.
void init(individual* pop, unsigned int size) {
    unsigned int i, j;

    srand((unsigned)time(NULL));

    for (i = 0; i < size; i++) {
        pop[i].id = 0;
        for (j = 0; j < PRECISION; j++) {
            pop[i].id += ((unsigned int)rand() % 2) * (unsigned int)pow(2, j);
        }

        pop[i].fitness = objective_function(linear_mapping(pop[i].id));
    }

}
//probability_calc() calculates the Probability of Selection of each individual.
void probability_calc(individual* pop, unsigned int size) {
    unsigned int i;
    float sum = 0;

    for (i = 0; i < size; i++) {
        pop[i].fitness += 100; //transfering current aptitude range to above zero values.
        sum += pop[i].fitness;
    }

    for (i = 0; i < size; i++) {
        pop[i].probability = (pop[i].fitness * (float)100.0) / sum;
        pop[i].fitness -= 100; //bringing back aptitude to its original value.
    }
}
//roulette_wheel() returns an index of an individual using Roulette Wheel Selection method.
unsigned int roulette_wheel(individual *pop, unsigned int size) {

    unsigned int i;
    float draw, wheel = 0;

    //Drawing a random float number in the [0, 100] range.
    draw = ((float)rand() / (float)RAND_MAX) * 100.0F;

    //Comparing the drawn number to each slice of probability wheel and returning its index when there is a match.
    for (i = 0; i < size; i++) {
        wheel += pop[i].probability;
        if (draw <= wheel) {
            return i;
        }
    }
    return i;
}
//crossover() returns one possible result of the Crossover between x and y.
unsigned int crossover(unsigned int x, unsigned int y)
{

    unsigned int i = 0, r;
    char aux, * bin1, * bin2;

    bin1 = dec2bin(x, PRECISION);
    bin2 = dec2bin(y, PRECISION);

    //Crossover point.
    r = rand() % PRECISION;

    while (i <= r) {
        aux = bin2[i];
        bin2[i] = bin1[i];
        bin1[i] = aux;
        i++;
    }

    return bin2dec(bin1);

}
//mutation() returns a flip bit mutation of its argument.
unsigned int mutation(unsigned int x)
{
    unsigned int aux;
    char* bin;

    bin = dec2bin(x, PRECISION);

    aux = rand() % PRECISION;

    switch (bin[aux]) {
    case '0': bin[aux] = '1'; break;
    case '1': bin[aux] = '0'; break;
    default: printf("Mutation failed.\n"); return x;
    }

    return bin2dec(bin);
}
