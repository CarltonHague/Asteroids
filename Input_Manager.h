#pragma once
#include"SFML/Graphics.hpp"
using namespace sf;
// Class for managing the player input could be expanded to allow for controller support etc

class Input_Manager
{
public:
	Input_Manager(); // constructor 
	void updateInput(Time deltaTime); // update the bools based on the players input
	void resetReadyToFire();
	bool getUp();
	bool GetDown();
	bool getLeft();
	bool getRight();
	bool getFire();


private:
	void resetMovementInput(); // function to reset the bools before each update
	bool inputUp = false;
	bool inputDown = false;
	bool inputLeft = false;
	bool inputRight = false;
	bool inputFire = false;
	const float fireRate = 1.f; // the player can only shoot every second by default
	float fireRateTracker = 0.f;


};

