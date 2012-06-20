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
	int i, steps = 10;
	
	// calculate the stepsize
	double stepsize = fabs(end - start)/(double)steps;
	
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
		// actually, we don't need calloc here, we could just create an array of length 11
		// but we might want to improve the code and save more steps then we'd only have
		// to let the number "11" vary in dependence of the amount of steps
		
		ys = (double*)calloc(11, sizeof(double));
		zs = (double*)calloc(11, sizeof(double));
		
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
			
			// we only need to store the values for 0.0, 0.1, 0.2, etc.
			if (!((int)x*100 % 10)) {
				ys[(int)(x*10)+1] = y;
				zs[(int)(x*10)+1] = z;
			}
		}
		
		// adapt stepsize and amount of steps
		stepsize /= 2;
		steps *= 2;
		
		// printf("%g\n", stepsize);
		
	} while ((fabs(y - y_old) > precision) || (fabs(z - z_old) > precision));
	
	// let's print out the result
	for (i = 0; i < 11; i++) {
		// print out the values
		printf("y(%-3g) = %g  z(%-3g) = %g\n", i*0.1, ys[i], i*0.1, zs[i]);
	}
	
	// print out the stepsize
	printf("stepsize: %g", stepsize*2);
	
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
	
	return 0;
}