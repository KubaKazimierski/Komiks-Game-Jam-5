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

#include "Enemy.hpp"

Enemy::Enemy(Season Type) 
	: Type(Type)
{
	switch(Type)
	{
	case Spring:
		Sprite.setFillColor(sf::Color(73, 89, 0));
		break;

	case Summer:
		Sprite.setFillColor(sf::Color::Yellow);
		break;

	case Autumn:
		Sprite.setFillColor(sf::Color::Magenta);
		break;

	case Winter:
		Sprite.setFillColor(sf::Color::Blue);
		break;
	}

	Sprite.setSize(sf::Vector2f(32, 32));
	Direction = sf::Vector2f(0, 0);
}

void Enemy::update(sf::Vector2f PlayerPosition)
{
	calcualateDirection(PlayerPosition);
	Position += Direction * SPEED;
}

void Enemy::calcualateDirection(sf::Vector2f PlayerPosition)
{
	float Angle = atan2f(Position.y - PlayerPosition.y,
						 PlayerPosition.x - Position.x);

	Direction = sf::Vector2f(cos(Angle), -sin(Angle));
}

void Enemy::interpolate(sf::Time Delta)
{
	Sprite.setPosition(Position + Direction * SPEED
					   * (static_cast<float>(Delta.asMilliseconds()) / (1000 / 60)));
}

bool Enemy::collide(const Wall& ActualWall)
{
	sf::FloatRect Intersection;
	Position = Sprite.getPosition();
	bool wasCollisionDetected = false;

	if(ActualWall.getBounds().intersects(Sprite.getGlobalBounds(), Intersection)
	   && Intersection.width > Intersection.height)
	{
		if(Intersection.top == Position.y)
		{
			Position.y += Intersection.height;

		}
		else
		{
			Position.y -= Intersection.height;
		}

		wasCollisionDetected = true;
	}

	if(ActualWall.getBounds().intersects(Sprite.getGlobalBounds(), Intersection)
	   && Intersection.width < Intersection.height)
	{
		if(Intersection.left == Position.x)
		{
			Position.x += Intersection.width;
		}
		else
		{
			Position.x -= Intersection.width;
		}

		wasCollisionDetected = true;
	}

	Sprite.setPosition(Position);

	return wasCollisionDetected;
}

void Enemy::collide(const Bullet& ActualBullet)
{
	if(ActualBullet.getBounds().intersects(Sprite.getGlobalBounds()))
	{
		ActualBullet.destroy();

		if(Type == (ActualBullet.getType() + 2) % 4)
		{
			--HP;
		}
	}
}

void Enemy::collide(const Enemy& ActualEnemy)
{
	sf::FloatRect Intersection;
	Position = Sprite.getPosition();
	bool wasCollisionDetected = false;

	if(ActualEnemy.getBounds().intersects(Sprite.getGlobalBounds(), Intersection)
	   && Intersection.width > Intersection.height)
	{
		if(Intersection.top == Position.y)
		{
			Position.y += Intersection.height;

		}
		else
		{
			Position.y -= Intersection.height;
		}

		wasCollisionDetected = true;
	}

	if(ActualEnemy.getBounds().intersects(Sprite.getGlobalBounds(), Intersection)
	   && Intersection.width < Intersection.height)
	{
		if(Intersection.left == Position.x)
		{
			Position.x += Intersection.width;
		}
		else
		{
			Position.x -= Intersection.width;
		}

		wasCollisionDetected = true;
	}

	Sprite.setPosition(Position);
}

void Enemy::setPosition(sf::Vector2f Position)
{
	this->Position = Position;
	Sprite.setPosition(Position);
}

sf::FloatRect Enemy::getBounds() const
{
	return Sprite.getGlobalBounds();
}

bool Enemy::shouldBeRemoved() const
{
	return HP <= 0;
}

void Enemy::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	Target.draw(Sprite, States);
}

Enemy::~Enemy()
{
}
