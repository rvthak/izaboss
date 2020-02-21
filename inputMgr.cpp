#include <limits>
#include <iostream>
#include "inputMgr.hpp"

using namespace std;

// returns int in [1, n]
unsigned int choosefrom(unsigned int n){
	cout << " > Type a number in [1, " << n << "]" << endl;
	unsigned int input;
	cin >> input;
	if (cin.fail()){
    	cin.clear(); 
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	while(input<1 || input>n){
		cout << " > Type a number in [1, " << n << "]" << endl;
		cin >> input;
		if (cin.fail()){
    		cin.clear(); 
    		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.get();
	return input;
}

bool getDesision(const string msg){
	string str;
	cout << msg << endl;
	
	while(1){
		cin >> str;

		if (cin.fail()){
	    	cin.clear(); 
	    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    	cout << " > Wrong input try again: (y/n)" << endl;
    	}
		else if(str=="y"){
			cin.get();
			return 1;
		}
		else if(str=="n"){
			cin.get();
			return 0;
		}
		else{
			cout << " > Wrong input try again: (y/n)" << endl;
		}
	}
}

void pause(){
	cin.get();
}