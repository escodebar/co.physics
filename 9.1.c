#include <math.h>

// the defined function:
// exp(-x) - x
double fun(double);
double fun(double x) {
	return exp(-x) - x;
}

// takes a function, an intervall, a precision,
// and finds one root inside the given interval for the given precision
int root_bisection(double (*f)(double), double interval[], double precision, double *result);
int root_bisection(double (*f)(double), double interval[], double precision, double *result) {
	
	double start, end, center, centerval, newinterval[2];
	newinterval[0] = interval[0];
	newinterval[1] = interval[1];
	
	// the center of the interval
	center = (interval[0] + interval[1])/2;
	
	// check if the given precision is reached
	if ((interval[1] - interval[0])/2 < precision) {
		*result = center;
		return 1;
	}

	// the value at the start, the center and the end of the interval
	// TODO
	// - the start and the end were already evaluated, so we have 
	start = f(interval[0]);
	centerval = f(center);
	end = f(interval[1]);
	
	// TODO
	// - we can do this part better... i'm sure!
	if ((start < 0) && (end > 0)) {
		if (centerval < 0) {
			newinterval[0] = center;
		} else {
			newinterval[1] = center;
		}
	} else if ((start > 0) && (end < 0)) {
		if (centerval < 0) {
			newinterval[1] = center;
		} else {
			newinterval[0] = center;
		}
	} else {
		// in this case we won't find any results, the interval has to be chosen more precisely
		printf("no results");
		return 0;
	}
	
	return root_bisection(*f, newinterval, precision, result);
}

int main ()
{
	double result, interval[] = {0,1};
	
	root_bisection(*fun, interval, pow(10,-8), &result);
	
	printf("%f", result);
	
	return 0;
}

