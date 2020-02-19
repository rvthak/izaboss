#include <iostream>
#include "GameBoard.hpp"

using namespace std;

#define NUMBER_OF_PLAYERS 2

void SplashScreen1();
void SplashScreen2();

int main(){

	#ifdef UI
	SplashScreen2();
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


void SplashScreen1(){
	system("clear");
	cout << "             <> --- Lidl Heartstone ALPHA (v0.1) --- <>" << endl;
	cout << endl;
	cout << "   `,.      .   .        *   .    .      .  _    ..          ." << endl;
	cout << "     ,~-.         *           .    .       ))       *    ." << endl;
	cout << "            *          .   .   |    *  . .  ~    .      .  .  ," << endl;
	cout << " ,           `-.  .            :               *           ,-" << endl;
	cout << " -             `-.         *._/_\\_.       .       .   ,-'" << endl;
	cout << " -                 `-_.,      |n|     .      .       ;" << endl;
	cout << "    -                    \\ ._/_._\\_.  .          . ,'         ," << endl;
	cout << "     -                    `-.|.n.|      .   ,-.__,'         -" << endl;
	cout << "      -                   ._/_,_,_\\_.    ,-'              -" << endl;
	cout << "      -                     |..n..|-`'-'                -" << endl;
	cout << "       -                 ._/_,_,_,_\\_.                 -" << endl;
	cout << "         -               ,-|...n...|                  -" << endl;
	cout << "           -         ,-'._/_,_,_,_,_\\_.              -" << endl;
	cout << "             -  ,-=-'     |....n....|              -" << endl;
	cout << "              -;       ._/_,_,_,_,_,_\\_.         -" << endl;
	cout << "             ,-          |.....n.....|          -" << endl;
	cout << "           ,;         ._/_,_,_,_,_,_,_\\_.         -" << endl;
	cout << "  `,  '.  `.   .  `,  '.| n   ,-.   n |  ,  `.  `,  '.  `,  '," << endl;
	cout << ",.:;..;;..;;.,:;,.;:,o__|__o !.|.! o__|__o;,.:;.,;;,,:;,.:;,;;:" << endl;
	cout << " ][  ][  ][  ][  ][  |_i_i_H_|_|_|_H_i_i_|  ][  ][  ][  ][  ][" << endl;
	cout << "                     |     //=====/\\     |" << endl;
	cout << "                     |____//=======/\\____|" << endl;
	cout << "                         //=========/\\    " << endl;
	cout << "\t\t    ~~~ Art by Glory Moon ~~~" << endl << endl;

	cout << "\t\t  Press Enter key to get started" << endl;
	cin.get();
	system("clear");
}

void SplashScreen2(){
	system("clear");
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
	cout << "            || |---||--------||-| | |-!!--------||---|  ||" << endl;
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
	cin.get();
	system("clear");
}