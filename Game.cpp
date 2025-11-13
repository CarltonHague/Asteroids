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
		this->renderGame();
	}
}

void Game::initialize()
{
	this->initializeWindow(); // create the game window
}

void Game::initializeWindow()
{
	
	this->window_size = Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->video_mode = video_mode = VideoMode(this->window_size.x, this->window_size.y);
	this->window.create(this->video_mode, this->GAME_TITLE, Style::Titlebar | Style::Close);
}

void Game::pollEvents()
{
	// checks to see if the window was closed or escape pressed
	while (this->window.pollEvent(this->gamePoller))
	{
		if (gamePoller.type == Event::Closed || gamePoller.KeyPressed == Keyboard::Escape)
		{
			this->window.close();
		}
	}

}

void Game::update()
{
}

void Game::renderGame()
{
	// clear the window
	this->window.clear();
	// draw objects here





	// display the window
	this->window.display();


}
