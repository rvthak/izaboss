#include "GameBoard.hpp"

using namespace std;


GameBoard::GameBoard(){
	player=NULL;
}
GameBoard::~GameBoard(){
	if(player!=NULL){
		delete[] player;
	}
	return;
}


void GameBoard::initializeGameBoard(unsigned int playerNo){
	// Prepare the board for a game by creating the players
	if(playerNo>1&&playerNo<9){	// Check the player number is in the set range
		player_amount=playerNo;
		player=new Player[player_amount];
		cout << " > Game board initialized succesfully!" << endl;
	}
	else{
		cout << " > Parameter Error: Player Number outside bounds." << endl;
		cout << " > Game board initialization failed! Please try again with different values" << endl;
	}
	return;
}
void GameBoard::printGameStatistics(){
	print(); // Print the game board state/stats

	// Print each player's stats 
	for(int i=0; i<player_amount; i++){
		player[i].print();
	}
}
void GameBoard::gameplay(){
	if(player==NULL){
		cout << " > Game Error: Game board not initialized. Terminating gameplay..." << endl;
		return;
	}

	// Main game loop
	while(checkWinningCondition()){
		startingPhase();
		equipPhase();
		battlePhase();
		economyPhase();
		finalPhase();
	}
	return;
}

//=====================================================

void GameBoard::startingPhase(){

}
void GameBoard::equipPhase(){

}
void GameBoard::battlePhase(){

}
void GameBoard::economyPhase(){

}
void GameBoard::finalPhase(){

}

bool GameBoard::checkWinningCondition(){

}

void GameBoard::print(){
	if(player==NULL){
		cout << " > Game Error: Game board not initialized. Terminating print..." << endl;
		return;
	}
	cout << "    Number of players: " << player_amount << endl;
	return;
}
