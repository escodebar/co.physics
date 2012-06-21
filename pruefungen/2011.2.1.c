#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

double gaussian_distr(double mu, double sigma) {
	
	// our uniformal distributed random numbers
	double u1, u2;
	
	u1 = (double) rand() / (double) RAND_MAX;
	u2 = (double) rand() / (double) RAND_MAX;
	
	// our normal distributed random number
	return mu + sigma * sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
}

double uniform_distr(double start, double end) {
	
	// stretch it, bulge it and shift it
	return ((end - start) * (double) rand() / (double) RAND_MAX) + start;
}

int in_circle(double x, double y, double radius) {
	return x*x + y*y <= radius*radius;
}

int brownian_motion(double x0, double y0, double radius, double mu, double sigma) {
	
	// the counter of steps until the particle left the circle
	int counter = 0;
	
	double x = x0;
	double y = y0;
	
	do {
		// get the coordinates of the next point
		x += gaussian_distr(mu, sigma) * cos(uniform_distr(0, 2 * M_PI));
		y += gaussian_distr(mu, sigma) * sin(uniform_distr(0, 2 * M_PI));
		
		counter++;
	} while (in_circle(x, y, radius));
	
	// return the number of steps
	return counter;
}

int main () {

	// init the random number generator
	srand(time(NULL));
	
	// starting position, radius of the field, mu and sigma
	double x0 = 0, y0 = 0, radius = 10, mu = 0, sigma = 1;
	
	// the total amont of steps, the steps for each particle, the maximum number of steps and the minimum number of steps
	int total_steps = 0, steps = 0, min_steps = INT_MAX, max_steps = INT_MIN;
	
	// the amount of particles and the index for the loop
	int particles = 1e4, i;
	
	for (i = 0; i < particles; i++) {
		steps = brownian_motion(x0, y0, radius, mu, sigma);
		
		total_steps += steps;
		
		if (max_steps < steps) {
			max_steps = steps;
		}
		if (min_steps > steps) {
			min_steps = steps;
		}
	}
	
	printf("The particle took in average %f steps to leave the circle\n", (float) total_steps / (float) particles);
	printf("The minimum amount of steps: %i\n", min_steps);
	printf("The maximum amount of steps: %i\n", max_steps);
	
	return 0;
}