#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double diffeq_y(double x, double y, double z) {
	return x*x * sin(y) + exp(x) * cos(z);
}

double diffeq_z(double x, double y, double z) {
	return 2 * x * y + exp(z);
}

int diff_runge_kutta(double (*diffeq_y)(double x, double y, double z), double (*diffeq_z)(double x, double y, double z), double y0, double z0, double start, double end, double precision) {
	
	double x, y, z, k1, k2, l1, l2;
	
	// we'll have to store the values somewhere
	double *ys = NULL, *zs = NULL;
	
	// we have to store the last values somewhere
	double y_old, z_old;
	
	// the integer for the loop and the step
	int i, steps = 1;
	
	// calculate the stepsize
	double stepsize = fabs(end - start);
	
	// let's set the values of y and z to something meaningless
	y = 0;
	z = 0;
	
	do {
		// store the last values of y and z
		y_old = y;
		z_old = z;
		
		// reset the start and the values at the start
		x = start;
		y = y0;
		z = z0;
		
		// let's free the memory allocated before (if any)
		if (ys != NULL) {
			free(ys);
		}
		if (zs != NULL) {
			free(zs);
		}
		
		// now that we know the amount of steps, we can allocate the memory for our values
		ys = (double*)calloc(steps + 1, sizeof(double));
		zs = (double*)calloc(steps + 1, sizeof(double));
		
		// we have to store the starting values
		ys[0] = y0;
		zs[0] = z0;
		
		// implementation of runge kutta method
		for (i = 0; i < steps; i++) {
			
			// calculate k1 and l1, k2 and l2
			k1 = stepsize * diffeq_y(x, y, z);
			l1 = stepsize * diffeq_z(x, y, z);
		
			k2 = stepsize * diffeq_y(x + stepsize/2.0, y + k1/2.0, z + l1/2.0);
			l2 = stepsize * diffeq_z(x + stepsize/2.0, y + k1/2.0, z + l1/2.0);
		
			// calculate the new y and z
			y += k2;
			z += l2;
			
			// increase the x
			x += stepsize;
			
			// store the values
			ys[i+1] = y;
			zs[i+1] = z;
		}
		
		// adapt stepsize and amount of steps
		stepsize /= 2;
		steps *= 2;
		
		// printf("%g\n", stepsize);
		
	} while ((fabs(y - y_old) > precision) || (fabs(z - z_old) > precision));
	
	// let's print out the result
	for (i = 0; i < steps + 1; i++) {
		
		// let's calculate the x
		x = i * stepsize + start;
		
		// print out the values
		printf("y(%-1.5g) = %g  z(%-3g) = %g\n", x, ys[i], x, zs[i]);
	}
	
	return 1;
}

int main() {
	
	int result;
	
	double y0 = 1;
	double z0 = -1;
	
	double start = 0;
	double end = 1;
	
	double precision = 1e-4;
	
	result = diff_runge_kutta(&diffeq_y, &diffeq_z, y0, z0, start, end, precision);
	
	return 1;
}