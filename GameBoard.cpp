#include "GameBoard.hpp"
#include "inputMgr.hpp"
#include "TypeConverter.hpp"

using namespace std;

void swap(unsigned int *x, unsigned int *y){  
    unsigned int temp = *x;
    *x = *y;
  	*y = temp;
}
void sort(unsigned int *buf, unsigned int *val, int n){   
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
	running=0;
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
		buf=new unsigned int[player_amount];	// in this array we store the players positions sorted
		unsigned int *bufval=new unsigned int[player_amount];	// this array has their honour values stored (used for sorting)
		
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
	running=1;

	// Main game loop
	while(running){
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
	cout << " ================================================ " << endl;
	cout << "                   Starting Phase                 " << endl;
	cout << " ================================================ " << endl;
	for(int i=0; i<player_amount; i++){
		cout << endl << " > Player's " << i+1 << " turn: " << endl;
    	player[buf[i]].untapEverything();
    	player[buf[i]].drawFateCard();
  	 	player[buf[i]].revealProvinces();
    	player[buf[i]].printHand();
    	player[buf[i]].printProvinces();
    } 
}
void GameBoard::equipPhase(){
	cout << " ================================================ " << endl;
	cout << "                    Equip Phase                   " << endl;
	cout << " ================================================ " << endl;
	for(int i=0; i<player_amount; i++){
		cout << endl << " > Player's " << i+1 << " turn: " << endl;
		if(player[buf[i]].hasArmy()){ // if the player has army
			
			// Print his hand and army to allow him to choose his next move
			player[buf[i]].printHand();
			player[buf[i]].printArmy();

			// Print player's money
			cout << " > Player money: " << player[buf[i]].getMoney() << endl;

			while(getDesision(" > Do you want continue on transactions(y) or pass(n)? (y/n)")){
				// Get user input for the requested move
				cout << " > Please choose a card from your hand:" << endl;
				unsigned int handCard = choosefrom(player[buf[i]].HandCardsNo());

				cout << " > Please choose a card from your Army:" << endl;
				unsigned int armyCard = choosefrom(player[buf[i]].ArmyCardsNo());

				if( player[buf[i]].getMoney() >= player[buf[i]].GetHandCardCost(handCard) ){
					if( player[buf[i]].GetArmyMemberHonour(armyCard) >= player[buf[i]].GetHandMemberHonour(handCard) ){
						player[buf[i]].buyAndAssign(handCard, armyCard); // remember to tap the according cards
						cout << " Transaction succesful!" << endl;
					}
					else{
						cout << " > Can't move on with the process. Not enough personality honour." << endl;
						cout << " he is a disgrace to our family" << endl;
					}	
				}
				else{
					cout << " > Can't move on with the process. Not enough money." << endl;
					cout << " Get rich and come back you little pleb" << endl;
				}

				// Print his hand and army to allow him to choose his next move
				player[buf[i]].printHand();
				player[buf[i]].printArmy();

				// Print player's money
				cout << " > Player money: " << player[buf[i]].getMoney() << endl;
			}
    	}
    	else{
    		cout << " > Player has no army can't do any transaction." << endl;
    	}
    }
}
void GameBoard::battlePhase(){
	cout << " ================================================ " << endl;
	cout << "                   Battle Phase                   " << endl;
	cout << " ================================================ " << endl;
	for(int i=0; i<player_amount; i++){		// for each player in the correct order
		cout << endl << " > Player's " << i+1 << " turn: " << endl;
		if(player[buf[i]].hasArmy()){ 		// check if he has an army
			player[buf[i]].printTapArmy();	// Show the player his army + tap status

			cout << " --- War Preparations ---" << endl;

			// Let the player decide which of his army cards does he want tapped
			while( getDesision(" > Do you want to tap any/more of your army members to leave them aside? (y/n)") ){
				cout << " > Which one of your army members do you want to tap?" << endl;
				unsigned int armyCard = choosefrom(player[buf[i]].ArmyCardsNo());
				player[buf[i]].TapArmyCard(armyCard);
				player[buf[i]].printTapArmy();
			}

			// Let the player decide which of his army cards does he want for attack
			player[buf[i]].printUntappedArmy();
			while( getDesision(" > Which soldiers do you want to use for attack? (y/n)") ){
				cout << " > Which one of your army members do you want to tap?" << endl;
				unsigned int sol = choosefrom(player[buf[i]].ActiveArmyCardsNo());
				player[buf[i]].AddToAttackForce(sol);
				player[buf[i]].printUntappedArmy();
			}

			cout << " --- War --- " << endl;

			// Calculate player attack
			unsigned int attack=player[buf[i]].getPlayerAttack();

			while(1){
				if( getDesision(" > Do you want to perform an attack?") ){
					// Print the available players to attack
					cout << " > Choose a player to attack " << endl;
					for(int j=0; j<player_amount; j++){
						if(j!=i){ // we dont print the current player
							cout << " Player " << j+1 << endl;
							player[buf[j]].print();			
						}
					}

					// let him choose his attack
					cout << " > Which one of the available players do you want to attack?" << endl;
					unsigned int target = choosefrom(player_amount);
					while(target==i){
						cout << " > You cant attack yourself... " << endl;
						cout << " > Which one of the available players do you want to attack?" << endl;
						target = choosefrom(player_amount);
					}

					// let him choose his enemy's province-target
					player[buf[target]].printProvinces();
					player[buf[target]].printArmy();
					int tmp=player[buf[target]].GetProvinceAmount();
					cout << " > Which one of the available provinces do you want to attack?" << endl;
					cout << " - Type " << tmp+1 << " to go back if you change your mind" << endl;
					unsigned int targetprov = choosefrom(tmp+1);
					if(target==tmp+1){
						cout << " Going back..." << endl;
						break;
					}
					else{
						cout << " > ATTACK " << endl;
						player[buf[i]].attack(player[buf[target]], targetprov); // remember to print the attack results
						return;
					}
				}
				else{
					cout << " > No attack perform" << endl;
					break;
				}
			}
		}
		else{
    		cout << " > Player has no army. He is unable to battle." << endl;
    	}
	}
}
void GameBoard::economyPhase(){
	cout << " ================================================ " << endl;
	cout << "                   Economy Phase                  " << endl;
	cout << " ================================================ " << endl;
	for(int i=0; i<player_amount; i++){ // !!! each player can buy only one card in this phase
		cout << endl << " > Player's " << i+1 << " turn: " << endl;	
		while(1){
			// Print his army and holdings
			player[buf[i]].printArmy();
			player[buf[i]].printHoldings();
			// Then print the provinces he can choose from
			player[buf[i]].printProvinces();

			unsigned int tmp=player[buf[i]].GetProvinceAmount();
			cout << " > Choose one of the available options:" << endl;
			cout << " - Province number to choose it [1, " << tmp << "]" << endl;
			cout << " - Type " << tmp+1 << " to pass this phase " << endl;
			unsigned int choice=choosefrom(tmp+1);
			if(choice!=tmp+1){
				if( player[buf[i]].getMoney() => player[buf[i]].GetProvinceCardCost(choice) ){
					player[buf[i]].buyAndUse(choice);
					cout << " > Transaction successful" << endl;
					break;
				}
				else{
					cout << " > Not enough money please try again" << endl;
				}
			}
			else{
				cout << " > Phase passed!" << endl;
				break;
			}
		}
	}
}
void GameBoard::finalPhase(){
	cout << " ================================================ " << endl;
	cout << "                    Final Phase                   " << endl;
	cout << " ================================================ " << endl;
	for(int i=0; i<player_amount; i++){
		cout << endl << " > Player's " << i+1 << " turn: " << endl;
		// Discard excess hand cards
		player[buf[i]].discardSurplusFateCards();
		player[buf[i]].printHand();
		player[buf[i]].printProvinces();
		player[buf[i]].printArena();
		player[buf[i]].printHoldings();
		if( checkWinningCondition(i) ){ // exit if someone wins
			cout << "    > Player " << i+1 << " WON! < " << endl;
			break; 
		} 
	}
	printGameStatistics();
}

bool GameBoard::checkWinningCondition(unsigned int i){
	if( player[buf[i]].hasProvinces()){
		bool flag=1;
		for(int j=0; j<player_amount; j++){
			if(j!=i){ // dont check the current player
				if( player[buf[j]].hasProvinces() ){
					flag=0;
					break;
				}
			}
		}

		if(flag){
			running=0;
			return 1;
		}
	}
	return 0;
}

void GameBoard::print(){
	if(player==NULL){
		cout << " > Game Error: Game board not initialized. Terminating print..." << endl;
		return;
	}
	cout << "    Number of players: " << player_amount << endl;
	return;
}