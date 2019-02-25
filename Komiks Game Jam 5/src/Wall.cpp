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
