#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void start();
	~Game();

private:
	sf::RenderWindow Window;

	void update();
	void processEvents();
	void draw(sf::Time Delta);
};

