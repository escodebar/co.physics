#include <math.h>
#include <stdio.h>

// our random number generator
int rn_generator(int x, int a) {
	int y;
	
	y = (a * x) % ((int)pow(2,13) - 1);
	
	return y;
}

int main() {
	
	// the indexes for the three different loops
	int i,j,k;
	
	// our integer a (element of {81, 83, 85}), the random number x, the number of the dice xd
	int a, x, xd;
	
	// our integer histogram
	int histogram[6] = {0,0,0,0,0,0};
	
	// expectation value x, expectation value x^2, variance
	float ewx, ewxx, varx;
	
	// the real expectation values and variance of a dice
	float ewxr, ewxxr, varxr;
	
	// the loop to calculate the expectation values
	for (i = 1; i < 7; i++) {
		ewxr += (float)i / (float)6;
		ewxxr += (float)i * (float)i / (float)6;
	}
	
	varxr = sqrt(ewxxr - ewxr * ewxr);
	
	// the loop for the variable a
	for (i = 0; i < 3; i++) {
		
		// our variable a
		a = 83 + 2*i;
		
		// the loop for the seed
		for (j = 1; j < 8191; j++) {
			
			// set our seed
			x = j;
			
			// the loop for the 3k numbers
			for (k = 0; k < 3000; k++) {
				
				// calculate the next random number
				x = rn_generator(x,a);
				
				// calculate the number of the dice
				xd = 1 + (x % 6);
				
				histogram[xd-1]++;
			}
			
			printf("Results for a=%i, x_initial=%i: \n", a, j);
			
			// reset the expectation values and the variation
			ewx = 0;
			ewxx = 0;
			varx = 0;
			
			// print out the histogram and reset it
			for (k = 0; k < 6; k++) {
				
				ewx += (float)(k+1) * (float)histogram[k]/(float)3000;
				ewxx += (float)(k+1) * (float)(k+1) * (float)histogram[k]/(float)3000;
				
				// reset the histogram
				histogram[k] = 0;
			}
			
			// calculate the variation
			varx = sqrt(ewxx - ewx*ewx);
			
			printf("expect. value: %f,  variantion: %f  \n", ewx, varx);			
		}
	}
	
	return 1;
}