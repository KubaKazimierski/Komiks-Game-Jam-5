#include "Game.hpp"

Game::Game() : Window(sf::VideoMode(980, 540), "")
{
}

void Game::start()
{
	int UPDATE_RATE = 60, 
		MILLISECONDS_PER_UPDATE = 1000 / UPDATE_RATE;
	sf::Clock Clock;
	sf::Time Delta = sf::Time::Zero;

	while (Window.isOpen())
	{
		Delta = Clock.getElapsedTime();

		if(Delta.asMilliseconds() >= MILLISECONDS_PER_UPDATE)
		{
			processEvents();
			update();

			Delta = sf::Time::Zero;
		}

		draw(Delta);
	}
}

void Game::update()
{

}

void Game::processEvents()
{
	sf::Event ActualEvent;

	while(Window.pollEvent(ActualEvent))
	{
		if (ActualEvent.type == sf::Event::Closed)
		{
			Window.close();
		}
	}
}

void Game::draw(sf::Time Delta)
{
	Window.clear();

	Window.display();
}

Game::~Game()
{
}
