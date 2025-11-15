#include "Asteroids.h"

Asteroids::Asteroids()
{
	
}

void Asteroids::resetAsteroid()
{
	this->deactivate(); // deactivate the object
	// reset the texture rect to the default animation 
	this->asteroidRect = IntRect(0, 0, this->SPRITE_SIZE, this->SPRITE_SIZE);
	this->asteroidSprite.setTextureRect(this->asteroidRect);
}

void Asteroids::setTexture(Texture& tex)
{
	this->asteroidSprite.setTexture(tex);
	this->asteroidSprite.setTextureRect(this->asteroidRect);
}

void Asteroids::animateAsteroid()
{
	this->asteroidRect.left += this->SPRITE_SIZE;
	if (this->asteroidRect.left > this->SPRITE_SIZE * 7)
	{
		this->asteroidRect.left = 0;
		this->asteroidRect.top += SPRITE_SIZE;

	}
	if (this->asteroidRect.top > this->SPRITE_SIZE * 3)
	{
		this->asteroidRect.top = 0;
	}
	this->asteroidSprite.setTextureRect(this->asteroidRect);

}



void Asteroids::updateObject(Time deltaTime, RenderWindow& window)
{
	if (this->getIsActive()) // if the asteroid is active
	{
		this->asteroidSprite.move(this->ASTEROID_MOVE_VECTOR);
		this->animateAsteroid();

		Vector2f asteroidPos = this->asteroidSprite.getPosition(); // get the current location of the asteroid
		if (asteroidPos.x >= window.getSize().x ||  // check to see if it leaves the window
			asteroidPos.x <= 0 || 
			asteroidPos.y >= window.getSize().y || 
			asteroidPos.y <= 0)
		{

			this->resetAsteroid();

        }



	}

}

void Asteroids::renderObject(RenderWindow& window)
{
	window.draw(this->asteroidSprite);
}

void Asteroids::initializeObject(RenderWindow& window)
{
	this->deactivate(); // set the asteroid to not active by default 
	this->object_type = ASTEROID; // set the type to asteroid

}

Asteroids::~Asteroids()
{
}
