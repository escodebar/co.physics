#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double fun(double x) {
	return 1/sqrt(2.0*M_PI) * exp(-x*x/2.0);
}

double trapezoidal_integration(double (*fun)(double), double precision, double start, double end);
double trapezoidal_integration(double (*fun)(double), double precision, double start, double end) {
	
	// the index for the for loop, the amount of steps
	int i, steps;
	
	// the stepwidth, the length of the interval, the series j
	double stepwidth, intervallength, j, deltaj;
	
	// the length of the interval is 
	intervallength = fabs(end - start);
	
	// let's start the series
	j = (fun(start) + fun(end))/2;
	
	// first we'll only calculate one step
	steps = 1;
	
	do {
		// increment the amount of steps for the next iteration
		steps *= 2;

		// the difference between j_i and j_(i+1)
		// we have to reset it to 0 and calculate it on every step
		deltaj = 0;
		
		// the stepwidth has to be recalculated if the amount of steps increase
		stepwidth = intervallength / steps;
		
		// now let's calculate the difference between J_i and J_(i+1)
		// you'll have to believe this formula, or calculate it yourself:
		// start with J_0 = 1/2(f(start) + f(end))
		// then calculate J_1 = J_0 + (the value of the function in the middle of the interval)
		// ...
		// so deltaJ = the sum of the values of the function between the points already calculated
		for (i = 1; i < steps; i+=2) {
			// printf("step %i/%i: %g\n", i, steps, fun(start + stepwidth*i));
			deltaj += fun(start + stepwidth*i);
		}
		
		// add the difference between J_i and J_(i+1) to our total J
		j+= deltaj;
	
	// we do this calculation until the needed precision is reached
	// for more information visit:
	// http://www.physik.unibe.ch/unibe/philnat/fachbphysik/content/e4897/e4910/e4913/e5244/e8465/files60510/Lec10_01_05_12_ger.pdf
	} while (fabs(2 * deltaj / j - 1) > precision);
	
	// finally calculate the value of the integral
	return intervallength/steps * j;
}

int main() {
	
	double result;
	
	int i;
	for (i = 1; i <= 5; i++) {
		result = trapezoidal_integration(&fun, 10e-7, -i, i);
		printf("%1.8g\n", result);		
	}
	
	return 1;
}