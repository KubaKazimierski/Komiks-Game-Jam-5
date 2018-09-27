/*
   Season Shooter - a Komiks Game Jam 5 entry, theme: 'Seasons'
   Copyright 2018 Jakub Kazimierski

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
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
