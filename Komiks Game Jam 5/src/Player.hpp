#pragma once
#include "Math.hpp"
#include "Wall.hpp"
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


class Player : public sf::Drawable
{
public:
	Player();
	void update();
	void interpolate(sf::Time Delta);
	void handleInput();
	sf::Vector2f getPosition() const;
	void collide(const Wall& ActualWall);
	void collide(const Enemy& ActualEnemy);
	bool checkBounds(const Enemy& ActualEnemy);
	const unsigned int getHP();
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	~Player();

private:
	const float ACCELERATION = 1.0f,
			  DECELERATION = 0.8f,
			  MAX_SPEED = 5;

	sf::RectangleShape Sprite;
	sf::Clock CollisionClock, BlinkClock;
	sf::Vector2f Direction, Position, Input;
	sf::Texture Texture;

	float Speed = 0;
	int HP = 12;
	mutable bool isBlinking = false, shouldBeDrawn = true;
};

