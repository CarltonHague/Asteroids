#include "Bullet.h"

Bullet::Bullet(Texture &tex, const float bulletSpeed)
{
	// create the bullet set the texture to the passed in texture and bullet speed to passed in float
	this->bulletSpeed = bulletSpeed;
	this->bulletVelocity.x = this->bulletSpeed;
	this->bulletSprite.setTexture(tex);
	this->object_type = BULLET;
	this->deactivate(); // set the bullet to not active by default

}

Bullet::~Bullet()
{
}


void Bullet::updateObject(Time deltaTime, RenderWindow& window)
{
	if (this->getIsActive()) //  if the bullet is active move it using the bullet velocity 
	{
		
		this->bulletSprite.move(this->bulletVelocity.x *deltaTime.asSeconds(), this->bulletVelocity.y * deltaTime.asSeconds());
  		this->animationTimer += deltaTime.asSeconds();
		if (this->animationTimer >= this->ANIMATION_SPEED)
		{
			this->bulletRect.left += this->SPRITE_SIZE; // change the sprite rect to animate a frame
			if (this->bulletRect.left > this->SPRITE_SIZE ) 
			{
				this->bulletRect.left = 0; // if the rect left is larger than the two frames on the sheet reset to base animation
			}
			this->animationTimer = 0.f;
		}
		this->bulletSprite.setTextureRect(this->bulletRect);
		this->bulletPosition = this->bulletSprite.getPosition();
		// if the sprite goes out of the bounds of the screen
		if (this->bulletPosition.x >= window.getSize().x
			|| this->bulletPosition.x <= 0
			|| this->bulletPosition.y >= window.getSize().y
			|| this->bulletPosition.y <= 0)
		{
			this->deactivate(); // deactivate the bullet
		}

	}



}

void Bullet::renderObject(RenderWindow& window)
{
	window.draw(this->bulletSprite);
	
}

FloatRect Bullet::getBounds()
{
	return this->bulletSprite.getGlobalBounds();
}

void Bullet::initializeObject(RenderWindow& window)
{
	this->bulletRect = IntRect(0, 0, this->SPRITE_SIZE, this->SPRITE_SIZE); // set the rect to the size of one frame of the sprite 
	this->bulletSprite.setTextureRect(this->bulletRect); // set texture rect




}

Game_Object::type Bullet::getType()
{
	return this->object_type;
}

IntRect Bullet::getTextureRect()
{
	return this->bulletSprite.getTextureRect();
}

void Bullet::setTextureRect(IntRect rect)
{
	this->bulletSprite.setTextureRect(rect);
}

Vector2f Bullet::getPosition()
{
	return this->bulletSprite.getPosition();
}

void Bullet::setPosition(Vector2f pos)
{
	this->bulletSprite.setPosition(pos);
	this->setToActive();
}
