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
