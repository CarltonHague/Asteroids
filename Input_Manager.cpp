#include "Input_Manager.h"

Input_Manager::Input_Manager()
{
	
}

void Input_Manager::updateInput(Time deltaTime)
{
	this->fireRateTracker += deltaTime.asSeconds(); // add time to the time
	if (this->fireRateTracker > this->fireRate)
	{
		this->fireRateTracker = this->fireRate; // set the timer to the max to prevent it infinatly increasing 
	}
	// reset the input flags from the previous frame
	this->resetMovementInput();
	// check for new input 
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
	{
		this->inputUp = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->inputRight = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
	{
		this->inputDown = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->inputLeft = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && this->fireRateTracker >= this->fireRate) // will only set the fire flag if space bar is pressed and the tracker is equal to the ships fire rate
	{
		this->inputFire = true;
		
	}
}

void Input_Manager::resetReadyToFire()
{
	this->inputFire = false; // resets the fire flag to false
	this->fireRateTracker = 0.f; // resets the fire rate tracker 
}

bool Input_Manager::getUp()
{
	return this->inputUp;
}

bool Input_Manager::GetDown()
{
	return this->inputDown;
}

bool Input_Manager::getLeft()
{
	return this->inputLeft;
}

bool Input_Manager::getRight()
{
	return this->inputRight;
}

bool Input_Manager::getFire()
{
	return this->inputFire;
}

void Input_Manager::resetMovementInput()
{
	
	this->inputRight = false;
	this->inputLeft = false;
	this->inputUp = false;
	this->inputDown = false;
}
