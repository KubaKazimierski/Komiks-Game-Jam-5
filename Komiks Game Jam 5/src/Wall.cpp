#include "Wall.hpp"

sf::Image Wall::SpriteSheet;
bool Wall::wasSpriteSheetLoaded = false;

Wall::Wall(sf::Vector2f Position)
{
	loadSpriteSheet();

	Sprite.setSize(sf::Vector2f(32, 32));
	Sprite.setPosition(Position);
}

void Wall::loadSpriteSheet()
{
	if(!wasSpriteSheetLoaded)
	{
		SpriteSheet.loadFromFile("assets/trees.png");
		wasSpriteSheetLoaded = true;
	}
}

void Wall::update(Season ActualSeason)
{
	if(ActualSeason != LastSeason)
	{
		SpriteTexture.loadFromImage(SpriteSheet,
									sf::IntRect(32 * ActualSeason, 0,
												32, 32));
		Sprite.setTexture(&SpriteTexture);

		LastSeason = ActualSeason;
	}
}

sf::FloatRect Wall::getBounds() const
{
	return Sprite.getGlobalBounds();
}

void Wall::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	Target.draw(Sprite, States);
}

Wall::~Wall()
{
}
