#pragma once
#include "Game_Object.h"
#include"Collidable_Object.h"
class Asteroids : public Game_Object, public Collidable_Object
{
public:
	Asteroids(); // constructor 
	void resetAsteroid(); // function to reset the asteroid 
	void setTexture(Texture& tex); // set the texture of the sprite
	~Asteroids() override;  // deconstructor 
	void spawnAsteroid(float yPos, RenderWindow &window); // function to spawn an asteroid using the y position provided 
	int getScore(); // get the score from the asteroid

private:
	// private functions 
	void animateAsteroid(); // function to animate the asteroid using the texture rect
	void turnOffAsteroid(); // function to turn off the asteroid object from collision and render/update loops
	void turnOnAsteroid(); // function to activate the asteroid for updating and collision 
	void killAsteroid(); // function to reset the asteroid when killd and add score to counter

	// overide functions 
	void updateObject(Time deltaTime, RenderWindow& window) override;  // function to update the object with delta time 
	void renderObject(RenderWindow& window) override; // function to draw the object 
	void initializeObject(RenderWindow& window) override; // function to initialize the object such as scaling and placement on screen
	FloatRect getBounds() override; // overide for getting the bounds of the asteroid
	bool collisionCheck(FloatRect objectYouAreHitting) override; // checks to see if the asteroid is hitting something and returns either true or false
	void collisionOutcome(bool collisionFlag, type) override; // the outcome of the asteroid getting hit

	//vairables
	Sprite asteroidSprite;
	const float NORMAL_SPEED = -300.f, SMALL_SPEED = - 400, LARGE_SPEED = - 250; // Speeds for the asteroids ensure these are negative to allow for the asteroids to move towards the player
	Vector2f ASTEROID_MOVE_VECTOR = Vector2f(0, 0);
	const int SPRITE_SIZE = 102; // The size of the sprite on the sheet
	IntRect asteroidRect = IntRect(0, 0, this->SPRITE_SIZE, this->SPRITE_SIZE); // the int rect for the asteroid animation
	int asteroidHealth = 0;
	const int BULLET_DAMAGE = 5, LARGE_ASTEROID_HP = 15, SMALL_ASTEROID_HP = 5, NORMAL_ASTEROID_HP = 10; // Max hp for asteroid depending on size and bullets damage amount
	const int LARGE_SCORE = 10, NORMAL_SCORE = 5, SMALL_SCORE = 2; // The score for killing each asteroid type
	int scoreTracker = 0; // value for tracking the score 
	const float SMALL_SCALE = 0.5, LARGE_SCALE = 1.5, NORMAL_SCALE = 1; // scalers for changing the size of the asteroid 
	const float ANIMATION_SPEED = 0.16; // around 60 frames per second 
	float animationTracker = 0.f;
};

