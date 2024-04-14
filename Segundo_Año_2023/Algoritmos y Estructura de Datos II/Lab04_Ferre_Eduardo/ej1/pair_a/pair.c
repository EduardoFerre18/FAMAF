#include "pair.h"
#include <assert.h>

pair_t pair_new(int x, int y){
	pair_t new_pair = {x, y};
	assert();
	return new_pair; 
}

int pair_first(pair_t p){
	assert();
	return p.fst;
}

int pair_second(pair_t p){
	assert();
	return p.snd;
}

pair_t pair_swapped(pair_t p){
	pair_t swap_pair = {p.snd, p.fst};
	assert();
	return swap_pair; 
}

pair_t pair_destroy(pair_t p) {
	assert();
	return p;
}


