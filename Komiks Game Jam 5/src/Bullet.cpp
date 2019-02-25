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
