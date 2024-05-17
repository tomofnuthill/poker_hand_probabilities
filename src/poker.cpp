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



void bestHand(int usableCards[]) {

// populating array valueNumber, could be a function?
	int valueNumber[13] = {0};
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 7; j++) {
			valueNumber[i] += (deck[usableCards[j]].value == i);
		}
	}
//	for (int i = 0; i < 13; i++) {
//		std::cout << values[i] << ": " << valueNumber[i] << "\n";
//	}

// populating array suitNumber
	int suitNumber[4] = {0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			suitNumber[i] += (deck[usableCards[j]].suit == i);
		}
	}
//	for (int i = 0; i < 4; i++) {
//		std::cout << suits[i] << ": " << suitNumber[i] << "\n";
//	}
	
	bool end = 0;
	while (end == 0) {
	
		//Checking for royal and straight flush
		for (int i = 0; i < 4; i++) {
			if (suitNumber[i] >= 5) {
				int flushSuit = i;
				bool straightFlushValues[13];	
				for (int j = 0; j < 7; j++) {
					if (deck[usableCards[j]].suit == flushSuit) {
						straightFlushValues[deck[usableCards[j]].value] = 1;
					}
				}
				int maxStraightFlushCounter = 0;
				int straightFlushCounter = 0;
				int straightFlushKicker = 0;
				for (int j = 12; j >= 0; j--) {
					if (straightFlushValues[j] == 1) {
						straightFlushCounter++;
						if ((straightFlushCounter == 1) && (maxStraightFlushCounter < 5)) {
							straightFlushKicker = j;
						}
						else if (straightFlushCounter > maxStraightFlushCounter) {
							maxStraightFlushCounter = straightFlushCounter;
							straightFlushCounter = 0;
						} else {
							straightFlushCounter = 0;
						}
					}
					//Checking for Royal Flush
					if ((maxStraightFlushCounter >= 5) && (straightFlushKicker = 12)) {
						combinations[0] = 9;
						end = 1;
					//Checking for straight flush
					} else if (maxStraightFlushCounter >= 5) {
						combinations[0] = 8;
						end = 1;
						combinations[1] = straightFlushKicker;
					} else if ((maxStraightFlushCounter == 4) && (straightFlushValues[12] == 1)) {
						combinations[0] = 8;
						end = 1;
						combinations[1] = straightFlushKicker;
					}
				}
			}
		}
		if (end == 1) {
			break;
		}
	

	//Checking for quads
		for (int i = 12; i>= 0; i--) {
			if (valueNumber[i] == 4) {
				combinations[0] = 7;
				end = 1;
				combinations[1] = i;
				for (int j = 12; j>= 0; j--) {
					if ((valueNumber[j] > 0) && (valueNumber[j] != 4)) {
						combinations[2] = j;
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
				for (int j = 0; j < 7; j++) {
					if (deck[usableCards[j]].suit == flushSuit) {
						flushValues[deck[usableCards[j]].value] = 1;
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
		else if ((straightCounter == 4) && (valueNumber[12] >= 1)) {
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
						break;
					}						
				}
			break;
			}
		}	
		for (int k = 12; k >= 0; k--) {
			if (valueNumber[k] == 1) {
				combinations[3] = k;
				break;
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
	
