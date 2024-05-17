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

//void Game::populate() {
//	int cards[2 + 5 + opponentCount * 2];
//	cards[0] = hand[0];
//	cards[1] = hand[1];
//	int size = 2;
//	for (int i = 0; i < 5; i++) {
//		communityCards[i] = newCard(cards, size);
//		size++;
//		cards[i + 2] = communityCards[i];
//	}
//	for (int i = 0; i < opponentCount; i++) {
//		opponents[i][0] = newCard(cards, size);
//		size++;
//		cards[i * 2 + 2 + 5] = communityCards[i];
		
//		opponents[i][1] = newCard(cards, size);
//		size++;
//		cards[i * 2 + 2 + 5 + 1] = communityCards[i];
//	}

//}

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

void Game::bestHand() {
// populating array valueNumber, could be a function?
	int valueNumber[13] = {0};
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 5; j++) {
			valueNumber[i] += (deck[communityCards[j]].value == i);
		}
		for (int j = 0; j < 2; j++) {
			valueNumber[i] += (deck[hand[j]].value == i);
		}
	}
//	for (int i = 0; i < 13; i++) {
//		std::cout << values[i] << ": " << valueNumber[i] << "\n";
//	}

// populating array suitNumber
	int suitNumber[4] = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			suitNumber[i] += (deck[communityCards[j]].suit == i);
		}
		for (int j = 0; j < 2; j++) {
			suitNumber[i] += (deck[hand[j]].suit == i);
		}
	}
//	for (int i = 0; i < 4; i++) {
//		std::cout << suits[i] << ": " << suitNumber[i] << "\n";
//	}
	
bool end = 0;
while (end == 0) {

	//Checking for quads
		for (int i = 12; i>= 0; i--) {
			if (valueNumber[i] == 4) {
				combinations[0] = 7;
				end = 1;
				for (int j = 12; j>= 0; j--) {
					if ((valueNumber[j] > 0) && (valueNumber[j] != 4)) {
						combinations[1] = j;
						break;
					}
				}
			}
		}
		if (end == 1) {
			break;
		}
	
	//Checking for full house
		for (int i = 12; i >= 0; i--) {
			if (valueNumber[i] == 3) {
				for (int j = 12; j >= 0; j--) {
					if ((valueNumber[j] >= 2) && (j != i)) {
				       		combinations[0] = 6;
					 	end = 1;
						combinations[1] = i;
						combinations[2] = j;
						break;
					}
				}
				break;
			}
		}
		if (end == 1) {
			break;
		}	
		
	//Checking for flush
		for (int i = 0; i < 4; i++) {
			if (suitNumber[i] >= 5) {
				combinations[0] = 5;
				end = 1;
				int flushSuit = i;
				bool flushValues[13];	
				for (int j = 0; j < 5; j++) {
					if (deck[communityCards[j]].suit == flushSuit) {
						flushValues[deck[communityCards[j]].value] = 1;
					}
				}
				for (int j = 0; j < 2; j++) {
					if (deck[hand[j]].suit == flushSuit) {
						flushValues[deck[hand[j]].value] = 1;
					}
				}
				int e = 1;
				for (int j = 12; j >= 0; j--) {
					if (flushValues[j] == 1) {
						combinations[e] = j;
						e++;
						if (e >= 6) {
							break;
						}
					}
				}
			}
		}
		if (end == 1) {
			break;
		}
		
	//Checking for straight 
		int straightCounter = 0;
		int maxStraightCounter = 0;
		int straightKicker = 0;
		for (int i = 12; i >= 0; i--) {
			if (valueNumber[i] >= 1) {
				straightCounter++;
				if ((straightCounter == 1) && (maxStraightCounter < 5)) {
					straightKicker = i;
				}
			} else if (straightCounter > maxStraightCounter) {
				maxStraightCounter = straightCounter;
				straightCounter = 0;	
			} else {
				straightCounter = 0;
			}
		}
		if (maxStraightCounter >= 5) {
			combinations[0] = 4;
			end = 1;
			combinations[1] = straightKicker;
		}
		if (end == 1) {
			break;
		}


	//Checking for three of a kind
		for (int i = 12; i >= 0; i--) {
			if (valueNumber[i] == 3) {
				combinations[0] = 3;
				end = 1;
				combinations[1] = i;
				for (int j = 12; j >= 0; j--) {
					if (valueNumber[j] == 1) {
						combinations[2] = j;
						for (int k = j -1; k >= 0; k--) {
							if (valueNumber[k] == 1) {
								combinations[3] = k;
								break;
							}
						}
					break;
					}
				}
			}
		}	
		if (end == 1) {
			break;
		}
			
	//Checking for two pair 
		for (int i = 12; i>= 0; i--) {
			if (valueNumber[i] == 2) {
		       		for (int j = i - 1; j >= 0; j--) {
			 		if (valueNumber[j] == 2) {
						combinations[0] = 2;
						end = 1;
						combinations[1] = i;
						combinations[2] = j;
						for (int k = 12; k >= 0; k--) {
							if (valueNumber[k] == 1) {
								combinations[3] = k;
								break;
							}
						}
						break;
				 	}
				}
			}
		}		
		
		if (end == 1) {
			break;}

	//Checking for pair
		for (int i = 12; i>= 0; i--) {
			if (valueNumber[i] == 2) {
				combinations[0] = 1;
				end = 1;
				combinations[1] = i;
				int c = 2;
				// c is a counter
				for (int j = 12; j >= 0; j--) {
					if (valueNumber[j] == 1) {
						combinations[c] = j;						
						c++;
						if (c > 4) {
							break;
						}
					}
				}
			}
		}

		if (end == 1) {
			break;
		}
	
	//Assigning high card
		combinations[0] = 0;
		end = 1;
		int d = 1;
		// d is a counter
		for (int i = 12; i >= 0; i--) {
			if (valueNumber[i] == 1) { 
				combinations[d] = i;
				d++;
				if (d > 5) {
					break;
				}
			}
		}

		if (end == 1) {
			break;
		}

	
	
	}

	
	std::cout << "\n" << combinationsDecoder[combinations[0]] << "\n";
	       
	for (int i = 1; i < 6; i++) {
		std::cout << values[combinations[i]] << "\n";
	}
	
}	
	
