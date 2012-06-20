#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// this function returns an array of the width nr_stickers with a few stickers within the given range
int* buy_pack(int nr_stickers, int range) {
	
	// our pack of stickers
	int *pack = (int*) calloc(nr_stickers, sizeof(int));
	
	// we need two indexes to loop and the nr of new stickers
	int i, j;
	
	// we need the number of the generated sticker
	int sticker;
	
	// let's create our 5 stickers
	for (i = 0; i < nr_stickers; i++) {
		
		do {
			// generate a random sticker
			sticker = range * (double) rand() / (double) RAND_MAX;
			
			// check if the sticker is already in the pack
			for (j = 0; (j < i) && (pack[j] != sticker); j++) {}
			
			// // if it's not in the pack, add it to the pack
			// if (j == i) {
			// 	pack[i] = sticker;
			// }
			
		} while (j != i);
		
		pack[i] = sticker;
	}
		
	return pack;
}

// this function buys as many packages as needed 'til the album is full
// it returns the amount of packages bought
int fill_album(int range, int stickers_per_pack) {
	
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
		
	} while ((total < range));
	
	// let's free the memory
	free(album);
	
	return counter;
}

int main() {
	
	// the integer for the loop
	int i; int loops = 1e4;
	
	// the counter of packs
	// the total amount of stickers packs bought
	// the maximum number of packs bought
	// the minimum number of packs bought
	int counter = 0, total_counter = 0, max_counter = INT_MIN, min_counter = INT_MAX;
	
	// initialize the seed
	srand(time(NULL));
	
	for (i = 0; i < loops; i++) {
		counter = fill_album(200, 5);
		
		total_counter += counter;
		
		min_counter = counter < min_counter? counter: min_counter;
		max_counter = counter > max_counter? counter: max_counter;
		
	}
	
	printf("You bought in average %f packs\n", (float) total_counter / (float) loops);
	printf("The minimum amount of packs bought was: %i\n", min_counter);
	printf("The maximum amount of packs bought was: %i\n", max_counter);
	
	return 1;

}