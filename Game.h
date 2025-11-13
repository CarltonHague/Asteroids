#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include"Background.h"
#include"Ship.h"
#include "Asteroids.h"
#include "cassert"
#include "memory"

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
	void initializeTextures(); // creates the 
	void initializeFontAndText();
	void initializeGameObjects(); // calls initialize on all the game objects in the array
	void initializeShip(); // creates a ship object using the texture
	void pollEvents(); // Function to poll window events 
	void updateGame(); // Function to update the game
	void updateGameObjects(); // function to update all the game objects in the array using overiden virtual function calls
	void renderGame(); // Function to render the game objects
	void renderGameObjects();
	bool loadBackgroundTexture(const std::string& filename, Texture& texture); // function to load textures with repeating 
	bool loadTexture(const std::string& filename, Texture& texture); // function to load textures without repeating



	// Number of game Objects
	static const int MAX_BACKGROUND_LAYERS = 8, MAX_SHIPS = 1, MAX_ASTEROIDS = 32, MAX_BULLETS = 64;
	static const int TOTAL_GAME_OBJECTS = (MAX_BACKGROUND_LAYERS + MAX_SHIPS + MAX_ASTEROIDS + MAX_BULLETS);
	std::unique_ptr <Game_Object> allObjectsInGame[TOTAL_GAME_OBJECTS]; // An array of game object pointers for polymorphic function calls 
	// window vairables
	RenderWindow window;
	VideoMode video_mode;
	Vector2u window_size;
	const std::string GAME_TITLE = "Asteroids Game";
	const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
	


	// game logic vairables  
	Event gamePoller;
	Clock gameClock;
	Time deltaTime;
	enum gameState
	{
		STARTSCREEN,
		PLAYING,
		GAMEOVER
	};
	gameState currentGameState = STARTSCREEN;

	// textures and fonts 
	Texture BackgroudTextures[MAX_BACKGROUND_LAYERS];
	std::string backgroundFilePaths[MAX_BACKGROUND_LAYERS];
	Texture shipTexture;
	Texture bulletTexture;
	Texture AsteroidTexture;
	Font gameFont;

};

