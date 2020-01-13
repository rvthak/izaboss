#include <iostream>
#include "inputMgr.hpp"

using namespace std;

unsigned int choosefrom(unsigned int n){
	cout << " > Type a number in [1, " << n+1 << "]" << endl;
	unsigned int input;
	cin >> input;
	while(input<1 || input>n+1){
		cout << " > Type a number in [1, " << n+1 << "]" << endl;
		cin >> input;
	}
	return input-1;
}

bool getDesision(const string msg){
	string str;
	cout << msg << endl;
	cin >> str;
	while(1){
		if(str=="y"){
			return 1;
		}
		else if(str!="n"){
			return 0;
		}
		else{
			cout << " > Wrong input try again: (y/n)" << endl;
			cin >> str;
		}
	}
}
