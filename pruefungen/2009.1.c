#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double function(double x) {
	return log(1 + x*x) * sqrt(cos(x));
}

double simpson_3_8_integration(double (*fun)(double), double precision, double start, double end) {
	
	// the index for the for loop, the amount of steps
	int i, steps;

	// the stepwidth, the length of the interval, the value of the integral, the value of the old integral
	double stepwidth, intervallength, j0, j, j_old, stepwidth_old;

	// the length of the interval is 
	intervallength = fabs(end - start);

	// the start and the end value of the integral
	j0 = fun(start) + fun(end);
	j = j0;
	stepwidth = intervallength / (double) steps;

	// first we'll only calculate one step
	steps = 1;

	do {
		// we need to store the old value of the integral
		j_old = j;
		stepwidth_old = stepwidth;

		// and reset the value of the integral
		j = j0;

		// increment the amount of steps for the next iteration
		steps *= 3;

		// let's calculate the stepwidth
		stepwidth = intervallength / (double) steps;

		// now let's calculate the value of the integral for the given amount of steps
		// we use the formula f_0 + 3f_1 + 3f_2 + f_3 + ... + 3f_(3k-2) + 3f_(3k-1) + f_(3k)
		// for more information visit:
		// http://www.physik.unibe.ch/unibe/philnat/fachbphysik/content/e4897/e4910/e4913/e5244/e7137/files7138/Exam2009_ger.pdf
		// we could actually calculate again a delta_j instead of the whole j
		for (i = 1; i < steps; i++) {
			j += (double) (1 + 2 * (i % 3 != 0)) * fun(start + i * stepwidth);
		}
		
	} while (fabs((double) 3 / (double) 8 * (j_old * stepwidth_old - j * stepwidth)) > precision);	

	// finally calculate the value of the integral
	return stepwidth / (double) 3 * j;
}
	
int main ()
{
	double result;
	
	result = simpson_3_8_integration(&function, 1e-2, -1, 1);
	
	printf("The result of the integral is: %g\n", result);
	
	return 0;
}