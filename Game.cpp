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
	// set the font to the text objects 
	this->startScreenText.setFont(this->gameFont);
	this->playerHealthText.setFont(this->gameFont);
	this->gameOverText.setFont(this->gameFont);
	// set the color of the text 
	this->startScreenText.setFillColor(Color::Black);
	this->playerHealthText.setFillColor(Color::Black);
	this->gameOverText.setFillColor(Color::Black);
	// set the size of the fonts 
	this->startScreenText.setCharacterSize(this->START_SIZE);
	this->playerHealthText.setCharacterSize(this->PLAYER_STATS_SIZE);
	this->gameOverText.setCharacterSize(this->ENDING_SIZE);
	// set the strings to the text objects
	this->startScreenText.setString(this->startScreenString);
	
	this->playerHealthStream << "Health: " << this->playerShip.getShipHealth() << "\nScore: " << this->score;
	this->playerHealthText.setString(this->playerHealthStream.str());

	this->sameOverStream << "Game Over!\nYour score was: " << this->score << "!\nPress esc to quit the game";
	this->gameOverText.setString(this->sameOverStream.str());

	// set the location of the text objects and center the text
	this->centerOfTheScreenTextLocation = Vector2f(this->window.getSize().x / 2, this->window.getSize().y / 2); // get the center of the screen as a vector 

	this->startScreenText.setPosition(this->centerOfTheScreenTextLocation);
    this->startScreenText.setOrigin(this->startScreenText.getGlobalBounds().width / 2, this->startScreenText.getGlobalBounds().height / 2); 

	this->playerHealthText.setPosition(this->playerStatsLocation);
	this->playerHealthText.setOrigin(this->playerHealthText.getGlobalBounds().width / 2, this->playerHealthText.getGlobalBounds().height / 2);

	this->gameOverText.setPosition(this->centerOfTheScreenTextLocation);
	this->gameOverText.setOrigin(this->gameOverText.getGlobalBounds().width / 2, this->gameOverText.getGlobalBounds().height / 2);

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
		// if the game state is startscreen poll for the enter key to be pressed and change the game state to playing
		if (this->currentGameState == STARTSCREEN)
		{
			if (this->gamePoller.key.code == Keyboard::Enter)
			{
				this->currentGameState = PLAYING;
			}
		}
	}

}

void Game::updateGame()
{
	this->deltaTime = this->gameClock.restart(); // capture delta time
	// if the game state is game over or playing update the background objects on their own
	if (this->currentGameState == GAMEOVER || this->currentGameState == STARTSCREEN)
	{
		this->updateBackground();
	}
	// if the game state is playing update the game loop
	if (this->currentGameState == PLAYING)
	{
		this->spawnAsteroid();
		this->playerInput.updateInput(this->deltaTime); // checks to see what input the player wants to do 
		this->playerShip.updateDirection(this->playerInput.getUp(), this->playerInput.GetDown(), this->playerInput.getLeft(), this->playerInput.getRight()); // update direction using flags from input handler
		this->fireBullet(this->playerInput.getFire()); // if the fire flag is set in the input manager fire a bullet 
		this->updateGameObjects(); // moves and updates all the objects in the game using a polymorphic function call 
		this->collisionChecker.updateCollision(this->allCollideableObjects, this->COLLIDEABLE_OBJECTS); // polymorphic collision call checks all collideable objects and works out collision and outcomes
		this->updatePlayerStats(); // update the player stats such as health and score
	}
	
}

void Game::updateGameObjects()
{
	for (auto& currentobject : this->allObjectsInGame) 
	{
		if (currentobject != nullptr) // check to ensure that you are only updating the objects in the loop and not the pointers
		{
			if (currentobject->getIsActive()) // only update active objects
			{
				currentobject->updateObject(this->deltaTime, this->window);
			}
		}

	}
}

void Game::updateBackground()
{
	for (Background& currentBackground : this->backgroundPool)
	{
		currentBackground.updateObject(this->deltaTime, this->window);
	}
}

void Game::updatePlayerStats()
{
	this->score = 0; // reset the score to 0 then calculate the new score
	for (Asteroids& currentAsteroid : this->asteroidPool)
	{
		this->score += currentAsteroid.getScore();
	}
	int shipHp = this->playerShip.getShipHealth(); // get the ships current hp
	// Clear the stream 
	this->playerHealthStream.str("");
	// update the player stat text
	this->playerHealthStream << "Health: " << shipHp << "\nScore: " << this->score;
	this->playerHealthText.setString(this->playerHealthStream.str());
	// check to see if the game is over
	if (shipHp <= 0)
	{
		// clear the stream
		this->sameOverStream.str("");
		// update the score to the game over text
		this->sameOverStream << "Game Over\nYour score was: " << this->score << "\nPress esc to quit the game";
		this->gameOverText.setString(this->sameOverStream.str());
		// set the game to game over and display the text
		this->currentGameState = GAMEOVER;
	}
}


void Game::renderGame()
{
	// clear the window
	this->window.clear();
	// draw objects here
	if (this->currentGameState == STARTSCREEN)
	{
		this->renderStartScreen();
	}
	if (this->currentGameState == PLAYING)
	{
		this->renderGameObjects();
		this->renderPlayerStats();
	}
	if (this->currentGameState == GAMEOVER)
	{
		this->renderEndScreen();
	}
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

void Game::renderStartScreen()
{
	for (Background& currentBackground : this->backgroundPool)
	{
		currentBackground.renderObject(this->window);
	}
	window.draw(this->startScreenText);
}

void Game::renderEndScreen()
{
	for (Background& currentBackground : this->backgroundPool)
	{
		currentBackground.renderObject(this->window);
	}
	window.draw(this->gameOverText);
}

void Game::renderPlayerStats()
{
	this->window.draw(this->playerHealthText);
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

void Game::spawnAsteroid()
{
	float randomYPos = rand() % this->window.getSize().y;
	this->asteroidTimerTracker += this->deltaTime.asSeconds();
	// buffer check to keep the sprite in screen bounds on spawn 
	if (randomYPos < this->ASTEROID_BUFFER)
	{
		randomYPos += this->ASTEROID_BUFFER;
	}
	if (randomYPos > this->window.getSize().y - this->ASTEROID_BUFFER)
	{
		randomYPos  -= this->ASTEROID_BUFFER;
	}
	if (this->asteroidTimerTracker >= this->ASTEROID_SPAWN_TIMER) // check to see if the spawn timer is full 
	{
		for (Asteroids& currentAsteroid : this->asteroidPool) // loop through the pool to find an asteroid that inactive to spawn
		{
			if (!currentAsteroid.getIsActive()) // check to see if the asteroid is inactive
			{
				currentAsteroid.spawnAsteroid(randomYPos, this->window);
				break; // only spawn one asteroid per cycle
			}
			
		}
		this->asteroidTimerTracker = 0.f;
	}
}

