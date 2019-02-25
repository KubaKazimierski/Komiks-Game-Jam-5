/*
MIT License

Copyright (c) 2018-2019 Jakub Kazimierski

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include "Season.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "HPIndicator.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <random>
#include <cmath>

class Game
{
public:
	Game();
	void start();
	~Game();

private:
	static const int SHOOTING_RATE = 250,
		SEASON_CHANGE = 9000;
	static const sf::Color Colors[];
	

	sf::RenderWindow Window;
	sf::Clock ShootingClock, SeasonClock;
	sf::FloatRect GameArea;
	sf::Font Font;
	sf::Text GameOverText;
	sf::Music ShotSound;
	Player MainPlayer;
	std::vector<std::unique_ptr<Bullet>> Bullets;
	std::vector<std::unique_ptr<Wall>> Walls;
	std::vector<std::unique_ptr<Enemy>> Enemies;
	Season ActualSeason = Spring;
	HPIndicator Indicator;
	bool GameOver = false;

	void initMap();
	void update();	
	void processEvents();
	void handleInput();
	void spawnEnemies();
	void draw(sf::Time Delta);
};

