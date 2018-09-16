#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class HPIndicator : public sf::Drawable
{
public:
	HPIndicator(sf::FloatRect GameArea);
	void update(unsigned int HP);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~HPIndicator();

private:
	static sf::Image SpriteSheet;
	static bool wasSpriteSheetLoaded;

	static void loadSpriteSheet();

	const sf::Vector2f SIZE = { 18, 18 };

	sf::Texture FullTexture, HalfTexture;
	sf::RectangleShape Rectangle;
	sf::IntRect GameArea;
	std::vector<std::unique_ptr<sf::Sprite>> Sprites;

	int HP = 0;
};

