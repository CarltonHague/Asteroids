#pragma once
#include"SFML/Graphics.hpp"
#include"Collidable_Object.h"
// this is a manager struct that checks collision between collideable objects 

struct Collision_Manager
{

	
	void updateCollision(Collidable_Object* array[], int amountOfObjects)
	{
		// loops throught the collideable objects 
		for (int firstLoop = 0; firstLoop < amountOfObjects; firstLoop++)
		{
			if (array[firstLoop] != nullptr) // checks to ensure it's an object not a null ptr
			{
				if (array[firstLoop]->getIsCollideable()) // checks to see if it is active
				{
					float object1Radius = array[firstLoop]->getRadius();// gets the radius of the first object
					Vector2f object1Position = array[firstLoop]->getPositionOfCircle(); // get the position of the first object

					for (int secondLoop = firstLoop + 1; secondLoop < amountOfObjects; secondLoop++) // do a second loop starting from 1 infront of the previous object
					{
						if (array[secondLoop] != nullptr) // check to ensure it is not a null pointer
						{
							if (array[secondLoop]->getIsCollideable()) // check to see if that object is even active
							{
								float object2Radius = array[secondLoop]->getRadius();
								Vector2f object2Position = array[secondLoop]->getPositionOfCircle();
								Vector2f distance = object1Position - object2Position; // calculate the distance between objects 
								float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y); // add x squared and y squared together to get one float 
								float radiusAdded = object1Radius + object2Radius; // add both circle hit box raidus together 
								bool collision = array[firstLoop]->collisionCheck(distanceSquared, radiusAdded); // check if the radius is greater than the distance if it is then you have collision 

								if (collision) // if collision 
								{
									array[firstLoop]->collisionOutcome(collision, array[secondLoop]->getType()); // apply outcomes to the fist object
									array[secondLoop]->collisionOutcome(collision, array[firstLoop]->getType()); // apply outcomes to the second object
								}
							}
						}
					}


				}
			}
		}

	}


};

