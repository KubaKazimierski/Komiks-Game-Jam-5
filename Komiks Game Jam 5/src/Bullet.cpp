#include "Bullet.hpp"

sf::Image Bullet::SpriteSheet;
bool Bullet::wasSpriteSheetLoaded = false;

Bullet::Bullet(sf::Vector2f Position, float Angle, Season Type)
	: Position(Position), Type(Type)
{
	loadSpriteSheet();

	Direction = sf::Vector2f(cos(Angle), -sin(Angle));
	Sprite.setSize(sf::Vector2f(16, 16));
	Sprite.setPosition(Position);

	Texture.loadFromImage(SpriteSheet,
						  sf::IntRect(32 * Type, 0,
										32, 32));
	Sprite.setTexture(&Texture);

}

void Bullet::loadSpriteSheet()
{
	if(!wasSpriteSheetLoaded)
	{
		SpriteSheet.loadFromFile("assets/Bullets.png");
		wasSpriteSheetLoaded = true;
	}
}

void Bullet::update()
{
	Position += Direction * SPEED;
}

void Bullet::interpolate(sf::Time Delta)
{
	Sprite.setPosition(Position + Direction * SPEED * (static_cast<float>(Delta.asMilliseconds()) / 1000 / 60));
}

void Bullet::collide(const Wall& ActualWall)
{
	if(ActualWall.getBounds().intersects(Sprite.getGlobalBounds()))
	{
		destroy();
	}
}

void Bullet::destroy() const
{
	wasDestroyed = true;
}

const sf::FloatRect Bullet::getBounds() const
{
	return Sprite.getGlobalBounds();
}

const Season Bullet::getType() const
{
	return Type;
}

bool Bullet::shouldBeRemoved() const
{
	return (LifeClock.getElapsedTime().asMilliseconds() > LIFE_SPAN)
		|| wasDestroyed;
}

void Bullet::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	Target.draw(Sprite, States);
}

Bullet::~Bullet()
{
}
