#ifndef GAMEBOARD
#define GAMEBOARD

class GameBoard
{
public:
	GameBoard();
	~GameBoard();

	initializeGameBoard();
	printGameStatistics();
	gameplay();

	startingPhase();
	equipPhase();
	battlePhase();
	economyPhase();
	finalPhase();

	checkWinningCondition();

private:

	
};

#endif