#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// the inverse function of the cumulative distribution
double P_inv_z(double z) {
	return acos((double) 1 - (double) 2 * z);
}

int* cdf_monte_carlo(double (*fun)(double), unsigned int steps, unsigned int bins) {
	
	// start our random number generator
	srand(time(NULL));
	
	// our random number
	double rn;
	
	// the maximum value of our cdf inverse function
	double max = fun(1);
	
	// the histogram
	int *histogram = (int*) calloc(bins, sizeof(int));
	
	// now let's shoot!
	while (steps > 0) {
		
		// a wild random number appears
		rn = (double) rand() / (double) RAND_MAX;
		
		// let's calculate in which bin our throw landed
		histogram[(int)(bins * (fun(rn) / max))]++;
		
		// one step less
		steps--;
	}
		
	return histogram;
}

int main() {
	
	// the number of times to generate numbers and the amount of bins
	unsigned int n, bins;
	
	// 40 bins, lalala, 40 bins, lalala
	bins = 40;
	
	int *histograms[20];
	
	// should we really start with only 2 shots? i'd say we start with a higher number
	for (n = 1; n < pow(2, 20); n *= 2) {
		histograms[(int)log2(n)] = cdf_monte_carlo(&P_inv_z, n, bins);
	}
	
	int i, j;
	
	// now let's print out our data in such way, that we can plot it with mathematica
	for (i = 0; i < 20; i++) {
		for (j = 0; j < bins; j++) {
			printf("{%i, %i},", (j+1), histograms[i][j]);
		}
		printf("\n");
	}
	
	
	return 1;
}