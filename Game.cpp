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
	this->initializeGameObjects();
}

void Game::initializeWindow()
{
	
	this->window_size = Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->video_mode = video_mode = VideoMode(this->window_size.x, this->window_size.y);
	this->window.create(this->video_mode, this->GAME_TITLE, Style::Titlebar | Style::Close);
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
	this->initializeShip();
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
	// create a ship using the ship texture and attach it to the game object pointer
	for(int numberOfShipsToCreate = 0; numberOfShipsToCreate < this->MAX_SHIPS; numberOfShipsToCreate++)
	this->allObjectsInGame[numberOfShipsToCreate] = std::make_unique<Ship>(this->shipTexture); 

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
	this->updateGameObjects();
}

void Game::updateGameObjects()
{
	for (auto& currentobject : this->allObjectsInGame)
	{
		if (currentobject)
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
		if (currentobject)
		{
			if (currentobject->getIsActive())
			{
				currentobject->renderObject(this->window);
			}
		}

	}

}

bool Game::loadBackgroundTexture(const std::string& filename, Texture& texture)
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
