#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
// Vitual class for inhertence by game objects

class Game_Object
{
public:
	// enum for checking what kind of object it is 
	enum type
	{
		NONE,
		ASTEROID,
		BULLET,
		BACKGROUND,
		SHIP

	};
	type object_type = NONE; // default is NO type
	bool is_active = false; // default is not active 


	// regular functions
	bool getIsActive(); // function to see if the object is active or not for rendering and collision
	void setToActive(); // function to set the current active state to true
	void deactivate(); // function to set the current active state to false


	// virtual functions
	virtual void updateObject(Time deltaTime, RenderWindow &window) = 0;  // function to update the object with delta time 
	virtual void renderObject(RenderWindow &window) = 0; // function to draw the object
	virtual FloatRect getBounds() = 0; // function that returns the bounds of the object 
	virtual void initializeObject(RenderWindow &window) = 0; // function to initialize the object such as scaling and placement on screen
	virtual ~Game_Object() = default; // deconstructor
	virtual type getType() = 0; // function that returns the type of the object
	virtual IntRect getTextureRect() = 0; // function to get the texture rect of the object
	virtual void setTextureRect(IntRect rect) = 0; // function to set the texture rect of the object's sprite
	virtual Vector2f getPosition() = 0; // function to get the position of the game object on the screen
	virtual void setPosition(Vector2f) = 0; // function to set the position of the object
};

