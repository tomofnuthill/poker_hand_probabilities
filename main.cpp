#include <iostream>
#include "src/poker.hpp"
#include <cstdlib>
#include "src/Game.hpp"

using namespace std;

int main () {
	srand((unsigned) time(NULL));
	initializeDeck();
//	Game game1(1, 0, 2, 22);
//	game1.print();
	Game game2(12,25,1,5);
	game2.print();
	game2.bestHand();	
}	

