#include "Background.h"

Background::Background(Texture &tex, float speed)
{
	this->backgroundSprite.setTexture(tex);
	this->backgroundSpriteRect = IntRect(0, 0, tex.getSize().x, tex.getSize().y);
	this->backgroundSprite.setTextureRect(this->backgroundSpriteRect);
	object_type = BACKGROUND;
	this->setSpriteSpeed(speed);
	this->setToActive();
	
}

Background::~Background()
{
}

void Background::setSpriteSpeed(float speed)
{
	this->spriteSpeed = speed;
}

void Background::centerAndScaleSprite(RenderWindow& window)
{
	IntRect spriteBounds = this->backgroundSprite.getTextureRect(); // get the bounds of the sprite
	this->backgroundSprite.setOrigin(static_cast<float>(spriteBounds.width) / 2.0f, static_cast<float>(spriteBounds.height) / 2.0f); // set the origin to the center of the sprite
	this->backgroundSprite.setPosition(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)); // set the position to the center of the window
	float scaleX = static_cast<float>(window.getSize().x) / static_cast<float>(spriteBounds.width); // calculate the scale factors by doing the window dimensions divided by the sprite dimensions
	float scaleY = static_cast<float>(window.getSize().y) / static_cast<float>(spriteBounds.height);
	this->backgroundSprite.setScale(scaleX, scaleY); // scale the sprite to fit the window

}

void Background::updateObject(Time deltaTime, RenderWindow& window)
{
	this->scrollOffset += (this->spriteSpeed * deltaTime.asSeconds()); // update the scroll offset based on the sprite speed and delta time
	float textureWidth = static_cast<float>(this->backgroundSprite.getTexture()->getSize().x); // get the width of the texture
	if (scrollOffset > textureWidth) // if the scroll offset exceeds the width of the sprite
	{
		this->scrollOffset -= textureWidth; // reset the scroll offset
	}

	this->backgroundSpriteRect.left = static_cast<int> (this->scrollOffset); // update the left position of the texture rect using the offset
	this->backgroundSprite.setTextureRect(this->backgroundSpriteRect); // set the texture rect to the updated rect


}

void Background::renderObject(RenderWindow& window)
{
	window.draw(this->backgroundSprite);
}

FloatRect Background::getBounds()
{
	return this->backgroundSprite.getGlobalBounds();
}

void Background::initializeObject(RenderWindow& window)
{
	this->centerAndScaleSprite(window);
}

Game_Object::type Background::getType()
{
	return object_type;
}

IntRect Background::getTextureRect()
{
	return this->backgroundSprite.getTextureRect();
}

void Background::setTextureRect(IntRect rect)
{
	this->backgroundSpriteRect = rect;
	this->backgroundSprite.setTextureRect(this->backgroundSpriteRect);
}

Vector2f Background::getPosition()
{
	return this->backgroundSprite.getPosition();
}

void Background::setPosition(Vector2f pos)
{
	this->backgroundSprite.setPosition(pos);
}
