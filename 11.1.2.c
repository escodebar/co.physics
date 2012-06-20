#include <math.h>
#include <stdio.h>

double diffeq(double x, double y) {
	return - x*x * y*y;
}

int diff_runge_kutta(double (*fun)(double, double), double startval, double start, double end, double stepsize) {
	
	double x, y, k1, k2;
	
	// set the start and the value at the start
	x = start;
	y = startval;
	
	// the index needed for the loop and the amount of steps
	int i, steps;
	
	// the amount of steps we'll calculate
	steps = ceil(fabs(end - start) / stepsize);
	
	for (i = 0; i < steps; i++) {
		
		k1 = stepsize * fun(x, y);
		k2 = stepsize * fun(x + stepsize/2, y + k1/2);
		
		y += k2;
		x += stepsize;
		
		// TODO
		// - the values should be stored in a file or in an array
		printf("x: %g, y: %g\n", x, y);
	}
	
	return 1;
}

int main() {
	
	int result;
	
	result = diff_runge_kutta(&diffeq, 1, 0, 1, 0.01);
	
	return 0;
}