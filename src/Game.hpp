//game.hpp

#pragma once
#include "poker.hpp"

class Game {
public: 
	Game(int card1, int card2, unsigned int simCount, const int opponentCount);
	~Game();
	int combinations[6] = {0};
	void print();
	void bestHand(); 
private:	
	const int opponentCount;
	unsigned int simCount;
	int hand[2] = {0};
	int communityCards[5] = {0};
	void populate();	

	int **opponents;
};





