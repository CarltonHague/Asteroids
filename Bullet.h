#pragma once
#include "Game_Object.h"
// class for managing the bullets logic
class Bullet : public Game_Object
{
public:
	Bullet(Texture &tex, const float bulletspeed); // constructor
	~Bullet()override; // deconstructor
	void spawnBullet(Vector2f playerPosition);


private:
	// private functions





	//virtual functions overrides
	void updateObject(Time deltaTime, RenderWindow& window) override;  // function to update the object with delta time 
	void renderObject(RenderWindow& window) override; // function to draw the object
	FloatRect getBounds() override; // function that returns the bounds of the object 
	void initializeObject(RenderWindow& window) override; // function to initialize the object such as scaling and placement on screen
	type getType() override; // function that returns the type of the object
	IntRect getTextureRect() override; // function to get the texture rect of the object
	void setTextureRect(IntRect rect) override; // function to set the texture rect of the object's sprite






	// vairables 
	Sprite bulletSprite;
	Vector2f bulletVelocity;
	float bulletSpeed = 0;
	IntRect bulletRect;


};

