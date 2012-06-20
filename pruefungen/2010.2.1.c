#include <math.h>
#include <stdio.h>

double diffeq_y(double x, double y, double z) {
	return x*x * sin(y) + exp(x) * cos(z);
}

double diffeq_z(double x, double y, double z) {
	return 2 * x * y + exp(z);
}

int diff_runge_kutta(double (*diffeq_y)(double x, double y, double z), double (*diffeq_z)(double x, double y, double z), double y0, double z0, double start, double end, double stepsize) {
	
	double x, y, z, k1, k2, l1, l2;
	
	// set the start and the value at the start
	x = start;
	y = y0;
	z = z0;
	
	// the index needed for the loop and the amount of steps
	int i, steps;
	
	// the amount of steps we'll calculate
	steps = ceil(fabs(end - start) / stepsize);
	
	for (i = 0; i < steps; i++) {
		
		k1 = stepsize * diffeq_y(x, y, z);
		l1 = stepsize * diffeq_z(x, y, z);
		
		k2 = stepsize * diffeq_y(x + stepsize/2, y + k1/2, z + l1/2);
		l2 = stepsize * diffeq_z(x + stepsize/2, y + k1/2, z + l1/2);
		
		y += k2;
		z += l2;
		
		x += stepsize;
		
		// TODO
		// - the values should be stored in a file or in an array for later evaluation
		printf("y(%-3g) = %g \t z(%-3g) = %g\n", x, y, x, z);
	}
	
	return 1;
}

int main() {
	
	int result;
	
	double y0 = 1;
	double z0 = -1;
	
	double start = 0;
	double end = 1;
	
	result = diff_runge_kutta(&diffeq_y, &diffeq_z, y0, z0, start, end, 0.1);
	
	return 0;
}