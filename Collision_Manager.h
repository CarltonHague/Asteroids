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
					FloatRect objectBounds = array[firstLoop]->getBounds();// gets the bounds of the first object

					for (int secondLoop = firstLoop + 1; secondLoop < amountOfObjects; secondLoop++) // do a second loop starting from 1 infront of the previous object
					{
						if (array[secondLoop] != nullptr)
						{
							if (array[secondLoop]->getIsCollideable()) // check to see if that object is even active
							{
								bool collision = array[secondLoop]->collisionCheck(objectBounds); // check to see if there's a collision 
								if (collision) // if there is 
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

