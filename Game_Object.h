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
	type object_type;
	bool is_active;
	// Pure virtual functions
	virtual void update(Time deltatime) = 0;
	virtual void render(RenderWindow window) = 0;
	virtual FloatRect getBounds() = 0;
	virtual bool getActive() = 0;
	virtual void initialize(Texture tex, RenderWindow window) = 0;



};

