#include <math.h>
#include <stdio.h>

double diffeq(double x, double y) {
	return - x*x * y*y;
}

int diff_eq_euler(double (*fun)(double, double), double startval, double start, double end, double stepsize) {
	
	double x, y;
	
	// set the start and the value at the start
	x = start;
	y = startval;
	
	// the index needed for the loop and the amount of steps
	int i, steps;
	
	// the amount of steps we'll calculate
	steps = ceil(fabs(end - start) / stepsize);
	
	for (i = 0; i < steps; i++) {
		y += stepsize * fun(x, y);
		x += stepsize;
		// TODO
		// - the values should be stored in a file or in an array
		printf("x: %g, y: %g\n", x, y);
	}
	
	return 1;
}

int main() {
	
	int result;
	
	result = diff_eq_euler(&diffeq, 1, 0, 1, 0.01);
	
	return 0;
}