//poker.cpp

#include "poker.hpp"
#include <cstdlib>

const char* suits[] = {"hearts","diamonds","clubs","spades"};
const char* values[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
const char* combinationsDecoder[] = {"high card","pair","two pair","three of a kind","straight","flush","full house","quads","straight flush","royal flush"};

Card deck[52];

int newCard(bool cards[]) {

	int size = 0;
	for (int i = 0; i < 52; i++) {
		size += cards[i];
	}
	int random = std::rand() % (52 - size);
	int shift = 0;
	for (int i = 0; i <= (random + shift); i++) {
		shift += cards[i];
	}
	return random + shift;
	
}

void initializeDeck() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			deck[13 * i + j].value = j;
			deck[13 * i + j].suit = i;
		}
	}
}
	

