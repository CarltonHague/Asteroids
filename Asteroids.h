#pragma once
#include "Game_Object.h"
class Asteroids : public Game_Object
{
public:
	Asteroids(); // constructor 
	void resetAsteroid(); // function to reset the asteroid 
	void setTexture(Texture& tex); // set the texture of the sprite
	~Asteroids() override;  // deconstructor 

private:
	// private functions 
	void animateAsteroid(); // function to animate the asteroid using the texture rect
	
	

	// overide functions 
	void updateObject(Time deltaTime, RenderWindow& window) override;  // function to update the object with delta time 
	void renderObject(RenderWindow& window) override; // function to draw the object 
	void initializeObject(RenderWindow& window) override; // function to initialize the object such as scaling and placement on screen
	

	//vairables
	Sprite asteroidSprite;
	const float ASTEROID_SPEED = -100.f; // ensure that this is negative so the asteroids spawn and move towards the player from the right of the screen
	const Vector2f ASTEROID_MOVE_VECTOR = Vector2f(ASTEROID_SPEED, 0);
	const int SPRITE_SIZE = 128; // The size of the sprite on the sheet
	IntRect asteroidRect = IntRect(0, 0, this->SPRITE_SIZE, this->SPRITE_SIZE); // the int rect for the asteroid animation


};

