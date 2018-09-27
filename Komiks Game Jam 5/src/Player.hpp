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
#include "Math.hpp"
#include "Wall.hpp"
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


class Player : public sf::Drawable
{
public:
	Player();
	void update();
	void interpolate(sf::Time Delta);
	void handleInput();
	sf::Vector2f getPosition() const;
	void collide(const Wall& ActualWall);
	void collide(const Enemy& ActualEnemy);
	bool checkBounds(const Enemy& ActualEnemy);
	const unsigned int getHP();
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	~Player();

private:
	const float ACCELERATION = 1.0f,
			  DECELERATION = 0.8f,
			  MAX_SPEED = 5;

	sf::RectangleShape Sprite;
	sf::Clock CollisionClock, BlinkClock;
	sf::Vector2f Direction, Position, Input;
	sf::Texture Texture;

	float Speed = 0;
	int HP = 12;
	mutable bool isBlinking = false, shouldBeDrawn = true;
};

