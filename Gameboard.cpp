#include "GameBoard.hpp"

using namespace std;

void swap(int *x, int *y){  
    int temp = *x;
    *x = *y;
  	*y = temp;
}
void sort(int *buf, unsigned int *val, int n){   
    for (int i=0; i<n-1; i++){
    	for (int j=0; j<n-i-1; j++){
    		if (val[j] > val[j+1]){
    			swap(&val[j], &val[j+1]);
    			swap(&buf[j], &buf[j+1]);
    		} 
    	}
    }
}


GameBoard::GameBoard(){
	player=NULL;
}
GameBoard::~GameBoard(){
	if(player!=NULL){ delete[] player; }
	if(buf!=NULL){ delete[] buf; }
}


void GameBoard::initializeGameBoard(unsigned int playerNo){
	// Prepare the board for a game by creating the players
	if(playerNo>1&&playerNo<9){	// Check the player number is in the set range
		player_amount=playerNo;
		player=new Player[player_amount];

		// Players Created => Their honour can't change during the game so we sort
		// so we "sort the player array" to make playing in each turn easier
		buf=new int[player_amount];	// in this array we store the players positions sorted
		unsigned int *bufval=new int[player_amount];	// this array has their honour values stored (used for sorting)
		
		// We pass the initial values to both arrays
		for (int i=0; i<player_amount; i++){
			buf[i]=i;
	    	bufval[i]=player[i].getHonour();
	    }
	    // sort the buf according to the bufval values
	    sort(buf, bufval, player_amount);
	    delete []bufval;
		cout << " > Game board initialized succesfully!" << endl;
	}
	else{
		cout << " > Parameter Error: Player Number outside bounds." << endl;
		cout << " > Game board initialization failed! Please try again with different values" << endl;
	}
	return;
}
void GameBoard::printGameStatistics(){
	if(player==NULL){
		cout << " > Game Error: Game board not initialized. Terminating print..." << endl;
		return;
	}
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
	for(int i=0; i<player_amount; i++){
    	player[i].untapEverything();
    	player[i].drawFateCard();
  	 	player[i].revealProvinces();
    	player[i].printHand();
    	player[i].printProvinces();
    }
}
void GameBoard::equipPhase(){
	for(int i=0; i<player_amount; i++){
		
    }
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
