#include <math.h>
#include <stdio.h>

double fun(double x, double p) {
	return cos(x) - p * sqrt(x) * exp(-x);
}

double simpsons_integration(double (*fun)(double, double), double p, double precision, double start, double end) {
	
	// the index for the for loop, the amount of steps
	int i, steps;
	
	// the stepwidth, the length of the interval, the value of the integral, the value of the old integral
	double stepwidth, intervallength, j0, j, j_old, stepwidth_old;
	
	// the length of the interval is 
	intervallength = fabs(end - start);
	
	// the start and the end value of the integral
	j0 = fun(start, p) + fun(end, p);
	j = j0;
	stepwidth = intervallength;
	
	// first we'll only calculate one step
	steps = 1;
	
	do {
		// we need to store the old value of the integral
		j_old = j;
		stepwidth_old = stepwidth;
		
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
		for (i = 1; i < steps; i++) {
			j += 2 * (1 + i % 2) * fun(start + i * stepwidth, p);
		}
	} while ((fabs(stepwidth_old * j_old - stepwidth * j) / (double) 3) > precision);	
	
	// finally calculate the value of the integral
	return stepwidth/3 * j;
}

int main() {
	
	// the result
	double result;
	
	// min and max p
	double p_min = 1, p_max = 5, p;
	
	// the index for our loop
	int i, steps;
	
	// the number of steps to be performed
	steps = ceil(log2((p_max - p_min) / 1e-5));
		
	// now let's rock!
	for (i=0; i < steps; i++) {
		
		// the center and its value
		p = (p_min + p_max) / 2;
		
		result = simpsons_integration(fun, p, 1e-2, 0, 2);
		
		if (result > 0) {
			p_min = p;
		} else {
			p_max = p;
		}
	}
		
	printf("I(%g) = %g\n", p, result);
	
	return 0;
}