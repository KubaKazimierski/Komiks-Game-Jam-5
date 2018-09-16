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

