#include <math.h>
#include <stdio.h>


double fun(double x, double p) {
	return cos(x) - p * sqrt(x) * exp(-x);
}

// takes a function, an intervall, a precision,
// and finds one root inside the given interval for the given precision
int root_bisection(double (*f)(double, double), double p, double start, double end, double precision, double *result) {
	
	/* 
		USE: You have to call root_bisection with the following parameters:
		- pointer to a function: the function for which the root has to be found
		- interval: the interval in which the root has to be found
		- precision: the precision at which the search will stop
		- result: the pointer to the double where the result will be stored		
	*/	
	
	/*  the variables used:
		- steps:		the amount of steps we'll have to perform
		- i:			the "index" for the iteration
		- start: 		the start of the interval
		- center: 		the center of the interval
		- end: 			the end of the interval
		- startval: 	value of the function at the start of the interval
		- centerval: 	value of the function at the center of the interval
		- endval:		value of the function at the end of the interval
	*/
	
	// the steps and the index
	int steps, i;

	// the amount of steps (with formula N = log2((b-a)/e))
	steps = ceil(log2((end-start)/precision));
		
	// the center of the interval
	double center;
	
	// the values at the start, the center and the end of the interval
	double startval, centerval, endval;
	startval = f(start, p);
	endval = f(end, p);
	
	// let's check if we're able to find a root inside the interval
	// (or if it's already at the start or the end)
	if (startval * endval > 0) {
		// no results if both values are positive or negative
		return 0;
	}
	
	// now let's rock!
	for (i=0; i < steps; i++) {
		
		// the center and its value
		center = (start + end) / 2;
		
		centerval = f(center, p);
		
		// check if the value at the center is already 0
		if (centerval == 0) {
			i = steps;
			break;
		}
		
		if (startval < 0) {
			if (centerval > 0) {
				end = center;
				endval = centerval; // not really necessary
			} else {
				start = center;
				startval = centerval;
			}
		} else {
			if (centerval > 0) {
				start = center;
				startval = centerval;
			} else {
				end = center;
				endval = centerval; // not really necessary
			}
		}
	}
		
	*result = center;
	
	return 1;
}


int main ()
{
	// the double the user has to give, the result
	double p;
	double result;
	double start = 0;
	double end = 2;
	double precision = 1e-6;
	
	// we need an input from the user
	printf("Put in the value for p: ");
	scanf("%lg", &p);
	
	if (root_bisection(&fun, p, start, end, precision, &result)) {
		printf("f(%lg) = %lg \n", result, fun(result, p));
	} else {
		printf("No root was found inside the interval [%g,%g]\n", start, end);
	}
	
	return 0;
}