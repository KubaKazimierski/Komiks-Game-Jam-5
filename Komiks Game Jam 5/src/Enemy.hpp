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

