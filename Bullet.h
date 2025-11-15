#pragma once
#include "Game_Object.h"
#include "Collidable_Object.h"
// class for managing the bullets logic
// each bullet texture is 32 by 32 and the total sprite sheet is 32 x 62

class Bullet : public Game_Object, public Collidable_Object
{
public:
	Bullet(); // constructor
	~Bullet()override; // deconstructor
	void setTexture(Texture& tex); // set the texture of the bullet sprite
	void fireBullet(Vector2f shipPos); // function to fire the bullet

private:
	// private functions
	void scaleAndCentre(RenderWindow& window); // to set the scale of the bullets and set the origin to the centre of the bullet
	



	//virtual functions overrides
	void updateObject(Time deltaTime, RenderWindow& window) override;  // function to update the object with delta time 
	void renderObject(RenderWindow& window) override; // function to draw the object
	void initializeObject(RenderWindow& window) override; //function to scale to the correct based on the render window




	// vairables 
	const float BULLET_SPEED = 200.f;
	const float BULLET_SCALE = 30.f; // scaler value of the bullet relative to the window size 
	const float ANIMATION_SPEED = 0.2f; // the speed that the sprite changes between the two frames in seconds 
	float animationTimer = 0.f;
	Sprite bulletSprite;
	const Vector2f bulletVelocity = Vector2f(BULLET_SPEED, 0); // set the x speed of the bullet to the const vairable
	float bulletSpeed = 0;
	IntRect bulletRect;
	Vector2f bulletPosition = Vector2f (0.f, 0.f); // for storing the bullets current position set to 0, 0 by default 
	const int SPRITE_SIZE = 32;

};

