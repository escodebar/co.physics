#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double diffeq_y(double x, double y, double z) {
	return x*x * sin(y) + exp(x) * cos(z);
}

double diffeq_z(double x, double y, double z) {
	return 2 * x * y + exp(z);
}

int diff_runge_kutta(double (*dy)(double x, double y, double z), double (*dz)(double x, double y, double z), double y0, double z0, double start, double end, double precision) {
	
	double x, y, z, k1, k2, l1, l2;
	
	// we'll have to store the values somewhere
	// we just need two arrays for this because only the actual values
	// and the values of the last series are compared
	double *ys[] = { NULL, NULL }, *zs[] = { NULL, NULL };
	
	// the integer for the loop and the step
	int i, steps = 1;
	
	// we only have to store two series of values, so we need an int
	// ooz stands for "one or zero"
	// ooz is 0 if log2(steps) is an even number
	// ooz is 1 if log2(steps) is an odd number
	// the condition integer is needed for the while loop
	int ooz, condition;
	
	// calculate the stepsize
	double stepsize = fabs(end - start);
	
	// let's set the values of y and z to something meaningless
	y = 0;
	z = 0;
	
	do {
		// calculate if we have to store the values in the 0th or the 1st array
		ooz = (int)log2(steps) % 2;
		
		// reset the start and the values at the start
		x = start;
		y = y0;
		z = z0;
		
		// let's free the memory allocated before (if any)
		if (ys[ooz] != NULL) {
			free(ys[ooz]);
		}
		if (zs[ooz] != NULL) {
			free(zs[ooz]);
		}
		
		// now that we know the amount of steps, we can allocate the memory for our values
		ys[ooz] = (double*)calloc(steps + 1, sizeof(double));
		zs[ooz] = (double*)calloc(steps + 1, sizeof(double));
		
		// we have to store the starting values
		ys[ooz][0] = y0;
		zs[ooz][0] = z0;
		
		// implementation of runge kutta method
		for (i = 0; i < steps; i++) {
			
			// calculate k1 and l1, k2 and l2
			k1 = stepsize * dy(x, y, z);
			l1 = stepsize * dz(x, y, z);
		
			k2 = stepsize * dy(x + stepsize/2.0, y + k1/2.0, z + l1/2.0);
			l2 = stepsize * dz(x + stepsize/2.0, y + k1/2.0, z + l1/2.0);
		
			// calculate the new y and z
			y += k2;
			z += l2;
			
			// increase the x
			x += stepsize;
			
			// store the values
			ys[ooz][i+1] = y;
			zs[ooz][i+1] = z;
		}
		
		// if it's the first time the loop runs, we won't have to check the conditions
		// (because there will be no values to compare), instead we set the condition to "true"
		if (steps == 1) {

			// we have to set the condition to 1
			condition = 1;
			
		} else {
			
			// reset the condition
			condition = 0;

			// now let's check if the conditions are fulfilled
			for (i = 0; i < (steps / 2) + 1; i++) {
				condition = condition || (fabs(ys[ooz][2*i] - ys[(ooz + 1) % 2][i]) > precision);
				condition = condition || (fabs(zs[ooz][2*i] - zs[(ooz + 1) % 2][i]) > precision);
			}
		}
		
		// adapt stepsize and amount of steps
		stepsize /= 2;
		steps *= 2;
		
	} while (condition);
	
	// let's print out the result
	for (i = 0; i < steps + 1; i++) {
		
		// let's calculate the x
		x = i * stepsize + start;
		
		// print out the values
		printf("y(%-3g) = %g  z(%-3g) = %g\n", x, ys[ooz][i], x, zs[ooz][i]);
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