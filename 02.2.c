#include <stdio.h>
#include <math.h>

#define G 9.81

int main (int argc, char const *argv[])
{
	float h;
	
	// Fancy stuff
	printf("When will the stone reach the ground? Let's find out!\n");
	
	printf("Introduce a value for the height \"h\" (in meters): ");
	scanf("%a",&h);
	
	printf("Reaching ground in %0.3f seconds.\n",sqrt((2*h)/G));
	
	
	return 0;
}