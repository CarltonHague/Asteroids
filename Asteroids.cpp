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

void Asteroids::turnOnAsteroid()
{
	this->setCollideable();
	this->setToActive();
}



void Asteroids::updateObject(Time deltaTime, RenderWindow& window)
{
	
	if (this->getIsActive()) // if the asteroid is active
	{
		if (this->asteroidHealth <= 0) // if the asteroid is dead remove it from the game
		{
			this->resetAsteroid();

		}
		this->asteroidSprite.move(this->ASTEROID_MOVE_VECTOR.x * deltaTime.asSeconds(),this->ASTEROID_MOVE_VECTOR.y *deltaTime.asSeconds());
		this->animationTracker += deltaTime.asSeconds(); // use delta time to track the speed at which the animation updates 
		if (this->animationTracker >= this->ANIMATION_SPEED)
		{
			this->animateAsteroid();// update the animation 
			this->animationTracker = 0.f; // reset the tracker 
		}

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
	if (this->getIsActive()) // if the asteroid is active
	{
		window.draw(this->asteroidSprite);
	}
}

void Asteroids::initializeObject(RenderWindow& window)
{
	this->turnOffAsteroid(); // set the asteroid to not active by default 
	// center origin of the asteroid sprite similar code to in the ship class
	this->asteroidSprite.setOrigin(static_cast<float>(this->asteroidSprite.getTextureRect().width) / 2.0f, static_cast<float>(this->asteroidSprite.getTextureRect().height) / 2.0f); 

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

void Asteroids::spawnAsteroid(float yPos, RenderWindow &window)
{
	int whatKindOfAsteroidSpawned = rand() % 3 + 1; // rolls a number between 1 and 3
	// spawn an asteroid based on the number rolled either large, small or normal
	switch (whatKindOfAsteroidSpawned) 
	{
	case 1: 
		this->object_type = SMALL_ASTEROID; // set the flag for the asteroid for ship to asteroid collision handling 
		this->asteroidHealth = SMALL_ASTEROID_HP; // set the health of the current asteroid based on type 
		this->asteroidSprite.setPosition(window.getSize().x, yPos); // set the position based on the new y pos
		this->turnOnAsteroid(); // set the asteroid to active 
		this->asteroidSprite.setScale(Vector2f(this->SMALL_SCALE,SMALL_SCALE)); // scale the asteroid to small
		this->ASTEROID_MOVE_VECTOR = Vector2f(this->SMALL_SPEED, 0); // Set the speed based on the const values 
		break;
	case 2:
		this->object_type = NORMAL_ASTEROID;
		this->asteroidHealth = NORMAL_ASTEROID_HP;
		this->asteroidSprite.setPosition(window.getSize().x, yPos);
		this->turnOnAsteroid();
		this->asteroidSprite.setScale(Vector2f(this->NORMAL_SCALE, NORMAL_SCALE)); 
		this->ASTEROID_MOVE_VECTOR = Vector2f(this->NORMAL_SPEED, 0); 
		break;
	case 3:
		this->object_type = LARGE_ASTEROID;
		this->asteroidHealth = LARGE_ASTEROID_HP;
		this->asteroidSprite.setPosition(window.getSize().x, yPos);
		this->turnOnAsteroid();
		this->asteroidSprite.setScale(Vector2f(this->LARGE_SCALE, LARGE_SCALE)); 
		this->ASTEROID_MOVE_VECTOR = Vector2f(this->LARGE_SPEED, 0);
		break;

	default:
		break;
	}






}
