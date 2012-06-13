#include <stdio.h>
#include <math.h>

int main (int argc, char const *argv[])
{
	float phi;
	
	printf("Introduce an angle phi:");
	scanf("%a",&phi);
	
	printf("sin(%0.3f) = %0.3f\n", phi, sin(phi));
	
	return 0;
}