#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include"Background.h"
#include"Ship.h"
#include "Asteroids.h"

// class containing all the game logic and constant vairbles


class Game
{
public:
	Game(); // constructor
	void run(); // main game loop
	void initialize(); // initialize game variables




private:
	// private functions
	void initializeWindow(); // Function to initialize the game window from the variables


	void pollEvents(); // Function to poll window events 
	void update(); // Function to update the game
	void renderGame(); // Function to render the game objects







	// window vairables
	RenderWindow window;
	VideoMode video_mode;
	Vector2u window_size;
	const std::string GAME_TITLE = "Asteroids Game";
	const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
	


	// game vairables  
	Event gamePoller;
	Clock gameClock;
	Time deltaTime;


};

