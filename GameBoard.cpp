#include <cstdlib>
#include "ui.hpp"
#include "inputMgr.hpp"
#include "GameBoard.hpp"
#include "TypeConverter.hpp"

using namespace std;

void SplashScreen2();

void swap(unsigned int *x, unsigned int *y){  
    unsigned int temp = *x;
    *x = *y;
  	*y = temp;
}
void sortPlayers(unsigned int *buf, unsigned int *val, int n){   
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
		for (unsigned int i=0; i<player_amount; i++){
			buf[i]=i;
	    		bufval[i]=player[i].getHonour();
	    	}
		// sort the buf according to the bufval values
		sortPlayers(buf, bufval, player_amount);
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
	cout << "   Player\tProvinces\tAttack\t\tDefence\t\tCurrent Income\t\tHoldings" << endl;
	for(unsigned int j=0; j<player_amount; j++){
		cout << " " << j+1 << ". Player " << j+1 << ": "
		<< "\t    " << player[buf[j]].GetProvinceAmount()
		<< "\t\t   "<< player[buf[j]].getPlayerAttack()
		<< "\t\t   "<< player[buf[j]].getPlayerDefence()
		<< "\t\t      "<< player[buf[j]].getMoney()
		<< "\t\t  "<< player[buf[j]].HoldingCardsNo()
		<< endl;
	}
}
void GameBoard::print(){
	if(player==NULL){
		cout << " > Game Error: Game board not initialized. Terminating print..." << endl;
		return;
	}
	cout << "	- Number of players: " << player_amount << endl;
	return;
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
		if(!running){break;}
		economyPhase();
		finalPhase();
	}
	return;
}

//=====================================================

void GameBoard::startingPhase(){
    #ifndef UI
	cout << " ================================================ " << endl;
	cout << "                   Starting Phase                 " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){
		#ifdef UI
		uiClear();
		cout << " ================================================ " << endl;
		cout << "                   Starting Phase                 " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;
    	player[buf[i]].untapEverything();
    	player[buf[i]].drawFateCard();
  	 	player[buf[i]].revealProvinces();
  	 	cout << endl;
    	player[buf[i]].printHand();
    	cout << endl;
    	player[buf[i]].printProvinces();
    	cout << endl;
    	#ifdef UI
    	cout << " > Phase ended for Player " << i+1 << " : Press Enter key to continue" << endl;
		pause();
		#endif
    }
}
void GameBoard::equipPhase(){
	#ifndef UI
	cout << " ================================================ " << endl;
	cout << "                    Equip Phase                   " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){
		#ifdef UI
		uiClear();
		cout << " ================================================ " << endl;
		cout << "                    Equip Phase                   " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;
		if(player[buf[i]].hasArmy()){ // if the player has army
			
			// Print his hand and army to allow him to choose his next move
			player[buf[i]].printHand();
			cout << " ================================================ " << endl;
			player[buf[i]].printArmy();

			// Print player's money
			cout << endl << " ($) Player money: " << player[buf[i]].getMoney() << endl << endl;

			while(getDesision(" > Do you want continue on transactions(y) or pass(n)? (y/n)")){
				// Check if he has any cards in his hand to use
				if(player[buf[i]].HandCardsNo()==0){
					cout<<"You don't have any cards on your hand!"<<endl;
					break;
				}
				
				// Get user input for the requested move
				cout << " > Please choose a card from your hand:" << endl;
				unsigned int handCard = choosefrom(player[buf[i]].HandCardsNo());

				cout << " > Please choose a card from your Army:" << endl;
				unsigned int armyCard = choosefrom(player[buf[i]].ArmyCardsNo());

				if( player[buf[i]].getMoney() >= player[buf[i]].GetHandCardCost(handCard) ){
					if( player[buf[i]].GetArmyMemberHonour(armyCard) >= player[buf[i]].GetHandMemberHonour(handCard) ){
						if( player[buf[i]].CheckPersonalityCapacity(armyCard, handCard) ){
							player[buf[i]].buyAndAssign(handCard, armyCard); // remember to tap the according cards
						}
						else{
							cout << " This personality already has reached its max capacity for that card type." << endl;
						}	
					}
					else{
						cout << " > Can't move on with the process. Not enough personality honour." << endl;
						cout << " He is a disgrace to our family" << endl;
					}	
				}
				else{
					cout << " > Can't move on with the process. Not enough money." << endl;
					cout << " Get rich and come back you little pleb" << endl;
				}

				#ifdef UI
				cout << " > Press Enter key to continue" << endl;
				pause();
				uiClear();
				cout << " ================================================ " << endl;
				cout << "                    Equip Phase                   " << endl;
				cout << " ================================================ " << endl;
				cout << endl << " > Player " << i+1 << "'s turn: " << endl;
				#endif

				// Print his hand and army to allow him to choose his next move
				player[buf[i]].printHand();
				player[buf[i]].printArmy();

				// Print player's money
				cout << " ($) Player money: " << player[buf[i]].getMoney() << endl << endl;
			}
    	}
    	else{
    		cout << " > Player has no army can't do any transaction." << endl;
    	}
    	#ifdef UI
    	cout << " > Phase ended for Player " << i+1 << " : Press Enter key to continue" << endl;
		pause();
		#endif
    }
}
void GameBoard::battlePhase(){
	bool flag;
	int k;
	#ifndef UI
	cout << " ================================================ " << endl;
	cout << "                   Battle Phase                   " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){	// for each player in the correct order
		flag=0;
		#ifdef UI
		uiClear();
		cout << " ================================================ " << endl;
		cout << "                   Battle Phase                   " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;
		if(player[buf[i]].hasArmy()){ 		// check if he has an army
			

			// ======= Stage 1 =======
			// Let the player decide which of his army cards does he wants tapped and safe
			#ifdef UI
			uiClear();
			#endif
			cout << "\t\t~-~ War Preparations ~-~" << endl << endl;
			cout << " > Available Player " << i+1 << " Army:" << endl;
			player[buf[i]].printTapArmy();	// Show the player his army + tap status

			while( getDesision(" > Do you want to tap any/more of your army members to leave them aside? (y/n)") ){
				cout << " > Which one of your army members do you want to tap?" << endl;
				unsigned int armyCard = choosefrom(player[buf[i]].ArmyCardsNo());
				
				if(player[buf[i]].TapArmyCard(armyCard)){
					cout<<" (!) This card is already tapped"<<endl;
					cout << " > Press Enter key to continue..." << endl;
					pause();
				}

				#ifdef UI
				uiClear();
				cout << "\t\t~-~ War Preparations ~-~" << endl << endl;
				cout << " > Available Player " << i+1 << " Army:" << endl;
				#endif

				player[buf[i]].printTapArmy();
			}


			// ======= Stage 2 =======
			// Let the player choose his attack/defense force soldiers
			#ifdef UI
			uiClear();
			#endif
			cout << "\t\t~-~ War Preparations ~-~" << endl << endl;
			cout << " > Available Player " << i+1 << " Army:" << endl;
			cout << " > Choose soldiers for your Attack force. The remaining troops " << endl;
			cout << "   will stay behind to defend our homes:" << endl;
			
			if(player[buf[i]].printUntappedArmy()){
				cout << " (!) No soldiers ready to battle left. Moving on..." << endl;
			}
			else{
				while( getDesision(" > Do you want to use any/more soldier to perform an attack? (y/n)") ){
					flag=1;
					if(!player[buf[i]].hasArmy()){
						cout << " > No Army left to lead to battle. Moving on..." << endl;
						break;
					}
					cout << " > Which one of your army members do you want to add to your attack force?" << endl;
					unsigned int sol = choosefrom(player[buf[i]].ActiveArmyCardsNo());
					player[buf[i]].AddToAttackForce(sol);

					#ifdef UI
					uiClear();
					cout << "\t\t~-~ War Preparations ~-~" << endl << endl;
					cout << " > Available Player " << i+1 << " Army:" << endl;
					cout << " > Choose soldiers for your Attack force. The remaining troops " << endl;
					cout << "   will stay behind to defend our homes:" << endl;
					#endif

					if(player[buf[i]].printUntappedArmy()){
						cout << endl << " (!) No soldiers ready to battle left. Moving on..." << endl;
						cout << " > Press Enter key to continue..." << endl;
						pause();
						break;
					}
				}
			}

			// ======= Stage 2 =======
			// Actual Attack
			while(flag){ // Player Selected at least one soldier for attack => Attack possible
				#ifdef UI
				uiClear();
				#endif
				cout << endl << "\t\t> Army Ready < " << endl;
				cout << "\t    <> ------ WAR ------ <> " << endl << endl;
				cout << " > Total player attack: " << player[buf[i]].getPlayerAttack() << endl << endl;

				while(1){
					if( getDesision(" > Do you want to perform an attack? (y/n)") ){
						// Print the available players to attack
						cout << endl << " > Choose a player to attack:" << endl;
						cout << "   _Player_\tProvinces\tDefence\t    Income" << endl;
						k=0;
						for(unsigned int j=0; j<player_amount; j++){
							if(j!=i){ // we dont print the current player
								k++;
								cout << " " << k << ". Player " << j+1 << ": ";
								cout << "\t    " << player[buf[j]].GetProvinceAmount();
								cout << "\t\t   " << player[buf[j]].getPlayerDefence();
								cout << "\t      " << player[buf[j]].getMoney();
								cout << endl;
							}
						}

						// let him choose his attack target
						cout << endl << " > Which one of the available players do you want to attack?" << endl;
						unsigned int target = choosefrom(player_amount-1);
						if(target>=i){ target++; }

						// let him spectate the target's provinces and choose a province
						#ifdef UI
						uiClear();
						#endif
						cout << " > Targeting Player " << target << ":" << endl << endl;
						player[buf[target]].printProvinces();
						cout << endl;
						player[buf[target]].printArmy();
						cout << endl;
						unsigned int tmp=player[buf[target]].GetProvinceAmount();
						cout << " > Which one of the available provinces do you want to attack?" << endl;
						cout << " - Type " << tmp+1 << " to go back if you change your mind" << endl;
						unsigned int targetprov = choosefrom(tmp+1);
						if(targetprov==tmp+1){
							cout << " Going back..." << endl;
							cout << " > Press Enter key to continue" << endl;
							pause();
							break;
						}
						else{
							cout << endl << "\t\t<><><><> ATTACK <><><><>" << endl << endl;
							player[buf[i]].attack(player[buf[target]], targetprov); // remember to print the attack results
							if( checkWinningCondition(i) ){ // exit if someone wins
								#ifdef UI
								uiClear();
								#endif
								cout << endl << endl << "\t\t> Player " << i+1 << " WON! < " << endl;
								#ifdef UI
						    	SplashScreen2();
						    	cout << endl << " > Press Enter key to continue" << endl;
						    	pause();
								#endif
								return; 
							}
							flag=0;
							break;
						}
					}
					else{
						cout << " (!) No attack performed" << endl;
						player[buf[i]].returnHome();
						flag=0;
						break;
					}
				}
			}
			
		}
		else{
    		cout << " > Player has no army. He is unable to battle." << endl;
    	}
    	#ifdef UI
    	cout << " > Phase ended for Player " << i+1 << " : Press Enter key to continue" << endl;
    	pause();
		#endif
	}
}
void GameBoard::economyPhase(){
	#ifndef UI
	cout << " ================================================ " << endl;
	cout << "                   Economy Phase                  " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){ // !!! each player can buy only one card in this phase
		#ifdef UI
		uiClear();
		cout << " ================================================ " << endl;
		cout << "                   Economy Phase                  " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;	
		while(getDesision(" > Do you want continue on transactions(y) or pass(n)? (y/n)")){
			// Print his army and holdings
			player[buf[i]].printArmy();
			cout << endl;
			player[buf[i]].printHoldings();
			cout << endl;
			// Then print the provinces he can choose from
			player[buf[i]].printProvinces();
			cout << endl;

			// Print player's money
			cout << " ($) Player money: " << player[buf[i]].getMoney() << endl << endl;

			unsigned int tmp=player[buf[i]].GetProvinceAmount();
			cout << " > Choose one of the available options:" << endl;
			cout << " - Province number to choose it [1, " << tmp << "]" << endl;
			
			unsigned int choice=choosefrom(tmp);

			if( player[buf[i]].getMoney() >= player[buf[i]].GetProvinceCardCost(choice) ){
				player[buf[i]].buyAndUse(choice);
				cout << " ($) Transaction succesful!" << endl;
			}
			else{
				#ifdef UI
		    		pause();
				#endif
				cout << " > Not enough money please try something else or pass" << endl;
			}
		}
		#ifdef UI
    	cout << " > Phase Ended for Player " << i+1 << " : Press Enter key to continue" << endl;
		pause();
		#endif
	}
}
void GameBoard::finalPhase(){
	#ifndef UI
	cout << " ================================================ " << endl;
	cout << "                    Final Phase                   " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){
		#ifdef UI
		uiClear();
		cout << " ================================================ " << endl;
		cout << "                    Final Phase                   " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;
		// Discard excess hand cards
		cout << " > Discarding extra hand cards if any.." << endl;
		player[buf[i]].discardSurplusFateCards();
		cout << endl;
		player[buf[i]].printHand();
		cout << endl;
		player[buf[i]].printProvinces();
		cout << endl;
		player[buf[i]].printArena();
		cout << endl;
		player[buf[i]].printHoldings();
		cout << endl;
		#ifdef UI
    	cout << " > Phase ended for Player " << i+1 << " : Press Enter key to continue" << endl;	
    	pause();
		#endif
	}
	#ifdef UI
	uiClear();
	#endif
	cout << " > Round ended: Printing Game Statistics..." << endl << endl;
	printGameStatistics();
	cout << "             Game statistics printed " << endl;
	cout << " ================================================ " << endl;
	cout << "                   End of Round                   " << endl;
	cout << " ================================================ " << endl;
	#ifdef UI
	cout << " > Press Enter key to start next game Round:" << endl;
	pause();
	#endif
}

bool GameBoard::checkWinningCondition(unsigned int i){
	if( player[buf[i]].hasProvinces()){
		bool flag=1;
		for(unsigned int j=0; j<player_amount; j++){
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

void SplashScreen2(){
	uiClear();
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

	cout << "\t\t  Press Enter key to continue" << endl;
	pause();
	uiClear();
}
