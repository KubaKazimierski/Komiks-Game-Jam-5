#pragma once
#include "Season.hpp"
#include <SFML/Graphics.hpp>

class Wall : public sf::Drawable
{
public:
	Wall(sf::Vector2f Position);
	void update(Season ActualSeason);
	sf::FloatRect getBounds() const;
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	~Wall();

private:
	static sf::Image SpriteSheet;
	static bool wasSpriteSheetLoaded;

	static void loadSpriteSheet();

	sf::Texture SpriteTexture;
	Season LastSeason = Season::Winter;
	sf::RectangleShape Sprite;
};

