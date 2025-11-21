#pragma once
#include "Game_Object.h"
#include "Collidable_Object.h"
class Ship : public Game_Object , public Collidable_Object
{
public:
     Ship(); //  constructor 
	 ~Ship() override; // deconstructor 
	 void setTexture(Texture& tex); // function to set the texture of the ship
	 void updateDirection(bool up, bool down, bool left, bool right); // updates the ships direction based on user input
	 Vector2f getPosition(); // get the current location of the ship for shooting
	 int getShipHealth(); // returns the current health of the ship
private:
	// private functions
	 void scaleAndCenterOrigin(RenderWindow& window); // function to scale the ship and set the origin to the center
	 void shipWindowBoundsCollision(RenderWindow& window, Time dt); // function that keeps the ship within the bounds of the current window
	 void shipTakeDamge(int damageAmount); // function for the ship to take damage
	 void moveShip(Time dt); // function to move the ship based on delta time and the ships current direction 
	 // override functions 
	 void initializeObject(RenderWindow& window) override; // function to overide the virtual base class function 
	 void renderObject(RenderWindow& window) override; // function to overide the virtual base class function and render the ship to the window
	void updateObject(Time deltatime, RenderWindow& window) override;// overide update function
	void collisionOutcome(bool collisionFlag,type) override; // the outcome of the ship getting hit

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
	const int SMALL_ASTEROID_DAMAGE = 5, LARGE_ASTEROID_DAMAGE = 15, NORMAL_ASTEROID_DAMAGE = 10;

	// the speed at which the ship handles
	const float SHIP_ACCELERATION = 300.f, SHIP_DECELETAION = 50.f, SHIP_TERMINAL_VELOCITY = 200.f; 
	// acceleration is how fast the ship speeds up and changes direction 
	// deceleration is how fast the ship slows down to a standstill when no key inputs are pressed
	// terminal velocity is how fast the ship is allowed to move overall 
	// play around with the 3 values to find a ship speed that feels best 

	const float SHIP_SCALE = 20.f ;
	int shipHealth = 0;
	const int MAX_HP = 100;
	const float SHIP_ROTATION = 90 ;
	const float HITBOX_SCALE = 0.45F; // used to scale the circle hit box by around 45% of the original size

};

