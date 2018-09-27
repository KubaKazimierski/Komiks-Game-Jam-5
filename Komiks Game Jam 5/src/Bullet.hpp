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

