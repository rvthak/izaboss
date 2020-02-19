#include <limits>
#include <iostream>
#include "inputMgr.hpp"

using namespace std;

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
	return input;
}

bool getDesision(const string msg){
	string str;
	cout << msg << endl;
	cin >> str;
	while(1){
		if(str=="y"){
			return 1;
		}
		else if(str=="n"){
			return 0;
		}
		else{
			cout << " > Wrong input try again: (y/n)" << endl;
			cin >> str;
		}
	}
}
