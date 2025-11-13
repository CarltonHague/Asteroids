#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
// Vitual class for inhertence by game objects

class Game_Object
{
public:
	enum type
	{
		NONE,
		ASTEROID,
		BULLET,
		BACKGROUND,
		SHIP

	};
	type object_type = NONE;
	bool is_active = false; // default is not active 


	// regular functions
	bool getIsActive();
	void setToActive();
	void deactivate();


	// Pure virtual functions
	virtual void updateObject(Time deltaTime, RenderWindow &window) = 0;
	virtual void renderObject(RenderWindow &window) = 0;
	virtual FloatRect getBounds() = 0;
	virtual void initializeObject(RenderWindow &window) = 0;
	virtual ~Game_Object() = default; // default deconstructor 
	virtual type getType() = 0;

};

