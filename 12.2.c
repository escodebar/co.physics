#include <math.h>
#include <stdio.h>

// our random number generator
int rn_generator(int x, int a) {
	int y;
	
	y = (a * x) % ((int)pow(2,13) - 1);
	
	return y;
}

// returns the number on a dice for a given random number
int dice(int x) {
	return 1 + (x % 6);
}

// this function returns the new field
int snakes_and_ladders(int x) {
	
	int next;
	
	// if you're over 100, you'll have to move back!
	if (x>100) {
		x = 100 - x % 100;
	}
	
	// now let's see on what field you landed and what field is the next
	switch(x) {
		case 1: next = 38;
	   	break;
	
		case 4: next = 14;
		break;
		
		case 9: next = 31;
		break;
		
		case 17: next = 7;
		break;
		
		case 21: next = 42;
		break;             
		                   
		case 28: next = 84;
		break;             
		                   
		case 51: next = 67;
		break;             
                           
		case 54: next = 34;
		break;

		case 62: next = 19;
		break;             
		                   
		case 64: next = 60;
		break;
		
		case 71: next = 91;
		break;
		
		case 80: next = 100;
		break;
		
		case 87: next = 24;
		break;
		
		case 93: next = 73;
		break;
		
		case 95: next = 75;
		break;
		
		case 98: next = 79;
		break;
		
		default: next = x;
	}
	
	return next;
}

int main() {
	
	// the counter, the field number, the variable a and the index i
	int counter, field, a, dice1, dice2, i;	
	
	// set the variable a (periodicity = 8190)
	a = 85;
	
	// let's play 100 times
	for (i = 0; i < 100; i++) {
		
		// reset the counter to 0
		counter = 0;
		
		// reset the field to 0
		field = 0;
		
		// we'll have to set the value of dice2 to the number of a seed
		dice2 = (i + 1);
		
		do {
			// let's generate two new random numbers
			dice1 = rn_generator(dice2, a);
			dice2 = rn_generator(dice1, a);
			
			field = snakes_and_ladders(field + dice(dice1) + dice(dice2));
			
			counter++;

		} while (field != 100);
		
		printf("a: %i  seed: %i  counts: %i \n", a, (i + 1), counter);
	}
	
	return 1;
}