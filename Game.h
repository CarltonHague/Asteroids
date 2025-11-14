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
	void initializeTextures(); // function to load the textures from the file paths 
	void initializeFontAndText(); // function to load the font and set any game text
	void initializeGameObjects(); // calls initialize on all the game objects in the array
	void initializeShip(); // creates a ship object using the texture
	void initializeBackgrounds(); // creates the background objects using textures
	void initializeBullets(); // creates the bullets objects and sets them to no active by default 
	void pollEvents(); // Function to poll window events 
	void updateGame(); // Function to update the game
	void updateGameObjects(); // function to update all the game objects in the array using overriden virtual function calls
	void renderGame(); // Function to render the game objects
	void renderGameObjects();
	bool loadBackgroundTexture(std::string& filename, Texture& texture); // function to load textures with repeating 
	bool loadTexture(const std::string& filename, Texture& texture); // function to load textures without repeating
	void fireBullet(); // function to allow the player to shoot



	// Number of game Objects
	static const int MAX_BACKGROUND_LAYERS = 8, MAX_SHIPS = 1, MAX_ASTEROIDS = 16, MAX_BULLETS = 32;
	static const int TOTAL_GAME_OBJECTS = (MAX_BACKGROUND_LAYERS + MAX_SHIPS + MAX_ASTEROIDS + MAX_BULLETS);
	std::unique_ptr <Game_Object> allObjectsInGame[TOTAL_GAME_OBJECTS]; // An array of game object pointers for polymorphic function calls 

	// an array of background speeds for moving the background sprites 0 is the furthest and 7 is the closest sprite
	const float backgroundSpeedArray[MAX_BACKGROUND_LAYERS]{ 10.f,35.f,45.f,45.f,60.f,180.f,180.f,240.f };



	// window vairables
	RenderWindow window;
	VideoMode video_mode;
	Vector2u window_size;
	const std::string GAME_TITLE = "Asteroids Game";
	const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
	
	// vairables for shooting the ship 
	const float SHOOT_SPEED = 0.5f; // speed at which the ship can fire in seconds
	float bulletTimerTracker = 0.f;
	const float BULLET_SPEED = 200.f; //speed at which the bullets will travel
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

