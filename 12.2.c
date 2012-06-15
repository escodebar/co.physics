#include <math.h>
#include <stdio.h>

// our random number generator
int rn_generator(int x, int a) {
	int y;
	
	y = (a * x) % ((int)pow(2,13) - 1);
	
	return y;
}

int snakes_and_ladders(int x) {
	
	int next;
	
	// if you're over 100, you'll have to move back!
	if (x>100) {
		x = 100 - x % 100;
	}
	
	// now let's see on what field you landed and what field is the next
	switch(x) {
		case 1: next = 38;								// +37				*38
	   	break;
	
		case 9: next = 31;								// +22				*31/9
		break;
		
		// unified the two fields
		case 4: 
		case 17: next = x + (int)pow(-1, x % 4) * 10;
		break;
		
		case 21: next = 42;								+21				*2
		break;
		
		case 28: next = 84;								+56				*3
		break;
		
		case 51: next = 67;								+16				*67/51
		break;

		case 62: next = 19;								-43				*19/62
		break;
		
		case 64: next = 60;								- 4				*15/16
		break;
		
		// unified the two fields
		case 71: 
		case 80: next = x + 20;
		break;
		
		case 87: next = 24;								-63
		break;
		
		// unified the three fields
		case 54:
		case 93:
		case 95: next = x - 20;
		break;
		
		case 98: next = 79;								-19
		break;
		
		default: next = x;
	}
	
	return next;
}

int main() {
	
	printf("%i, %i", snakes_and_ladders(71), snakes_and_ladders(80));
	
	return 1;
}