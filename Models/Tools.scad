
module place_at_array(array) {
	if(len(array) >= 1)

		for(i = [0: len(array) - 1]) translate(array[i]) children();
}
