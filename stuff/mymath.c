float total(float vals[], int amount) {
	int i; float total;
	
	for (i=0, total=0; i<amount; i++) {
		total += vals[i];
	}
	
	return total;
}

float mean(float vals[], int amount) {
	return total(vals, amount) / amount;
}