#include <iostream>
#include "GameBoard.hpp"

using namespace std;

#define NUMBER_OF_PLAYERS 2

int main(){
	#ifdef UI
	system("clear");
	#endif
	cout << " <> --- Lidl Heartstone ALPHA (v0.1) --- <>" << endl;

	// Create a game board
	cout << " > Creating Game Board..." << endl;
	GameBoard board;

	// Initialize it to prepare for the game
	cout << " > Initializing Game Board..." << endl;
	board.initializeGameBoard(NUMBER_OF_PLAYERS);

	// Print initial game state and statistics
	cout << " > Printing Game Stats:" << endl;
	board.printGameStatistics();

	#ifdef UI
	cout << " > Press Enter key to start a game:" << endl;
	cin.get();
	#endif

	// Enter the main gameplay loop
	cout << endl << " --- Starting game... ---" << endl;
	board.gameplay();

	cout << " > Quitting game..." << endl;
	cout << " ___Game made for glory by azuran and pigeon___" << endl;
	return 0;
}
