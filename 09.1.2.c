#include <math.h>
#include <stdio.h>

// the function:
double fun(double x) {
	return pow(x, 8);
}

// the derivation of the function:
double funder(double x) {
	return 8*pow(x,7);
}


// takes a function, the derivation of the function, an intervall, a precision,
// and finds one root inside the given interval for the given precision
int root_newton_raphson(double (*f)(double), double (*fder)(double), double start, double precision, double *result) {
	
	int i = 0;
	double x1, x1_old, x2, funval, funderval;
	
	x1 = start;
	x3 = start;
	
 	do {
		x1_old = x1;
		
		funval = f(x1);
		funderval = fder(x1);
		
		if (funderval != 0) {
			x2 = x1 - funval / funderval;
		}
		
		x1 = x2;
		
		i++;
		
	} while ((fabs(x1_old - x2) / 2.0 > precision) & (i < 1000));
		
	*result = x2;
	
	return 1;
}


int main ()
{
	double start, precision, result;
	
	start = 1;
	precision = 10e-8;
	
	root_newton_raphson(&fun, &funder, start, precision, &result);
	printf("%f", result);
	
	return 0;
}