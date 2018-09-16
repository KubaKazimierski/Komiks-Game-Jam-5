#pragma once
#include "Wall.hpp"
#include "Season.hpp"
#include "Bullet.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class Enemy : public sf::Drawable
{
public:
	Enemy(Season Type);
	void update(sf::Vector2f PlayerPosition);
	void interpolate(sf::Time Delta);
	bool collide(const Wall& ActualWall);
	void collide(const Bullet& ActualBullet);
	void collide(const Enemy& ActualEnemy);
	void setPosition(sf::Vector2f Position);
	sf::FloatRect getBounds() const;
	bool shouldBeRemoved() const;
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	~Enemy();

private:
	const float SPEED = 1;

	sf::RectangleShape Sprite;
	sf::Vector2f Direction, Position;
	Season Type;
	int HP = 4;

	void calcualateDirection(sf::Vector2f PlayerPosition);
};

