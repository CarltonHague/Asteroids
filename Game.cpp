#include "Game.h"

Game::Game()
{
}

void Game::run()
{
	// main game loop 
	while (this->window.isOpen())
	{
		this->pollEvents();
		this->updateGame();
		this->renderGame();
	}
}

void Game::initialize()
{
	currentGameState = STARTSCREEN;
	this->initializeWindow(); // create the game window
	this->initializeTextures(); // sets the textures to the file path
	this->initializeFontAndText(); // sets the font and text vairables
	this->initializeGameObjects(); // creates the game objects and attaches them to the pointer
}

void Game::initializeWindow()
{
	
	this->window_size = Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->video_mode = video_mode = VideoMode(this->window_size.x, this->window_size.y);
	this->window.create(this->video_mode, this->GAME_TITLE, Style::Titlebar | Style::Close);
	this->window.setVerticalSyncEnabled(true);
}

void Game::initializeTextures()
{
	// set the string array to the file paths of the background textures 
	this->backgroundFilePaths[0] = "Assets/backgroundLayers/Mountains01_007.png";
	this->backgroundFilePaths[1] = "Assets/backgroundLayers/Mountains01_000.png";
	this->backgroundFilePaths[2] = "Assets/backgroundLayers/Mountains01_001.png";
	this->backgroundFilePaths[3] = "Assets/backgroundLayers/Mountains01_002.png";
	this->backgroundFilePaths[4] = "Assets/backgroundLayers/Mountains01_003.png";
	this->backgroundFilePaths[5] = "Assets/backgroundLayers/Mountains01_004.png";
	this->backgroundFilePaths[6] = "Assets/backgroundLayers/Mountains01_005.png";
	this->backgroundFilePaths[7] = "Assets/backgroundLayers/Mountains01_006.png";
	// load the ship texture
	this->loadTexture("Assets/ship.png", this->shipTexture);
	// load the backgrounds using the file path array
	for (int backgroundLooper = 0; backgroundLooper < MAX_BACKGROUND_LAYERS; backgroundLooper++)
	{
		this->loadBackgroundTexture(backgroundFilePaths[backgroundLooper], this->BackgroudTextures[backgroundLooper]);
	}
	// load the texture for the asteroids
	this->loadTexture("Assets/asteroid.png", this->AsteroidTexture);
	// load the texture for the missles 
	this->loadTexture("Assets/missile-01.png", this->bulletTexture);
}

void Game::initializeFontAndText()
{
	this->gameFont.loadFromFile("Assets/fonts/comic.ttf");
	if (!this->gameFont.loadFromFile("Assets/fonts/comic.ttf")) // if it fails to load it will assert
	{
		assert(!this->gameFont.loadFromFile("Assets/fonts/comic.ttf"));
	}
}

void Game::initializeGameObjects()
{
	

	// set the pointers to the objects in the pools the order is also the order in which they are rendered and updated 
	this->initializeBackgrounds();
	this->initializeAsteroids();
	this->initializeBullets();
	this->initializeShip();

	// calls a polymorphic initialize call to scale the sprites and set starting positions relative to the window

	for (auto& currentobject : this->allObjectsInGame)
	{
		if (currentobject != nullptr)
		{
			currentobject->initializeObject(this->window);
		}

	}


}

void Game::initializeShip()
{
	// set the texture of the ship
	this->playerShip.setTexture(this->shipTexture);
	// set the pointer to the ship 
	this->addGameObjectToPointerArray(&this->playerShip);
	this->addCollideableObjectToArray(&this->playerShip);

}

void Game::initializeBackgrounds()
{
	// set the texture and speed for each background layer in the pool
	for (int backgroundLooper = 0; backgroundLooper < MAX_BACKGROUND_LAYERS; backgroundLooper++)
	{
		this->backgroundPool[backgroundLooper].initializeBackground(this->BackgroudTextures[backgroundLooper], this->backgroundSpeedArray[backgroundLooper]);

		// set a pointer in the all object array to a copy of each of background in the background array for polymorphic update and render calling 
		this->addGameObjectToPointerArray(&this->backgroundPool[backgroundLooper]);
	}


}

void Game::initializeBullets()
{
	for (int bulletLooper = 0; bulletLooper < MAX_BULLETS; bulletLooper++)
	{
		this->bulletPool[bulletLooper].setTexture(this->bulletTexture);
		this->addGameObjectToPointerArray(& this->bulletPool[bulletLooper]);
		this->addCollideableObjectToArray(&this->bulletPool[bulletLooper]);
	}

}

void Game::initializeAsteroids()
{
	for (int asteroidLooper = 0; asteroidLooper < MAX_ASTEROIDS; asteroidLooper++)
	{
		this->asteroidPool[asteroidLooper].setTexture(this->AsteroidTexture);
		this->addGameObjectToPointerArray(&this->asteroidPool[asteroidLooper]);
		this->addCollideableObjectToArray(&this->asteroidPool[asteroidLooper]);
	}
}


void Game::pollEvents()
{
	// checks to see if the window was closed or escape pressed
	while (this->window.pollEvent(this->gamePoller))
	{
		if (gamePoller.type == Event::Closed || gamePoller.key.code == Keyboard::Escape)
		{
			this->window.close();
		}
	}

}

void Game::updateGame()
{
	this->deltaTime = this->gameClock.restart(); // capture delta time
	this->playerInput.updateInput(this->deltaTime); // checks to see what input the player wants to do 
	this->playerShip.updateDirection(this->playerInput.getUp(), this->playerInput.GetDown(), this->playerInput.getLeft(), this->playerInput.getRight()); // update direction using flags from input handler
	this->fireBullet(this->playerInput.getFire()); // if the fire flag is set in the input manager fire a bullet 
	this->updateGameObjects(); // moves and updates all the objects in the game using a polymorphic function call 
	this->collisionChecker.updateCollision(this->allCollideableObjects, this->COLLIDEABLE_OBJECTS); // polymorphic collision call checks all collideable objects and works out collision and outcomes
}

void Game::updateGameObjects()
{
	for (auto& currentobject : this->allObjectsInGame) 
	{
		if (currentobject) // check to ensure that you are only updating the objects in the loop and not the pointers
		{
			currentobject->updateObject(this->deltaTime, this->window);
		}

	}
}

void Game::renderGame()
{
	// clear the window
	this->window.clear();
	// draw objects here
    this->renderGameObjects();



	// display the window
	this->window.display();


}

void Game::renderGameObjects()
{
	for (auto& currentobject : this->allObjectsInGame)
	{
		if (currentobject) // check to ensure that you are only rendering the objects in the loop and not the pointers
		{
			if (currentobject->getIsActive())
			{
				currentobject->renderObject(this->window);
			}
		}

	}

}

bool Game::loadBackgroundTexture( std::string& filename, Texture& texture)
{
	// similar code used from homework 3 ship game
	if (texture.loadFromFile(filename))
	{
		texture.setSmooth(true); // turns on filtering of the texture
		texture.setRepeated(true); // turns on texture repeating
		return true;
	}
	assert(false); // if loading fails it triggers an assertion
	return false;

}

bool Game::loadTexture(const std::string& filename, Texture& texture)
{
	// similar code used from homework 3 ship game
	if (texture.loadFromFile(filename))
	{
		texture.setSmooth(true); // turns on filtering of the texture
		return true;
	}
	assert(false); // if loading fails it triggers an assertion
	return false;
}



void Game::addGameObjectToPointerArray(Game_Object *objectPassedIn)
{
	
	for (int pointerLooper = 0; pointerLooper < TOTAL_GAME_OBJECTS; pointerLooper++)
	{
		if (this->allObjectsInGame[pointerLooper] == nullptr)
		{
			this->allObjectsInGame[pointerLooper] = objectPassedIn;
			return; // breaks the loop and returns out the function after adding in the object
		}
	}


}

void Game::addCollideableObjectToArray(Collidable_Object * cObject)
{

	for (int pointerLooper = 0; pointerLooper < COLLIDEABLE_OBJECTS; pointerLooper++)
	{
		if (this->allCollideableObjects[pointerLooper] == nullptr)
		{
			this->allCollideableObjects[pointerLooper] = cObject;
			return; // breaks the loop and returns out the function after adding in the object
		}
	}

}

void Game::fireBullet(bool readyToFire)
{
	
	if (readyToFire) // if the player wants to fire
	{
			for (Bullet& bulletInPool : this->bulletPool) // loop throught the bullet pool 
			{
				if (!bulletInPool.getIsActive()) // if a bullet is not active
				{
					bulletInPool.fireBullet(this->playerShip.getPosition()); // fire the bullet 
					this->playerInput.resetReadyToFire(); // reset the fire flag
					break; // should ensure that only 1 bullet is fired 
				}
			}
	}
}

