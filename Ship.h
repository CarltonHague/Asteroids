#pragma once
#include "Game_Object.h"
class Ship : public Game_Object
{
public:
     Ship(Texture& tex); //  constructor 
	 ~Ship() override; // deconstructor 




private:
	// private functions
	 void scaleAndCenterOrigin(RenderWindow& window); // function to scale the ship and set the origin to the center
	 void updateDirection();
	 void shipWindowBoundsCollision(RenderWindow& window); // function that keeps the ship within the bounds of the current window

	 // override functions 
	 void initializeObject(RenderWindow& window) override; // function to overide the virtual base class function 
	 void renderObject(RenderWindow& window) override; // function to overide the virtual base class function and render the ship to the window
	void updateObject(Time deltatime, RenderWindow& window) override;// overide update function
	Game_Object::type getType() override; // function to return that the object is a ship
	FloatRect getBounds() override; // get the bounds of the ship 
	IntRect getTextureRect() override; // get the texture rect of the ship
	void setTextureRect(IntRect rect) override; // set the texture rect of the ship sprite
	void setPosition(Vector2f) override; // set the position of the ship
	Vector2f getPosition() override; // gets the position of the ship

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
	int shipHealth = MAX_HP; // set to Max hp on start
	const int MAX_HP = 100;
	const float SHIP_ROTATION = 90 ;

};

