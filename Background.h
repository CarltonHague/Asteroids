#pragma once
#include "Game_Object.h"
// class for managing the background inherits from the game object class
class Background : public Game_Object
{
public:
	Background(); // constructor 
	~Background() override; // deconstructor
	void initializeBackground(Texture& tex, float speed);


private:
	// private functions
	void setSpriteSpeed(float spriteSpeed); // function to set the sprite speed
	void centerAndScaleSprite(RenderWindow& window);// function to center and scale sprites
	
	// overide functions
	void updateObject(Time deltaTime, RenderWindow& window) override;  // function to update the object with delta time 
	void renderObject(RenderWindow& window) override; // function to draw the object
	void initializeObject(RenderWindow& window) override; // function to initialize the object such as scaling and placement on screen

	// background vairables
	Sprite backgroundSprite; // background sprite
	IntRect backgroundSpriteRect; // the intRect for the background sprite
	float spriteSpeed = 0.f; // the speed at which the sprite scrolls
	float scrollOffset = 0.f; // vairable for storing the scroll offset
};

