#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int over_parabola(double x, double y) {
	return y >= 2.5 * x * x - 0.9 * x + 0.4;
}

int in_circle(double x, double y) {
	return pow((y-0.5),2) <= 0.01 - pow((x-0.5),2);
}

int in_area(double x, double y) {
	return over_parabola(x, y) && in_circle(x, y);
}

double monte_carlo(int (*f)(double x, double y), double x_start, double x_end, double y_start, double y_end, unsigned int steps) {
	
	// the counter, the number of steps and the index i
	unsigned int counter, i;
	
	// our variables x and y and the area for the given limits
	double x, y, area;
	
	// set the seed for the random number generator
	srand(time(NULL));
	
	// set the counter to 0
	counter = 0;
	
	// set the amount of steps, set the counter and LOOP!
	for (i = 0; i < steps; i++) {
		
		// stretch it, bulge it and shift it
		x = ((x_end - x_start) * (double) rand() / (double) RAND_MAX) + x_start;
		y = ((y_end - y_start) * (double) rand() / (double) RAND_MAX) + y_start;
		
		// check if the point is inside the area and increase the counter
		if (f(x, y)) {
			counter++;
		}
	}
	
	// calculate the area of the given interval
	area = (x_end - x_start) * (y_end - y_start);
		
	return area * (double)counter / (double)steps;
}

int main() {
	
	double result;
	
	result = monte_carlo(&in_area, 0, 1, 0, 1, 1e6);
	
	printf("The area is: %g +/- %g", result, sqrt(result / 1e6));
	
	return 0;
}