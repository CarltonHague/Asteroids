

#include <iostream>
#include"Game.h"
#include <ctime>

int main()
{
	srand(time(0));
	Game game; // create the game object
	game.initialize(); // sets the game fonts textures and initializes objects
	game.run(); // run the main update and render loop of the game 

   
}

