#include <iostream>
#include "src/poker.hpp"
#include <cstdlib>
#include "src/Game.hpp"

#define SIM_COUNT 1000000

using namespace std;

int main () {
	srand((unsigned) time(NULL));
	initializeDeck();
	Game game1(0,13,1);
	game1.simulate(SIM_COUNT);

	return 0;

}	

