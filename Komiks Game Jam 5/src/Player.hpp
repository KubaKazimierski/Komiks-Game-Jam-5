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

