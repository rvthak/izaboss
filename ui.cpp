#include <cstdlib>
#include <string.h>
#include <iostream>
#include "ui.hpp"

using namespace std;

static char *param=NULL;

void uiInit(){

	#ifdef _WIN32
	cout << "WINDOWS" << endl;
	param=new char[4];
	strcpy(param, "cls");
	#endif

	#ifdef linux
	cout << "LINUX" << endl;
	param=new char[6];
	strcpy(param, "clear");
	#endif
}


void uiClear(){
	// if the ui is uninitialized
	if(param==NULL){
		// initialize it to work in the correct operating system
		uiInit();
	}
	// make the system call to clear the screen
	system(param);
}

void uiTerminate(){
	if(param!=NULL){ delete[] param; }
}
