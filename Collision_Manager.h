#pragma once
#include"SFML/Graphics.hpp"
#include"Collidable_Object.h"
// this is a manager that checks collision between collideable objects 
class Collision_Manager
{
public:
	Collision_Manager(); // constructor
	void updateCollision(Collidable_Object* array[], int amountOfObjects);



private:





};

