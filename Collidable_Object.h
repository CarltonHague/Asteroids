#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

// virtual parent class for objects the are collidable and need collision checking 

class Collidable_Object
{
public:

	// enum for checking what kind of object it is 
	enum type
	{
		NONE,
		NORMAL_ASTEROID,
		LARGE_ASTEROID,
		SMALL_ASTEROID,
		BULLET,
		SHIP

	};


	bool isCollideable = false; // bool for tracking if it's currently collideable
	bool getIsCollideable() { return this->isCollideable; } // returns the is collideable bool
	void setCollideable() { this->isCollideable = true; } // sets the bool to true
	void notCollideable() { this->isCollideable = false; } // sets the bool to false



	type object_type = NONE; // default is NONE type

	type getType() { return object_type; }; // function that returns the type of collideable object it is 

	// virtual functions 
	virtual FloatRect getBounds() = 0; // function to get the bounds of the object
	virtual bool collisionCheck(FloatRect objectYouAreHitting) = 0; // check to see if you hit that object
	virtual void collisionOutcome(bool collisionFlag, type) = 0; // the outcome of hitting something



private:

};

