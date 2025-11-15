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
	// the order in which these objects are created is important as it is the order in which they will render or update
	this->initializeBackgrounds();
	this->initializeBullets();
	this->initializeShip();

	// calls a polymorphic initialize call to scale the sprites and set starting positions relative to the window

	for (auto& currentobject : this->allObjectsInGame)
	{
		if (currentobject)
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
	this->deltaTime = this->gameClock.restart();
	this->fireBullet();
	this->updateGameObjects();
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

void Game::fireBullet()
{
	this->bulletTimerTracker += this->deltaTime.asSeconds(); // add the frame time to the bullet timer 
	if (this->bulletTimerTracker >= this->SHOOT_SPEED) // if the ship is ready to shoot 
	{
		if (Keyboard::isKeyPressed(Keyboard::Space)) // if the player presses space bar
		{
			for (auto& objectInLoop : this->allObjectsInGame)
			{
				if (objectInLoop)
				{
					if (objectInLoop->getType() == Game_Object::SHIP && objectInLoop->getIsActive())
					{

						Vector2f shipPos = objectInLoop->getPosition(); // get the position of the ship

						for (auto& bulletInLoop : this->allObjectsInGame) // loop again and look for a non active bullet in the object pool 
						{
							if (bulletInLoop)
							{
								if (bulletInLoop->getType() == Game_Object::BULLET && !bulletInLoop->getIsActive())
								{
									bulletInLoop->setPosition(shipPos); // set the position of the bullet = to the ship and activate it 
 									this->bulletTimerTracker = 0; // reset the timer
									break; // break loop to ensure only 1 bullet is fired 
								}
							}
						}
					}

				}
			}
				
				
		}
	}
}

void Game::addGameObjectToPointerArray(Game_Object* objectPassedIn)
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

