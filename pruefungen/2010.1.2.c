#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int over_parabola(double x, double y) {
	return y >= 2.5 * x * x - 0.9 * x + 0.4;
}

int in_circle(double x, double y, double r) {
	return pow((y-0.5),2) + pow((x-0.5),2) <= r*r;
}

int in_area(double x, double y, double r) {
	return over_parabola(x, y) && in_circle(x, y, r);
}

double monte_carlo(int (*f)(double x, double y, double r), double x_start, double x_end, double y_start, double y_end, unsigned int steps, double r) {
	
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
		if (f(x, y, r)) {
			counter++;
		}
	}
	
	// calculate the area of the given interval
	area = (x_end - x_start) * (y_end - y_start);
		
	return area * (double)counter / (double)steps;
}

int main() {
	
	// r is the radius, result is the result of the integration
	double r, result;
	// r_min is the minimal radius, r_max the maximal radius
	double r_min = 0.1, r_max = 0.4;
		
	do {
		// calculate the new r
		r = (r_min + r_max) / (double)2;
				
		// calculate the new surface
		result = monte_carlo(&in_area, 0, 1, 0, 1, 1e6, r);
		
		// If the result is negative, then our radius is the new minimal radius
		if (result - 0.1 < 0) {
			r_min = r;
		} else {
			r_max = r;
		}
		
	} while (fabs(result - 0.1) > 0.001);
	
	printf("The found radius is: %g\n", r);
	printf("The area is: %g +/- %g", result, sqrt(result / 1e6));
	
	return 0;
}