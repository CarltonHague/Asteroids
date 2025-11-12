#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include"Background.h"
#include"Ship.h"
#include "Asteroids.h"
using namespace sf;
// class containing all the game logic and constant vairbles


class Game
{
public:
	Game(); //constructor 
	void run();
	void initializeGame();
private:

};

