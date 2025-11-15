#pragma once
#include "Game_Object.h"
class Ship : public Game_Object
{
public:
     Ship(); //  constructor 
	 ~Ship() override; // deconstructor 
	 void setTexture(Texture& tex); // function to set the texture of the ship
	 void updateDirection(bool up, bool down, bool left, bool right); // updates the ships direction based on user input
	 Vector2f getPosition(); // get the current location of the ship for shooting

private:
	// private functions
	 void scaleAndCenterOrigin(RenderWindow& window); // function to scale the ship and set the origin to the center
	 void shipWindowBoundsCollision(RenderWindow& window); // function that keeps the ship within the bounds of the current window
	 

	 // override functions 
	 void initializeObject(RenderWindow& window) override; // function to overide the virtual base class function 
	 void renderObject(RenderWindow& window) override; // function to overide the virtual base class function and render the ship to the window
	void updateObject(Time deltatime, RenderWindow& window) override;// overide update function
	

	// vairables for the ship
	Sprite shipSprite;
	Vector2f shipPosition;
	Vector2f shipVelocity;
	IntRect shipRect;
	enum Direction
	{
		NORTH,
		NORTH_EAST,
		SOUTH_EAST,
		SOUTH,
		SOUTH_WEST,
		WEST,
		NORTH_WEST,
		EAST,
		STOPPED
	};
	Direction shipDirection = STOPPED; // default is stopped
	
	const float SHIP_SPEED = 250.f;
	const float SHIP_SCALE = 20.f ;
	int shipHealth = 0;
	const int MAX_HP = 100;
	const float SHIP_ROTATION = 90 ;

};

