#include "Bullet.h"

Bullet::Bullet()
{
	// create the bullet set it inactive by default

	
	this->object_type = BULLET;
	this->deactivate(); // set the bullet to not active by default

}

Bullet::~Bullet()
{
}

void Bullet::scaleAndCentre(RenderWindow& window)
{
	IntRect bulletBounds = this->bulletSprite.getTextureRect(); // get the texture rect of the bullet sprite
	float scaleX = static_cast<float>(window.getSize().x / bulletBounds.width);
	float scaleY = (static_cast<float>(window.getSize().y) / static_cast <float> (bulletBounds.height));
	scaleX = scaleX / this->BULLET_SCALE;
	scaleY = scaleY / this->BULLET_SCALE;
	this->bulletSprite.setScale(scaleX, scaleY); // scale the bullet based on the scale amount you want 
	this->bulletSprite.setOrigin(static_cast<float>(bulletBounds.width) / 2.0f, static_cast<float>(bulletBounds.height) / 2.0f);  // set the origin to the center of the ship sprite

}

void Bullet::fireBullet(Vector2f shipPos)
{
	this->bulletSprite.setPosition(shipPos); // set the bullet to the same position as the ship
	this->setToActive(); // set the bullet to active to be rendered and moved 
}

void Bullet::setTexture(Texture& tex)
{
	this->bulletSprite.setTexture(tex);
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
		if (this->animationTimer > this->ANIMATION_SPEED) // set the timer to the max timer amount to avoid it infinately increasing
		{
			this->animationTimer = this->ANIMATION_SPEED;
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



void Bullet::initializeObject(RenderWindow& window)
{
	this->bulletRect = IntRect(0, 0, this->SPRITE_SIZE, this->SPRITE_SIZE); // set the rect to the size of one frame of the sprite 
	this->bulletSprite.setTextureRect(this->bulletRect); // set texture rect
	this->scaleAndCentre(window);



}

