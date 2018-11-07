// Support Code written by Michael D. Shah
// Last Updated: 1/21/17
// Please do not redistribute without asking permission.

// Functionality that we created
#include "SDLGraphicsProgram.h"
#include <iostream>

int main(int argc, char** argv){

	std::cout << "(main.cpp) Beginning Intitialization\n";
	// Create an instance of an object for a SDLGraphicsProgram
	SDLGraphicsProgram mySDLGraphicsProgram(1280,720);
	// Run our program forever
	mySDLGraphicsProgram.loop();
	// When our program ends, it will exit scope, the
	// destructor will then be called and clean up the program.
	return 0;
}
