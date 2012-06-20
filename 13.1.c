#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double fun(double x) {
	return exp(- x * x / (double) 2) / sqrt((double) 2 * M_PI);
}

double monte_carlo(double (*f)(double), double variance, double start, double end, double precision) {
	
	// the counter, the number of steps and the index i
	long int steps, i;
	
	// our random x
	double x, sum;
	
	// set the seed for the random number generator
	srand(time(NULL));
	
	// calculate the amount of steps
	steps = (long int) (variance/(precision * precision) + 1);
	
	printf("number of steps: %li", steps);
	
	// set the amount of steps and the sum, set the counter and LOOP!
	for (i = 0, sum = 0; i < steps; i++) {
		
		// stretch it, bulge it and shift it
		x = ((end - start) * (double) rand() / (double) RAND_MAX) + start;
		
		// add the result of the function to the series
		sum += f(x);
	}
	
	return (end - start) * sum / (double) steps;
}

int main() {
	
	double result;
	
	result = monte_carlo(&fun, 8, -1, 1, 1e-6);
	
	printf("Value of the integral: %g\n", result);
	
	return 1;
}