#include <math.h>

// the defined function:
// exp(-x) - x
double fun(double);
double fun(double x) {
	return exp(-x) - x;
}

// the derivation of the defined function:
// -exp(-x) - 1
double funder(double);
double funder(double x) {
	return -exp(-x) - 1;
}


// takes a function, an intervall, a precision,
// and finds one root inside the given interval for the given precision
int root_newton_raphson(double, double, double*);
int root_newton_raphson(double start, double precision, double *result) {
	
	double x, funval, funderval;
	int i = 0;
	
	// TODO
	// - stop it at the right time
	
	while (i < 100) {
	
		funval = fun(x);
		funderval = funder(x);
		
		if (funderval != 0) {
			x = x - funval / funderval;
		} else {
			i = 100;
		}
		
		i++;
	}
	
	*result = x;
	
	return 1;
}


int main ()
{
	double start, precision, result;
	
	start = 1;
	precision = pow(10,-8);
	
	root_newton_raphson(start, precision, &result);
	printf("%f", result);
	
	return 0;
}