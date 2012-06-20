#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double fun(double x) {
	return exp(- x * x / (double) 2) / sqrt((double) 2 * M_PI);
}

double monte_carlo(double (*f)(double), double start, double end, int steps) {
	
	// the counter, the number of steps and the index i
	int i;
	
	// our random x
	double x, sum;
	
	// set the seed for the random number generator
	srand(time(NULL));
		
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
	int steps = 1e6;
	
	result = monte_carlo(&fun, -1, 1, steps);
	
	printf("Value of the integral: %g\n", result);
	printf("The error of the integral is: %g\n", fabs(0.68268949 - result));
	printf("The theoretical error is: %g\n", (double) 8 / sqrt(steps - 1));
	
	return 1;
}