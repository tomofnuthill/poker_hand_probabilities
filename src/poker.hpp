//poker.hpp

#pragma once
extern const char* suits[]; //size = 5
extern const char* values[]; //size = 15		

typedef struct Card {

	//0=hearts, 1=diamonds, 2=clubs, 3=spades
	//0=2... 12=ace

	unsigned short suit;
	unsigned short value;

	Card(unsigned short suit=0, unsigned short value=0): 
		value (value), suit (suit)
	{}

} Card;

extern Card deck[52];

void initializeDeck();

int newCard(bool cards[]);
extern const char* combinationsDecoder[]; //size = 10
