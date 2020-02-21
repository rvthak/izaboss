#ifndef INPUT
#define INPUT

#include <string>

unsigned int choosefrom(unsigned int n);	// Reads an int in [1, n] and returns it
bool getDesision(const std::string msg);	// Ask question written in msg and return 1/0 as an y/n answer
void pause();								// Pauses the execution of the program until user presses '\n'

#endif