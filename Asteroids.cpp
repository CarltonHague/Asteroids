#include "Asteroids.h"

Asteroids::Asteroids()
{
	
}

void Asteroids::resetAsteroid()
{
	this->turnOffAsteroid(); // deactivate the object
	// reset the texture rect to the default animation 
	this->asteroidRect = IntRect(0, 0, this->SPRITE_SIZE, this->SPRITE_SIZE);
	this->asteroidSprite.setTextureRect(this->asteroidRect);
	this->asteroidHealth = 0;
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

void Asteroids::turnOffAsteroid()
{
	this->deactivate();
	this->notCollideable();
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
	this->turnOffAsteroid(); // set the asteroid to not active by default 
	

}

FloatRect Asteroids::getBounds()
{
	return this->asteroidSprite.getGlobalBounds();
}

bool Asteroids::collisionCheck(FloatRect objectYouAreHitting)
{
	FloatRect currentBounds = this->asteroidSprite.getGlobalBounds();
	if (currentBounds.intersects(objectYouAreHitting) && currentBounds != objectYouAreHitting) // check if the object intersects the bounds of the current object
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Asteroids::collisionOutcome(bool collisionFlag, type whatHitYou)
{
	if (collisionFlag && whatHitYou == BULLET)
	{
		this->asteroidHealth -= this->BULLET_DAMAGE;
	}
	if (collisionFlag && whatHitYou == SHIP)
	{
		resetAsteroid();
	}
}

Asteroids::~Asteroids()
{
}
