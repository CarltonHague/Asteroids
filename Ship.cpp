#include "Ship.h"

Ship::Ship()
{
	this->shipHealth = this->MAX_HP;
	object_type = SHIP;
	this->setCollideable(); // set the ship to collideable for collision detection 
}

Ship::~Ship()
{
	
}

void Ship::initializeObject(RenderWindow& window)
{
	this->setToActive();
	this->scaleAndCenterOrigin(window);
}

void Ship::scaleAndCenterOrigin(RenderWindow& window)
{
	// similar code to the 3rd homework with the ship

	IntRect shipBounds = this->shipSprite.getTextureRect(); // get the texture rect of the ship sprite
	float scaleX = static_cast<float>(window.getSize().x / shipBounds.width);
	float scaleY = (static_cast<float>(window.getSize().y) / static_cast <float> (shipBounds.height));
	scaleX = scaleX / this->SHIP_SCALE;
	scaleY = scaleY / this->SHIP_SCALE;
	this->shipSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2); // set the ship to the center of the screen
	this->shipSprite.setScale(scaleX, scaleY); // scale the ship down to half size
	this->shipSprite.setRotation(this->SHIP_ROTATION); // rotate the ship to face to the right
	this->shipSprite.setOrigin(static_cast<float>(shipBounds.width) / 2.0f, static_cast<float>(shipBounds.height) / 2.0f);  // set the origin to the center of the ship sprite


}

void Ship::renderObject(RenderWindow& window)
{
	window.draw(this->shipSprite);
}

void Ship::updateDirection(bool up, bool down, bool left, bool right)
{
	// update the ship using input from the manager class
	if (up && right)
		this->shipDirection = NORTH_EAST;
	else if (up && left)
		this->shipDirection = NORTH_WEST;
	else if (down && right)
		this->shipDirection = SOUTH_EAST;
	else if (down && left)
		this->shipDirection = SOUTH_WEST;
	else if (up)
		this->shipDirection = NORTH;
	else if (down)
		this->shipDirection = SOUTH;
	else if (left)
		this->shipDirection = WEST;
	else if (right)
		this->shipDirection = EAST;
	else
		this->shipDirection = STOPPED;

}

Vector2f Ship::getPosition()
{
	return this->shipSprite.getPosition();
}

int Ship::getShipHealth()
{
	return this->shipHealth;
}

void Ship::updateObject(Time deltaTime, RenderWindow& window)
{
	//check the ship direction and update the velocity accordingly
	switch (this->shipDirection)
	{
	case NORTH:
		this->shipVelocity.y = (this->SHIP_SPEED * -1);
		this->shipVelocity.x = 0.f;
		break;
	case NORTH_EAST:
		this->shipVelocity.x = this->SHIP_SPEED / 2;
		this->shipVelocity.y = (this->SHIP_SPEED * -1) / 2;
		break;
	case NORTH_WEST:
		this->shipVelocity.x = (this->SHIP_SPEED * -1) / 2;
		this->shipVelocity.y = (this->SHIP_SPEED * -1) / 2;
		break;
	case SOUTH:
		this->shipVelocity.y = this->SHIP_SPEED;
		this->shipVelocity.x = 0.f;
		break;
	case SOUTH_EAST:
		this->shipVelocity.x = this->SHIP_SPEED / 2;
		this->shipVelocity.y = this->SHIP_SPEED / 2;
		break;
	case SOUTH_WEST:
		this->shipVelocity.x = (this->SHIP_SPEED * -1) / 2;
		this->shipVelocity.y = this->SHIP_SPEED / 2;
		break;
	case WEST:
		this->shipVelocity.x = (this->SHIP_SPEED * -1);
		this->shipVelocity.y = 0.f;
		break;
	case EAST:
		this->shipVelocity.x = this->SHIP_SPEED;
		this->shipVelocity.y = 0.f;
		break;
	case STOPPED: this->shipVelocity.x = 0.f;
		this->shipVelocity.y = 0.f;
		break;
	default:
		break;
	}
	this->shipWindowBoundsCollision(window);
	this->shipSprite.move(this->shipVelocity * deltaTime.asSeconds()); // move the ship based on its velocity and delta time


}

FloatRect Ship::getBounds()
{
	return this->shipSprite.getGlobalBounds();
}

bool Ship::collisionCheck(FloatRect objectYouAreHitting)
{
	FloatRect currentBounds = this->shipSprite.getGlobalBounds();
	if (objectYouAreHitting.intersects(currentBounds) && objectYouAreHitting != currentBounds) // checks if you intersecred with the object and it's not yourself
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void Ship::collisionOutcome(bool collisionFlag, type whatHitYou)
{
	// if the ship is hit by an asteroid of diffrent kinds take damge 
	if (collisionFlag && whatHitYou == LARGE_ASTEROID)
	{
		this->shipTakeDamge(LARGE_ASTEROID_DAMAGE);
		
	}
	if (collisionFlag && whatHitYou == SMALL_ASTEROID)
	{
		this->shipTakeDamge(SMALL_ASTEROID_DAMAGE);
	}
	if (collisionFlag && whatHitYou == NORMAL_ASTEROID)
	{
		this->shipTakeDamge(NORMAL_ASTEROID_DAMAGE);
	}
}

void Ship::shipWindowBoundsCollision(RenderWindow& window)
{
	// same function as in homework 3

	this->shipPosition = this->shipSprite.getPosition();
	if (this->shipPosition.x <= 0 + this->shipSprite.getGlobalBounds().width)
	{
		this->shipSprite.setPosition(0 + this->shipSprite.getGlobalBounds().width, this->shipPosition.y);
	}
	if (this->shipPosition.x >= (window.getSize().x - this->shipSprite.getGlobalBounds().width))
	{
		this->shipSprite.setPosition(window.getSize().x - this->shipSprite.getGlobalBounds().width, this->shipPosition.y);
	}
	if (this->shipPosition.y <= 0 + this->shipSprite.getGlobalBounds().height)
	{
		this->shipSprite.setPosition(this->shipPosition.x, 0 + this->shipSprite.getGlobalBounds().height);
	}
	if (this->shipPosition.y >= (window.getSize().y - this->shipSprite.getGlobalBounds().height))
	{
		this->shipSprite.setPosition(this->shipPosition.x, window.getSize().y - this->shipSprite.getGlobalBounds().height);
	}
}

void Ship::shipTakeDamge(int damageAmount)
{
	this->shipHealth -= damageAmount;
	if (this->shipHealth <= 0)
	{
		shipHealth = 0;
	}
}

void Ship::setTexture(Texture& tex)
{
	this->shipSprite.setTexture(tex);
}



