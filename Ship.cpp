#include "Ship.h"

Ship::Ship(Texture &tex)
{
	this->shipSprite.setTexture(tex);
	object_type = SHIP;
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

void Ship::updateDirection()
{
	// poll to see if a key is pressed and change the ship direction accordingly
	bool up = Keyboard::isKeyPressed(Keyboard::W);
	bool down = Keyboard::isKeyPressed(Keyboard::S);
	bool left = Keyboard::isKeyPressed(Keyboard::A);
	bool right = Keyboard::isKeyPressed(Keyboard::D);

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

void Ship::updateObject(Time deltaTime, RenderWindow& window)
{
	this->updateDirection(); // update the ship direction based on user input
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

Game_Object::type Ship::getType()
{
	return SHIP;
}

FloatRect Ship::getBounds()
{
	return this->shipSprite.getGlobalBounds();
}


