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
			static_cast<float>(GameArea.top + GameArea.height) - 52
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

		for(int i = 0; i < (HP / 2); ++i)
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
