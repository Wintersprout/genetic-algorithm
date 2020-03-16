# genetic-algorithm
<h1>Genetic Algorithm Example</h1>

<p>This program uses <a href="https://en.wikipedia.org/wiki/Genetic_algorithm">genetic algorithm</a> to calculate the maximum value of <br>f(x) = 1 + x * sin(10 * pi * x) <br>when x is within the interval [-1, 2].</p>
<p>The population consists of unsigned integers of 4 bytes randomly generated, which are then transfered to the above interval through a <a href="https://en.wikipedia.org/wiki/Linear_map">linear map</a> function. After the mapping process, each individual receives a fitness level based on the <a href="https://en.wikipedia.org/wiki/Fitness_function">fitness function</a> above.</p>
<p>Individuals are chosen by a <a href="https://en.wikipedia.org/wiki/Fitness_proportionate_selection">roulette wheel selection</a> process to perform a crossover. The resulting child joins the population if fitter than the least fit individual.</p>

<p><a href="https://en.wikipedia.org/wiki/Mutation_(genetic_algorithm)">Mutation</a> occurs at every other iteraction, and it consists of a bit flip at a random position in one of the individuals.</p>
