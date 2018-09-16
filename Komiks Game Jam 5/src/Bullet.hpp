#pragma once
#include "Season.hpp"
#include "Wall.hpp"
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f Position, float Angle, Season Type);
	void update();
	void interpolate(sf::Time Delta);
	void collide(const Wall& ActualWall);
	void destroy() const;
	const sf::FloatRect getBounds() const;
	const Season getType() const;
	bool shouldBeRemoved() const;
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	~Bullet();

private:
	static sf::Image SpriteSheet;
	static bool wasSpriteSheetLoaded;

	static void loadSpriteSheet();

	const float SPEED = 15, LIFE_SPAN = 500;

	sf::RectangleShape Sprite;
	sf::Texture Texture;
	sf::Clock LifeClock;
	sf::Vector2f Direction, Position;
	Season Type;
	mutable bool wasDestroyed = false;
};

