//Game.cpp

#include "Game.hpp"
#include <iostream>

Game::Game(int card1, int card2, unsigned int simCount, const int opponentCount):
	opponentCount(opponentCount),
	simCount(simCount)
{
	hand[0] = card1;
	hand[1] = card2;
	opponents = new int*[opponentCount];
	for (int i = 0; i < opponentCount; i++) {
		opponents[i] = new int[2];
	}
	populate();
}

Game::~Game() {
	for (int i = 0; i < opponentCount; i++) {
		delete[] opponents[i];
	}
	delete[] opponents;
}

inline void printCard(int i) {
	std::cout << values[deck[i].value] << " of " << suits[deck[i].suit] << "\n";
}


void Game::print() {
	std::cout << "\nyour hand:\n";
	printCard(hand[0]);
	printCard(hand[1]);
	std::cout << "\ncommunity cards:\n";
	for (int i = 0; i < 5; i++) {
		printCard(communityCards[i]);
	}
	for (int i = 0; i < opponentCount; i++) {
		std::cout << "\nopponent " << i + 1 << ":\n";
		printCard(opponents[i][0]);
		printCard(opponents[i][1]);
	}
}

void Game::populate() {
	bool cards[52] = {0};
	cards[hand[0]] = 1;
	cards[hand[1]] = 1;
	for (int i = 0; i < 5; i++) {
		communityCards[i] = newCard(cards);
		cards[communityCards[i]] = 1;
	}
	for (int i = 0; i < opponentCount; i++) {
		opponents[i][0] = newCard(cards);
		cards[opponents[i][0]] = 1;

		opponents[i][1] = newCard(cards);
		cards[opponents[i][1]] = 1;
	}

}
void Game::createUsableCards() {

//Creating array with usable cards

	for(int i = 0; i < 5; i++) {
		usableCards[i] = communityCards[i];
	}
	for(int i = 0; i < 2; i++) {
		usableCards[i + 5] = hand[i];
	}
}

