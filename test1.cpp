#include <iostream>
#include "src/poker.hpp"
#include<cstdlib>

using namespace std;

int main () {

        Card deck[52];
	int communityCardNumber = 5;

        for (int i = 0; i < 4; i++) {
                Card thisCard;
                thisCard.suit = i;
			for (int j = 0; j < 13; j++) {
				thisCard.value = j;
				deck[i * 13 + j] = thisCard;
			}
	}
			


	int deckIndex[52];

	for (int i = 0; i < 52; i++) {
		deckIndex[i] = i;}

//	picks card "c" and shifts deckIndex to nolonger include that card
	
	int hand[2] {38,37};
	//hand cards must be listed from greatest to smallest in order for removal from deck to work
	for (int i = 0; i < 2; i++) {
		cout << "hole cards: " << values[deck[hand[i]].value] << " of " << suits[deck[hand[i]].suit] << "\n";}

	for (int i = 0; i < 2; i++) {

		for (int j = hand[i]; j < 52; j++) {
			deckIndex[j] = deckIndex[j + 1];}
	}


//	Card* hand [2] {&deck[0],& deck[1]};
//	for (int i = 0; i < 2; i++) {
//		cout << values[(*hand[i]).value] << " of " << suits[(*hand[i]).suit] << "\n";

// picking three cards:
	
	srand((unsigned) time(NULL));
	int communityCards[communityCardNumber];

	for (int i = 0; i < communityCardNumber; i++) {	
		int random = rand() % (50 - i);
		communityCards[i] = deckIndex[random];
		for (int j = random; j < (50 - i); j++) {
			deckIndex[j] = deckIndex[j + 1];}
	}
	
	for (int i = 0; i < communityCardNumber; i++) {
		cout << "Community Cards: " << values[deck[communityCards[i]].value] << " of " << suits[deck[communityCards[i]].suit] << "\n";}	

//	for (int i = 0; i < (50 - communityCardNumber); i++) {
//		cout << values[deck[deckIndex[i]].value] << " of " << suits[deck[deckIndex[i]].suit] << "\n";}
	
//	int handPairs[2] {0,0};	
	
//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j < 5; j++) {
//			if (deck[hand[i]].value == deck[communityCards[j]].value) {
//				handPairs[i] = handPairs[i] + 1 ;}
//	}}

//	cout << handPairs[0] << "\n";
	
//	cout << handPairs[1] << "\n";

//	if (handPairs[0] == 3 || handPairs[1] == 3) {
//		cout << "quads" << "\n";
//	} else if ((handPairs[0] == 2 && handPairs[1] == 1) || (handPairs[0] == 1 && handPairs[1] == 2)) {
//		cout << "full house" << "\n";
//	} else if (handPairs[0] == 2 || handPairs[1] == 2) {
//		cout << "trips" << "\n";
//	} else if (handPairs[0] == 1 && handPairs[1] == 1) {
//		cout << "two pair" << "\n";
//	} else if (handPairs[0] == 1 || handPairs[1] == 1) {
//		cout << "pair" << "\n";
//	}		


	int totalCards[communityCardNumber + 2];
	
	for (int i = 0; i < 2; i++) {
		totalCards[i] = hand[i];}
	for (int i = 0; i < communityCardNumber; i++) {
		totalCards[i + 2] = communityCards[i];}

//	for (int i = 0; i < (communityCardNumber + 2); i++) {
//		cout << "totalCards: " << values[deck[totalCards[i]].value] << " of " << suits[deck[totalCards[i]].suit] << "\n";}	

	int valueNumber[13];


	for (int i = 12; i >= 0; i = i - 1) {
		valueNumber[i] = 0;
		for (int j = 0; j < (communityCardNumber + 2); j++) {
			if (deck[totalCards[j]].value == i) {
				valueNumber[i] = valueNumber[i] + 1;}
				}
			}
	for (int i = 0; i < 13; i++) {
		cout << values[i] << ": " << valueNumber[i] << "\n";
	}

	int suitNumber[4];

	for (int i = 0; i < 4; i++) {
		suitNumber[i] = 0;
		for (int j = 0; j < (communityCardNumber + 2); j++) {
			if (deck[totalCards[j]].suit == i) {
				suitNumber[i] = suitNumber[i] + 1;}
				}
			}
	for (int i = 0; i < 4; i++) {
		cout << suits[i] << ": " << suitNumber[i] << "\n";
	}

	for (int i = 0; i < 4; i++)
		if (suitNumber[i] >= 5) {
			cout << "flush" << "\n";}
	
//	int c = 0;	
//	
//	while (c == 0) {
//		for (int i = 12; i >= 0; i = i - 1) {
//			if (valueNumber[i] == 4) {
//				cout << "quad " << values[i] << "s" << "\n";
//				c++;}}
//		for (int i = 12; i >= 0; i = i - 1) {
//			if (valueNumber[i] == 3) {
//				cout << "trip " << values[i] << "s" << "\n";
//				c++;}}
//		for (int i = 12; i >= 0; i = i - 1) {
//			if (valueNumber[i] == 2) {
//                      	cout << "pair of " << values[i] << "s" << "\n";
//				c++;}}
//		for (int i = 12; i >= 0; i = i - 1) {
//			if (valueNumber[i] == 1) {
//                      cout << values[i] << " high" << "\n";
//			c++;}}}


	

}	

