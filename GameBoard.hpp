#ifndef GAMEBOARD
#define GAMEBOARD

#include "Player.hpp"

class GameBoard
{
public:
	// Constructor + Destructor
	GameBoard();
	~GameBoard();

	// Main public class functionality
	void initializeGameBoard(unsigned int playerNo); // Initialize the game board with your prefered values
	void printGameStatistics(); // Print the game state and statistics
	void gameplay(); // Enter the main gameplay loop

	void print(); // Print the game board state/stats

private:
	// The game board components
	unsigned int player_amount;
	// The Array of players
	Player *player;
	// The player turn buffer
	int *buf;

	// Internally used functions
	// Used in gameplay() | The five gameplay phases + The win condition function
	void startingPhase();
	void equipPhase();
	void battlePhase();
	void economyPhase();
	void finalPhase();
	bool checkWinningCondition();	// Returns 0 if we have a winner and the game is over

};

#endif
