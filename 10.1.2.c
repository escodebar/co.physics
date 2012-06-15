#include <math.h>
#include <stdio.h>

double fun(double x) {
	return 1/sqrt(2.0*M_PI) * exp(-x*x/2.0);
}

double simpsons_integration(double (*fun)(double), double precision, double start, double end);
double simpsons_integration(double (*fun)(double), double precision, double start, double end) {
	
	// the index for the for loop, the amount of steps
	int i, steps;
	
	// the stepwidth, the length of the interval, the value of the integral, the value of the old integral
	double stepwidth, intervallength, j0, j, j_old;
	
	// the length of the interval is 
	intervallength = fabs(end - start);
	
	// the start and the end value of the integral
	j0 = fun(start) + fun(end);
	j = j0;
	
	// first we'll only calculate one step
	steps = 1;
	
	do {
		// we need to store the old value of the integral
		j_old = j;
		
		// and reset the value of the integral
		j = j0;
		
		// increment the amount of steps for the next iteration
		steps *= 2;
		
		// let's calculate the stepwidth
		stepwidth = intervallength / steps;
		
		// now let's calculate the value of the integral for the given amount of steps
		// we use the formula f_0 + 4f_1 + 2f_2 + 4f_3 + ... + 2f_(2k-2) + 4f_(2k-1) + f_(2k)
		// for more information visit:
		// http://www.physik.unibe.ch/unibe/philnat/fachbphysik/content/e4897/e4910/e4913/e5244/e8465/files60510/Lec10_01_05_12_ger.pdf
		// we could actually calculate again a delta_j instead of the whole j
		// but I'll work on the other exercises first
		for (i = 1; i < steps; i++) {
			j += 2 * (1 + i % 2) * fun(start + i * stepwidth);
		}
	} while (fabs(1 - 2 * j_old / j) > precision);	
	
	// finally calculate the value of the integral
	return stepwidth/3 * j;
}

int main() {
	
	double result;
	
	int i;
	for (i = 1; i <= 5; i++) {
		result = simpsons_integration(&fun, 10e-7, -i, i);
		printf("%1.8g\n", result);		
	}
	
	return 1;
}