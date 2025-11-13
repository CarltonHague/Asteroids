#pragma once
#include "Game_Object.h"
class Ship : public Game_Object
{
public:
     Ship(Texture& tex); //  constructor 
	




private:
	// private functions
     void initializeObject(RenderWindow& window) override; // function to overide the virtual base class function 
	 void scaleAndCenterOrigin(RenderWindow& window); // function to scale the ship and set the origin to the center
	 void renderObject(RenderWindow& window) override; // function to overide the virtual base class function and render the ship to the window
	 void updateDirection();
	 void updateObject(Time deltatime, RenderWindow& window) override; // overide update function
	 void shipWindowBoundsCollision(RenderWindow& window); // function that keeps the ship within the bounds of the current window
	Game_Object::type getType() override; // function to return that the object is a ship
	FloatRect getBounds() override;

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
	Direction shipDirection;
	
	const float SHIP_SPEED = 250.f;
	const float SHIP_SCALE = 20.f ;
	int shipHealth;
	const int MAX_HP = 100;
	const float SHIP_ROTATION = 90 ;

};

