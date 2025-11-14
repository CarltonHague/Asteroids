#pragma once
#include "Game_Object.h"
// class for managing the bullets logic
// each bullet texture is 32 by 32 and the total sprite sheet is 32 x 62

class Bullet : public Game_Object
{
public:
	Bullet(Texture &tex, const float bulletspeed); // constructor
	~Bullet()override; // deconstructor


private:
	// private functions
	void scaleAndCentre(RenderWindow& window); // to set the scale of the bullets and set the origin to the centre of the bullet




	//virtual functions overrides
	void updateObject(Time deltaTime, RenderWindow& window) override;  // function to update the object with delta time 
	void renderObject(RenderWindow& window) override; // function to draw the object
	FloatRect getBounds() override; // function that returns the bounds of the object 
	void initializeObject(RenderWindow& window) override; // function to initialize the object such as scaling and placement on screen
	type getType() override; // function that returns the type of the object
	IntRect getTextureRect() override; // function to get the texture rect of the object
	void setTextureRect(IntRect rect) override; // function to set the texture rect of the object's sprite
	Vector2f getPosition() override; // override to get the position of the bullet 
	void setPosition(Vector2f) override; // override to set the position of the bullet and activate it




	// vairables 
	const float BULLET_SCALE = 30.f; // scaler value of the bullet relative to the window size 
	const float ANIMATION_SPEED = 0.2f; // the speed that the sprite changes between the two frames in seconds 
	float animationTimer = 0.f;
	Sprite bulletSprite;
	Vector2f bulletVelocity;
	float bulletSpeed = 0;
	IntRect bulletRect;
	Vector2f bulletPosition = Vector2f (0.f, 0.f); // for storing the bullets current position set to 0, 0 by default 
	const int SPRITE_SIZE = 32;

};

