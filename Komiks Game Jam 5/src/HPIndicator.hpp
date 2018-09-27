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
#include <SFML/Graphics.hpp>
#include <memory>

class HPIndicator : public sf::Drawable
{
public:
	HPIndicator(sf::FloatRect GameArea);
	void update(unsigned int HP);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~HPIndicator();

private:
	static sf::Image SpriteSheet;
	static bool wasSpriteSheetLoaded;

	static void loadSpriteSheet();

	const sf::Vector2f SIZE = { 18, 18 };

	sf::Texture FullTexture, HalfTexture;
	sf::RectangleShape Rectangle;
	sf::IntRect GameArea;
	std::vector<std::unique_ptr<sf::Sprite>> Sprites;

	int HP = 0;
};

