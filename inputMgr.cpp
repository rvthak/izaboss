#include <limits>
#include <iostream>
#include "inputMgr.hpp"

using namespace std;

// returns int in [1, n]
unsigned int choosefrom(unsigned int n){
	cout << " > Type a number in [1, " << n << "]" << endl;
	unsigned int input;
	cout << " ";
	cin >> input;
	if (cin.fail()){
    	cin.clear(); 
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	while(input<1 || input>n){
		cout << " > Type a number in [1, " << n << "]" << endl;
		cout << " ";
		cin >> input;
		if (cin.fail()){ // in case the user gives wrong input
    		cin.clear(); 
    		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	cin.get(); // get the remaining \n left from >> operator to keep the buffer safe
	return input;
}

bool getDesision(const string msg){
	string str;
	cout << msg << endl;
	
	while(1){
		cout << " ";
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