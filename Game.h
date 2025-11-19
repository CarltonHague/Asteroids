#pragma once
#include "Bullet.h"
#include"Background.h"
#include"Ship.h"
#include "Asteroids.h"
#include "cassert"
#include "Input_Manager.h"
#include "Collision_Manager.h"
#include <sstream>


// game manager style class contains:  The main update loop 
//                                     Initialize functions 
//                                     Render loop 
//                                     Textures and fonts
//                                     Pools for game objects (ship, asteroids, bullets and backgrounds)
//                                     Game state Logic
//                                     RenderWindow vairables and object


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
	void initializeShip(); // initialize the  ship object using the texture
	void initializeBackgrounds(); // initialize the background objects using textures
	void initializeBullets(); // initialize the bullets objects textures and sets them to no active by default 
	void initializeAsteroids(); // initialize the asteroids in the pool and set to not active by default

	void pollEvents(); // Function to poll window events 

	void updateGame(); // Function to update the game 
	void updateGameObjects(); // function to update all the game objects in the array using overriden virtual function calls
	void updateBackground(); // update the background for startScreen and end game states
	void updatePlayerStats(); // updates the player health and score
	

	void renderGame(); // Function to render the game 
	void renderGameObjects(); // polymorphic call that renders all the game objects
	void renderStartScreen();
	void renderEndScreen();
	void renderPlayerStats();

	// Helper functions 
	bool loadBackgroundTexture(std::string& filename, Texture& texture); // function to load textures with repeating 
	bool loadTexture(const std::string& filename, Texture& texture); // function to load textures without repeating
	void addGameObjectToPointerArray(Game_Object * object); // adds the objet being passed into the function to the array for polymorphic update and rendering calls
	void addCollideableObjectToArray(Collidable_Object* cObject); // adds an object to the collision array for polymorphic collision calling
	void fireBullet(bool readyToFire); // fire a bullet using the input manager ready to fire bool
	void spawnAsteroid(); // spawns an asteroid on a fixed timer 

	// Number of game Objects
    static const int MAX_BACKGROUND_LAYERS = 8, MAX_SHIPS = 1, MAX_ASTEROIDS = 16, MAX_BULLETS = 32;
	static const int TOTAL_GAME_OBJECTS = (MAX_BACKGROUND_LAYERS + MAX_SHIPS + MAX_ASTEROIDS + MAX_BULLETS), COLLIDEABLE_OBJECTS = (MAX_SHIPS + MAX_ASTEROIDS + MAX_BULLETS);
   Game_Object * allObjectsInGame[TOTAL_GAME_OBJECTS] = { nullptr }; // An array of game object pointers for polymorphic function calls set to null by default
   Collidable_Object* allCollideableObjects[COLLIDEABLE_OBJECTS] = { nullptr }; // an array of collideable game objects for collision dectection calls  set to null by default 

	// an array of background speeds for moving the background sprites 0 is the furthest and 7 is the closest sprite
	const float backgroundSpeedArray[MAX_BACKGROUND_LAYERS]{ 10.f,35.f,45.f,45.f,60.f,160.f,160.f,240.f };

	// pools of objects for better cache coherence and refrencing
	Bullet bulletPool[MAX_BULLETS];
	Background backgroundPool[MAX_BACKGROUND_LAYERS];
	Asteroids asteroidPool[MAX_ASTEROIDS];
	Ship playerShip;

	// input manager object
	Input_Manager playerInput;

	// collision manager
	Collision_Manager collisionChecker;

	// window vairables
	RenderWindow window;
	VideoMode video_mode;
	Vector2u window_size;
	const std::string GAME_TITLE = "Asteroids Game";
	const int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
	
	// asteroid spawn timer (could be moved to a spawn handler class or struct in future updates) 
	const float ASTEROID_SPAWN_TIMER = 0.5f; // spawntimer in seconds 
	float asteroidTimerTracker = ASTEROID_SPAWN_TIMER; // set to spawn one on game start then should spawn one every time it reaches the spawn timer vairable
	const float ASTEROID_BUFFER = 76.5; // the buffer for spawning the asteroid to ensure it is always within the bounds of the screen

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
	int score = 0; // the score of the player

	// textures
	Texture BackgroudTextures[MAX_BACKGROUND_LAYERS];
	std::string backgroundFilePaths[MAX_BACKGROUND_LAYERS];
	Texture shipTexture;
	Texture bulletTexture;
	Texture AsteroidTexture;

	// text and fonts
	Font gameFont;
	Text startScreenText;
	Text gameOverText;
	Text playerHealthText;
	const std::string startScreenString = "WSAD or arrow keys to move Spacebar to fire\n                   Press enter to play!";
	std::stringstream playerHealthStream;
	std::stringstream sameOverStream;
	const int START_SIZE = 74, PLAYER_STATS_SIZE = 30, ENDING_SIZE = 84; // Size of the text
	const Vector2f playerStatsLocation = Vector2f(100, 40); // location of the player stats should be the top left of the screen 
	Vector2f centerOfTheScreenTextLocation = Vector2f(0.f,0.f); // the center of the screen for the other text objects on the star and end screen
};

