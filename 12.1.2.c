#include <math.h>
#include <stdio.h>

// our random number generator
int rn_generator(int x, int a) {
	int y;
	
	y = (a * x) % ((int)pow(2,13) - 1);
	
	return y;
}

int main() {
	
	// the index for the loop
	int i;
	
	// our integer a (element of {81, 83, 85}), the random number x
	int a, x;
	
	// the counter used to find out what seed and variable a are the best
	int counter;
	
	// the maximum counter
	int max_counter = 0, max_a, max_x;
	
	// the loop for the variable a
	for (a = 83; a <= 87; a += 2) {
		
		// the loop for the seed
		for (i = 1; i < 8191; i++) {
			
			// reset the counter
			counter = 0;
			
			// set our seed
			x = i;
			
			// let's find out what the periodicity of our random number generator is
			do {
				x = rn_generator(x,a);
				counter++;
			} while (x != i);
			
			// if the counter is bigger than max_counter store the new maximal data
			if (counter > max_counter) {
				max_a = a;
				max_x = i;
				max_counter = counter;
			}
			
			// TODO
			// - put this inside a textfile for later evaluation
			printf("Periodicity: %i (a = %i, x = %i) \n", counter, a, i);
		}
	}

	// evaluation
	printf("\n\nThe best sequence whas found with the following parameters:\n");
	printf("Seed     (x): %i\n", max_x);
	printf("Variable (a): %i\n", max_a);
	printf("Periodicity:  %i\n", max_counter);
	
	return 0;
}