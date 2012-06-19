#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fun(double x) {
	
	// initialise the result
	double result = 0;
	
	// if x is inside our interval calculate it
	if ((x >= 0) && (x <= M_PI)) {
		result = sin(x)/2;
	}
	
	return result;
}

double cdf_monte_carlo() {
	
	
	
	return 1;
}

int main() {
	
	double result;
	
	result = cdf_monte_carlo();
	
	printf("Value of the integral: %g\n", result);
	
	return 1;
}