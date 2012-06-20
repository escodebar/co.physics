#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// this function returns an array of the width nr_stickers with a few stickers within the given range
int* buy_pack(int nr_stickers, int range) {
	
	// our pack of stickers
	int *pack = (int*) calloc(nr_stickers, sizeof(int));
	
	// we need two indexes to loop and the nr of new stickers
	int i, j;
	
	// we need the number of the generated sticker
	int sticker;
	
	// now let's get some stickers (randomly)
	for (i = 0; i < nr_stickers; i++) {
		
		do {
			// generate a random sticker
			sticker = range * (double) rand() / (double) RAND_MAX;

			// let's check if the sticker is already in the pack
			// TODO
			for (j = 0; (j < i+1) && (sticker != pack[j]); j++) {}
			
			printf("Pack[%i] = %i\n", i, sticker);
			
		} while (j!=i);
		
		// the sticker is new, let's add it to the pack
		pack[i] = sticker;
	}
	
	return pack;
}

int main() {
	
	// the range of the stickers
	int range = 200;
	int stickers_per_pack = 5;
	
	// our album
	int *album = (int*) calloc(range, sizeof(int));
	
	// our pack of stickers we'll buy
	int *pack;
	
	// our total amount of different stickers
	int total;
	
	// an index for the loop
	int i;
	
	// the counter of bought packs
	int counter = 0;
	
	do {
		// buy a pack
		// don't be greedy, it's just 5 CHF!
		pack = buy_pack(stickers_per_pack, range);
		
		// let's stick the news stickers inside the album
		// if there are already stickers inside, we'll
		// just stick the new ones over the old ones...
		// our album will be thick as hell, but it'll be
		// a priceless joy once it's finished!
		for (i = 0; i < stickers_per_pack; i++) {
			album[pack[i]] = 1;
		}
		
		// we spent another 5 CHF! awesome!
		counter++;
		
		// now, let's count the amount of stickers
		// we already have inside the album
		total = 0;
		for (i = 0; i < range; i++) {
			total += album[i];
		}
		
	} while ((total < range) && counter < 10);
	
	printf("Mister! You bought %d packs!", counter);
	
	return 1;
}