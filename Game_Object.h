#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
// Vitual class for inhertence by game objects

class Game_Object
{
public:
	
	bool isActive = false; // default is not active 


	// regular functions
	bool getIsActive() { return this->isActive; } // function to see if the object is active or not for rendering and collision
	void setToActive() { this->isActive = true; } // function to set the current active state to true
	void deactivate() { this->isActive = false; }// function to set the current active state to false
	

	// virtual functions
	virtual void updateObject(Time deltaTime, RenderWindow &window) = 0;  // function to update the object with delta time 
	virtual void renderObject(RenderWindow &window) = 0; // function to draw the object 
	virtual void initializeObject(RenderWindow &window) = 0; // function to initialize the object such as scaling and placement on screen
	virtual ~Game_Object() = default; // deconstructor
   
	
};

