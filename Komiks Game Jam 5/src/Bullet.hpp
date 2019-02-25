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
#include "Season.hpp"
#include "Wall.hpp"
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable
{
public:
	Bullet(sf::Vector2f Position, float Angle, Season Type);
	void update();
	void interpolate(sf::Time Delta);
	void collide(const Wall& ActualWall);
	void destroy() const;
	const sf::FloatRect getBounds() const;
	const Season getType() const;
	bool shouldBeRemoved() const;
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	~Bullet();

private:
	static sf::Image SpriteSheet;
	static bool wasSpriteSheetLoaded;

	static void loadSpriteSheet();

	const float SPEED = 15, LIFE_SPAN = 500;

	sf::RectangleShape Sprite;
	sf::Texture Texture;
	sf::Clock LifeClock;
	sf::Vector2f Direction, Position;
	Season Type;
	mutable bool wasDestroyed = false;
};

