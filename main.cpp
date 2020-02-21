#include <iostream>
#include "ui.hpp"
#include "inputMgr.hpp"
#include "GameBoard.hpp"

using namespace std;

#define NUMBER_OF_PLAYERS 2

void SplashScreen();

int main(){

	#ifdef UI
	SplashScreen();
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
	pause();
	#endif

	// Enter the main gameplay loop
	cout << endl << " --- Starting game... ---" << endl;
	board.gameplay();

	cout << " > Quitting game..." << endl;
	cout << " ___Game made for glory by azuran and pigeon___" << endl;
	uiTerminate(); // Garbage collect ui
	return 0;
}

void SplashScreen(){
	uiClear();
	cout << "              <> --- Lidl Heartstone ALPHA (v0.1) --- <>" << endl;
	cout << endl;
	cout << "               )\\         O_._._._A_._._._O         /(" << endl;
	cout << "                \\`--.___,'=================`.___,--'/" << endl;
	cout << "                 \\`--._.__                 __._,--'/" << endl;
	cout << "                   \\  ,. l`~~~~~~~~~~~~~~~'l ,.  /" << endl;
	cout << "       __            \\||(_)!_!_!_.-._!_!_!(_)||/            __" << endl;
	cout << "       \\`-.__         ||_|____!!_|;|_!!____|_||        __,-'//" << endl;
	cout << "        \\    `==----='-----------'='-----------`=---=='    //" << endl;
	cout << "        | `--.                                         ,--'|" << endl;
	cout << "         \\  ,.`~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~',. /" << endl;
	cout << "           \\||  ____,-------._,-------._,-------.____  ||/" << endl;
	cout << "            ||\\|___!`======= !`======= !`======= !___|/||" << endl;
	cout << "            || |---||--------||-| | |-!!--------||---| ||" << endl;
	cout << "  __O_____O_ll_lO_____O_____O|| |'|'| ||O_____O_____Ol_ll_O_____O__" << endl;
	cout << "  o H o o H o o H o o H o o |-----------| o o H o o H o o H o o H o" << endl;
	cout << " ___H_____H_____H_____H____O =========== O____H_____H_____H_____H___" << endl;
	cout << "                          /|=============|\\" << endl;
	cout << "()______()______()______() '==== +-+ ====' ()______()______()______()" << endl;
	cout << "||{_}{_}||{_}{_}||{_}{_}/| ===== |_| ===== |\\{_}{_}||{_}{_}||{_}{_}||" << endl;
	cout << "||      ||      ||     / |==== s(   )s ====| \\     ||      ||      ||" << endl;
	cout << "======================()  =================  ()======================" << endl;
	cout << "----------------------/| ------------------- |\\----------------------" << endl;
	cout << "                     / |---------------------| \\" << endl;
	cout << "-'--'--'           ()   ---------------------   ()" << endl;
	cout << "                   /| ------------------------- |\\    --'--'--'" << endl;
	cout << "       --'--'     / |---------------------------| \\    '--'" << endl;
	cout << "                ()  |___________________________|  ()           '--'-" << endl;
	cout << "  --'-          /| _______________________________  |\\" << endl;
	cout << " --'           / |__________________________________| \\" << endl;

	cout << "\t\t      ~~~ Art by Glory Moon ~~~" << endl << endl;

	cout << "\t\t    Press Enter key to get started" << endl;
	pause();
	uiClear();
}