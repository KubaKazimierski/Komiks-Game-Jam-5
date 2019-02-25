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

#include "HPIndicator.hpp"

sf::Image HPIndicator::SpriteSheet;
bool HPIndicator::wasSpriteSheetLoaded = false;

HPIndicator::HPIndicator(sf::FloatRect GameArea)
	: GameArea(GameArea)
{
	loadSpriteSheet();
	Rectangle.setFillColor(sf::Color(121, 121, 121, 200));
	Rectangle.setSize({ 200, 52});
	Rectangle.setPosition(
		{
			static_cast<float>(GameArea.left),
			static_cast<float>(GameArea.top + GameArea.height) - 50
		}
	);
	FullTexture.loadFromImage(SpriteSheet, sf::IntRect(0, 0, static_cast<int>(SIZE.x), static_cast<int>(SIZE.y)));
	HalfTexture.loadFromImage(SpriteSheet, sf::IntRect(static_cast<int>(SIZE.x), 0, static_cast<int>(SIZE.x), static_cast<int>(SIZE.y)));
}

void HPIndicator::loadSpriteSheet()
{
	if(!wasSpriteSheetLoaded)
	{
		SpriteSheet.loadFromFile("assets/Heart.png");
		wasSpriteSheetLoaded = true;
	}
}

void HPIndicator::update(unsigned int HP)
{
	if(this->HP != HP)
	{
		Sprites.clear();

		for(size_t i = 0; i < (HP / 2); ++i)
		{
			std::unique_ptr<sf::Sprite> NewSprite
				= std::make_unique<sf::Sprite>();

			NewSprite->setTexture(FullTexture);
			NewSprite->setScale(1.5f, 1.5f);
			NewSprite->setPosition(
				static_cast<float>(GameArea.left) + 10 + (NewSprite->getGlobalBounds().width + 2)  * i,
				static_cast<float>(GameArea.top + GameArea.height) - NewSprite->getGlobalBounds().height - 10
			);

			Sprites.push_back(std::move(NewSprite));
		}

		if(HP & 1)
		{
			std::unique_ptr<sf::Sprite> NewSprite
				= std::make_unique<sf::Sprite>();

			NewSprite->setTexture(HalfTexture);
			NewSprite->setScale(1.5f, 1.5f);
			NewSprite->setPosition(
				static_cast<float>(GameArea.left) + 10 + (NewSprite->getGlobalBounds().width + 2)  * Sprites.size(),
				static_cast<float>(GameArea.top + GameArea.height) - NewSprite->getGlobalBounds().height - 10
			);

			Sprites.push_back(std::move(NewSprite));
		}

		this->HP = HP;
	}
}

void HPIndicator::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	Target.draw(Rectangle, States);
	for(size_t i = 0; i < Sprites.size(); ++i)
	{
		Target.draw(*Sprites[i], States);
	}
}

HPIndicator::~HPIndicator()
{
}
