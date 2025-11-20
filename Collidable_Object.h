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
	CircleShape circleHitbox;

	bool collisionCheck(float distanceSquared, float radius) // collision dectection calculation if the radius of object 1 + object 2 is greater than the distance squared then you have a collision 
	{
		if (distanceSquared <= (radius*radius))
		{
			return true;

		}
		else
		{
			return false;
		}
	}

	type object_type = NONE; // default is NONE type

	type getType() { return object_type; }; // function that returns the type of collideable object it is 

	
	Vector2f getPositionOfCircle() { return this->circleHitbox.getPosition(); } // function to get the position of the obejct
	float getRadius() { return this->circleHitbox.getRadius(); } // function to get the radius of of the hitbox circle

	// virtual functions 
	virtual void collisionOutcome(bool collisionFlag, type) = 0; // the outcome of hitting something changed depending on the kind of object being hit and what hit it



private:

};

