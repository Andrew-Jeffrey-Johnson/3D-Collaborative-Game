<<<<<<< Updated upstream
/******************************************************************************
** File: main.cpp
** Project: 3D Collaborative Game
** Date Created: 4 July 2020
** Description: Holds the main function of the whole program
******************************************************************************/



#include "gameEngine.h"
#include <iostream>

using namespace std;

/******************************************************************************
** Function: main
** Description: This is the start of the entire program. 
** Parameters: int argc holds the number of arguments, char **argv holds the 
** string of characters that hold the arguments
** Pre-Conditions: None
** Post-Conditions: None
******************************************************************************/
#include "physicsTestKit.h"
using namespace std;
int main (int argc, char **argv) {
	GameEngine engine;
	bool success = engine.initialize();
	if (success) {
		engine.run();
	}
	else {
		cout << "Failed to initiallize game engine" << endl;
	}

	engine.shutdown();

	return 0;
}
=======

#define STB_IMAGE_IMPLEMENTATION // Required for stb_image.h (Only define once)

#include "game_engine.h"
#include "program_log.h"

int main (int argc, char **argv) {
	program_log("\n\nBegin Program");
	
	GameEngine engine;
	if(engine.initialize() == 0) {
		engine.game_loop();
		engine.deallocate();
	}

	return 0;
}

>>>>>>> Stashed changes
