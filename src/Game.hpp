//game.hpp

#pragma once
#include "poker.hpp"

class Game {
public: 
	Game(int card1, int card2, const int opponentCount);
	~Game();
	void print();
	void simulate(unsigned long count);
private:	
	const int opponentCount;
	unsigned long simCount = 1;
	int hand[2] = {0};
	int communityCards[5] = {0};
	void populate();	
	void createUsableCards();	
	void runSimulation();
	int winCount = 0;
	float winRate;
	int usableCards[7];	
	int **combinations;
	int **opponents;
	void printHand();
	void expectedValue();
};




