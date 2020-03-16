# genetic-algorithm
<h1>Genetic Algorithm Example</h1>

<p>This program uses <a href="https://en.wikipedia.org/wiki/Genetic_algorithm">genetic algorithm</a> to calculate the maximum value of <br>f(x) = 1 + x * sin(10 * pi * x) <br>when 'x' is within the interval [-1, 2].</p>
<p>The population of candidate solutions consists of 4-byte unsigned integers of randomly generated. Their genotype is represented by a string of 0's and 1's. These candidate solutions, or individuals, are transfered to the above interval through a <a href="https://en.wikipedia.org/wiki/Linear_map">linear map</a> function. After the mapping process, each individual receives a fitness level based on the <a href="https://en.wikipedia.org/wiki/Fitness_function">fitness function</a> above.</p>
<p>Individuals are chosen by a <a href="https://en.wikipedia.org/wiki/Fitness_proportionate_selection">roulette wheel selection</a> process to perform a crossover at a crossover point in their genotype. The resulting child joins the population if fitter than the least fit individual.</p>

<p><a href="https://en.wikipedia.org/wiki/Mutation_(genetic_algorithm)">Mutation</a> occurs at every other iteraction, and it consists of a bit flip at a random position in one of the individuals. As with the crossover, the mutant will join the population if fitter than the least fit individual.</p>

<h2>Characteristics of the problem</h2>
<p>Since the solution is not known in advance, there is a risk of not reaching the correct answer if the number of iteractions is not big enough. The solution can also converge to a local maximum; stopping the program when there is convergence might lead to an incorrect solution.</p>
<p>There are three factors that have influence on the final result:</p>
<ul>
  <li>Genotype lenght: can vary from 8 to 32 characters, each one representing one bit. 16 bits presented itself to be an appropriated size.</li>
  <li>Population size: A large population brings genotype variety to the problem, but makes the roulette wheel selection ineffective (since all of its individuals would have similar probabilities of being chosen). A small population converges quickly, and the chance of new offspring would heavily depend on mutation.</li>
  <li>Number of iteractions: The larger the better, especially considering smaller populations.</li>
</ul>

<h2>Points for Improvement</h2>
<ul>
  <li>A different method of selection (instead of the roulette wheel) might bring better results for larger populations.</li>
  <li>There is only one new offspring at each iteration. Adding two or more children might increase the speed of which the answer is found.</li>
  <li>Mutation only happens at every other iteration. Forcing new mutations when there is convergence might increase the chances of leaving a local maximum.</li>
</ul>

<h2>About the Program / Acknowledgements</h2>
<p>The program was originally written in November 2004 as a grading project of Applied Computational Inteligence at Federal University of Ceara, Brazil. I took it out from the drawer and rewrote it in March 2020, with improved readability and computing efficiency.</p>
<p>The program is coded in C. It was compiled with Microsoft Visual Studio 2019, Community Version.</p>
<p> Special thanks to my wife, for looking after my 7-month old son while I was taking the rust out of my coding skills; and to Professor Almeida of Electrical Engineering Department, for giving me this assigment back in 2004.</p>
