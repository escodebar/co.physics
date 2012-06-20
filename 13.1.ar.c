#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fun(double x, double y) {
	return y <= exp(-x*x/(double)2) / sqrt((double)2 * M_PI);
}

double ar_monte_carlo(int (*f)(double, double), double variance, double x_start, double x_end, double y_start, double y_end, double precision) {
	
	// the counter, the number of steps and the index i
	unsigned int counter, steps, i;
	
	// our variables x and y and the area for the given limits
	double x, y, area;
	
	// set the seed for the random number generator
	srand(time(NULL));
	
	// set the counter to 0
	counter = 0;
	
	// calculate the amount of steps
	steps = (unsigned int)(variance/(precision * precision) + 1);
	
	// set the amount of steps, set the counter and LOOP!
	for (i = 0; i < steps; i++) {
		
		// stretch it, bulge it and shift it
		x = ((x_end - x_start) * (double) rand() / (double) RAND_MAX) + x_start;
		y = ((y_end - y_start) * (double) rand() / (double) RAND_MAX) + y_start;
		
		// check if the point is inside the area and increase the counter
		if (f(x,y)) {
			counter++;
		}
	}
	
	// calculate the area of the given interval
	area = (x_end - x_start) * (y_end - y_start);
		
	return area * (double)counter / (double)steps;
}

int main() {
	
	double result;
	
	result = ar_monte_carlo(&fun, 8, -1, 1, 0, 0.5, 1e-6);
	
	printf("Value of the integral: %g\n", result);
	
	return 0;
}