/*
   Season Shooter - a Komiks Game Jam 5 entry, theme: 'Seasons'
   Copyright 2018 Jakub Kazimierski

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Game.hpp"

const sf::Color Game::Colors[] = {
	sf::Color(108, 238, 60),
	sf::Color(235, 211, 32),
	sf::Color(245, 111, 30),
	sf::Color(230, 230, 230)
};

Game::Game() : Window(sf::VideoMode(980, 540),
					  "Season Shooter"),
			   GameArea(0, 0, Window.getSize().x, Window.getSize().y),
			   Indicator(GameArea)
{
	Font.loadFromFile("assets/Kemco Pixel Bold.ttf");
	GameOverText.setFont(Font);
	GameOverText.setString("Game Over");
	GameOverText.setFillColor(sf::Color::Black);
	GameOverText.setCharacterSize(100);
	GameOverText.setPosition(
		GameArea.width / 2 - GameOverText.getGlobalBounds().width / 2,
		GameArea.height / 2 - GameOverText.getGlobalBounds().height
	);

	ShotSound.openFromFile("assets/Shot.wav");
	initMap();
	spawnEnemies();
}

void Game::initMap()
{
	for(sf::Vector2f i = sf::Vector2f(0, 0); i.x < Window.getView().getSize().x; i.x += 32)
	{
		Walls.push_back(std::make_unique<Wall>(i));
	}

	for(sf::Vector2f i = sf::Vector2f(0, 0); i.y < (Window.getView().getSize().y - 32); i.y += 32)
	{
		Walls.push_back(std::make_unique<Wall>(i));
	}

	for(sf::Vector2f i = sf::Vector2f(static_cast<float>(Window.getView().getSize().x) - 32, 32); i.y < Window.getSize().y - 32; i.y += 32)
	{
		Walls.push_back(std::make_unique<Wall>(i));
	}

	for(sf::Vector2f i = sf::Vector2f(0, static_cast<float>(Window.getView().getSize().y) - 32); i.x < Window.getSize().x; i.x += 32)
	{
		Walls.push_back(std::make_unique<Wall>(i));
	}

	sf::Vector2f ActualPosition = sf::Vector2f(128, 128);

	for(int i = 0; i < 9; ++i, ActualPosition.x += 32)
	{
		if(i % 3 == 0 && i != 0)
		{
			ActualPosition.y += 32;
			ActualPosition.x = 128;
		}

		Walls.push_back(std::make_unique<Wall>(ActualPosition));
	}

	ActualPosition = sf::Vector2f(800, 232);

	for(int i = 0; i < 9; ++i, ActualPosition.x += 32)
	{
		if(i % 3 == 2 && i != 0)
		{
			ActualPosition.y += 32;
			ActualPosition.x = 800;
		}

		Walls.push_back(std::make_unique<Wall>(ActualPosition));
	}

	ActualPosition = sf::Vector2f(400, 350);

	for(int i = 0; i < 13; ++i, ActualPosition.x += 32)
	{
		if(i % 5 == 4 && i != 0)
		{
			ActualPosition.y += 32;
			ActualPosition.x = 400;
		}

		Walls.push_back(std::make_unique<Wall>(ActualPosition));
	}
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
			handleInput();
			update();

			Clock.restart();
			Delta = sf::Time::Zero;
		}

		draw(Delta);
	}
}

void Game::update()
{
	if(SeasonClock.getElapsedTime().asMilliseconds() >= SEASON_CHANGE)
	{
		ActualSeason = static_cast<Season>((ActualSeason + 1) % 4);

		if(!GameOver)
		{
			spawnEnemies();
		}
		
		SeasonClock.restart();
	}

	for(size_t i = 0; i < Walls.size(); ++i)
	{
		Walls[i]->update(ActualSeason);
		MainPlayer.collide(*Walls[i]);

		for(size_t j = 0; j < Bullets.size(); ++j)
		{
			Bullets[j]->collide(*Walls[i]);
		}

		for(size_t j = 0; j < Enemies.size(); ++j)
		{
			Enemies[j]->collide(*Walls[i]);
		}
	}

	if(!GameOver)
	{
		MainPlayer.update();
		Indicator.update(MainPlayer.getHP());

		for(size_t i = 0; i < Enemies.size(); ++i)
		{
			Enemies[i]->update(MainPlayer.getPosition());
			MainPlayer.collide(*Enemies[i]);

			for(size_t j = 0; j < Enemies.size(); ++j)
			{
				if(j == i)
				{
					continue;
				}

				Enemies[j]->collide(*Enemies[i]);
			}

			if(Enemies[i]->shouldBeRemoved())
			{
				Enemies.erase(Enemies.begin() + i);
				--i;
			}
		}

		for(size_t i = 0; i < Bullets.size(); ++i)
		{
			Bullets[i]->update();

			for(size_t j = 0; j < Enemies.size(); ++j)
			{
				Enemies[j]->collide(*Bullets[i]);
			}

			if(Bullets[i]->shouldBeRemoved())
			{
				Bullets.erase(Bullets.begin() + i);
				--i;
			}
		}

		if(MainPlayer.getHP() == 0)
		{
			Enemies.clear();
			Bullets.clear();
			GameOver = true;
		}
	}
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

void Game::handleInput()
{
	MainPlayer.handleInput();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Window.close();
	}

	if(!GameOver)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)
		   && ShootingClock.getElapsedTime().asMilliseconds() >= SHOOTING_RATE)
		{
			sf::Vector2i MousePosition = sf::Mouse::getPosition(Window);
			sf::Vector2f PlayerPosition = MainPlayer.getPosition();
			Bullets.push_back(
				std::make_unique<Bullet>(PlayerPosition,
										 atan2f(PlayerPosition.y - MousePosition.y,
												MousePosition.x - PlayerPosition.x),
										 ActualSeason)
			);


			ShotSound.stop();
			ShotSound.play();
			ShootingClock.restart();
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)
		   && ShootingClock.getElapsedTime().asMilliseconds() >= SHOOTING_RATE / 2)

		{
			std::random_device Device;

			Window.setView(sf::View(sf::Vector2f(std::uniform_real_distribution<float>(static_cast<int>(Window.getSize().x / 2) - 2, Window.getSize().x / 2 + 2)(Device),
												 std::uniform_real_distribution<float>(static_cast<int>(Window.getSize().y / 2) - 2, Window.getSize().y / 2 + 2)(Device)),
									sf::Vector2f(Window.getSize().x, Window.getSize().y)));
		}
		else
		{
			Window.setView(Window.getDefaultView());
		}
	}
}

void Game::spawnEnemies()
{
	std::random_device Device;

	const int NUMBER_OF_ENEMIES 
		= std::uniform_int_distribution<int>(2, 4)(Device);

	std::unique_ptr<Enemy> NewEnemy;
	for(int i = 0; i < NUMBER_OF_ENEMIES; ++i)
	{
		NewEnemy = std::make_unique<Enemy>(ActualSeason);

		bool wasCollisionDetected = false;

		do
		{
			sf::Vector2f NewPosition(
				std::uniform_int_distribution<unsigned int>(
					0, static_cast<unsigned int>(Window.getView().getSize().x - 32))(Device),
				std::uniform_int_distribution<unsigned int>(
					0, static_cast<unsigned int>(Window.getView().getSize().y - 32))(Device)
			);

			NewEnemy->setPosition(NewPosition);

			if(MainPlayer.checkBounds(*NewEnemy))
			{
				wasCollisionDetected = true;
			}

			for(size_t j = 0; j < Walls.size(); ++j)
			{
				if(NewEnemy->collide(*Walls[j]))
				{
					wasCollisionDetected = true;
				}
			}
		}
		while(!wasCollisionDetected);

		Enemies.push_back(std::move(NewEnemy));
	}
		
}

void Game::draw(sf::Time Delta)
{
	Window.clear(Colors[ActualSeason]);

	for(size_t i = 0; i < Walls.size(); ++i)
	{
		Window.draw(*Walls[i]);
	}

	for(size_t i = 0; i < Enemies.size(); ++i)
	{
		Enemies[i]->interpolate(Delta);
		Window.draw(*Enemies[i]);
	}

	for(size_t i = 0; i < Bullets.size(); ++i)
	{
		Bullets[i]->interpolate(Delta);
		Window.draw(*Bullets[i]);
	}

	if(!GameOver)
	{
		MainPlayer.interpolate(Delta);
		Window.draw(MainPlayer);

		Window.draw(Indicator);
	}
	else
	{
		Window.draw(GameOverText);
	}

	Window.display();
}

Game::~Game()
{
}
