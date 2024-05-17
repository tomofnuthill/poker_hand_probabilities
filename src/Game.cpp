//Game.cpp

#include "Game.hpp"
#include <iostream>

Game::Game(int card1, int card2, const int opponentCount):
	opponentCount(opponentCount)
{
	hand[0] = card1;
	hand[1] = card2;
	opponents = new int*[opponentCount];
	for (int i = 0; i < opponentCount; i++) {
		opponents[i] = new int[2];
	}
	populate();

	combinations = new int*[opponentCount + 1];
	for (int i = 0; i < (opponentCount + 1); i++) {
		combinations[i] = new int[6];
	}
}

Game::~Game() {
	for (int i = 0; i < opponentCount; i++) {
		delete[] opponents[i];
	}
	delete[] opponents;

	for (int i = 0; i < (opponentCount + 1); i++) {
		delete[] combinations[i];
	}
	delete[] combinations;

}	
inline void printCard(int i) {
	std::cout << values[deck[i].value] << " of " << suits[deck[i].suit] << "\n";
}


void Game::printHand() {
	printCard(hand[0]);
	printCard(hand[1]);
	std::cout << opponentCount << " opponents\n";
}

void Game::print() {
	#ifdef COUT
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
	#endif
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
void Game::runSimulation() {

//Creating array with usable cards

	for(int i = 0; i < 2; i++) {
		usableCards[i] = hand[i];
	}
	for(int i = 0; i < 5; i++) {
		usableCards[i + 2] = communityCards[i];
	}
	findHand(usableCards, combinations[0]);

	for (int i = 0; i < opponentCount; i++) {
		usableCards[0] = opponents[i][0];
		usableCards[1] = opponents[i][1];
		findHand(usableCards, combinations[i + 1]);
	}

	for (int i = 0; i < opponentCount; i++) {
		for (int j = 0; j < 6; j++) {
//			std::cout << "\nours: " << combinations[0][j] << "theirs: " << combinations[i + 1][j] << "\n";
			if (combinations[0][j] < combinations[i + 1][j]) {
				#ifdef COUT
				std::cout << "we lost\n";
				#endif
				return;
			} else if (combinations[0][j] > combinations[i + 1][j]) {
				break;
			}

		}
	}
	winCount++;
	#ifdef COUT
	std::cout << "we win" << "\n";	
	#endif
}

void Game::expectedValue() {
	float expectedValue;
	expectedValue = winRate * opponentCount + winRate - 1;
	std::cout << "expected value: " << expectedValue << "\n";
}

void Game::simulate(unsigned long count) {
	
	printHand();
	for(int i = 0; i < count; i++) {
		populate();
		print();
		runSimulation();
	}
	winRate = (float)winCount / (float)count;
	std::cout << "win rate: " << winRate * 100.0 << "%\n";

	expectedValue();

}


