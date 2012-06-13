#include <stdio.h>

int main (int argc, char const *argv[])
{
	// Define the variables
	float a,b;
	
	// Fancy stuff
	printf("Let's solve \"ax + b = 0\"!\n");
	
	printf("Introduce a value for \"a\": ");
	scanf("%a",&a);
	printf("Introduce a value for \"b\": ");
	scanf("%a",&b);	
	
	printf("The solution is: x=%.3f\n",-b/a);
	
	return 0;
}