#include "Player.hpp"


Player::Player()
{
	Texture.loadFromFile("assets/Player.png");
	Sprite.setTexture(&Texture);
	Sprite.setSize(sf::Vector2f(32, 32));
	Position = sf::Vector2f(64, 64);
	Direction = sf::Vector2f(0, 0);
}

void Player::update()
{
	if(Speed < MAX_SPEED 
	   && Input != sf::Vector2f(0, 0))
	{
		Speed += ACCELERATION;
	}
	else if(Speed > 0 && Input == sf::Vector2f(0, 0))
	{
		Speed -= DECELERATION;

		if(Speed < 0)
		{
			Speed = 0;
		}
	}

	Position += Direction * Speed;
}

void Player::interpolate(sf::Time Delta)
{
	Sprite.setPosition(Position + Direction * Speed 
					   * (static_cast<float>(Delta.asMilliseconds()) / (1000 / 60)));
}

void Player::handleInput()
{
	Input = sf::Vector2f(0, 0);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Input.y -= 1;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Input.y += 1;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Input.x -= 1;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Input.x += 1;
	}

	if(Input != sf::Vector2f(0, 0))
	{
		Direction = Math::calculateDirection(Input);
	}
}

sf::Vector2f Player::getPosition() const
{
	return Position;
}

void Player::collide(const Wall& ActualWall)
{
	sf::FloatRect Intersection;
	Position = Sprite.getPosition();

	if(ActualWall.getBounds().intersects(Sprite.getGlobalBounds(), Intersection)
	   && Intersection.width > Intersection.height)
	{
		if(Intersection.top == Position.y)
		{
			Position.y += Intersection.height;

		}
		else
		{
			Position.y -= Intersection.height;
		}
		Speed = 0;
	}

	if(ActualWall.getBounds().intersects(Sprite.getGlobalBounds(), Intersection)
			&& Intersection.width < Intersection.height)
	{
		if(Intersection.left == Position.x)
		{
			Position.x += Intersection.width;
		}
		else
		{
			Position.x -= Intersection.width;
		}

		Speed = 0;
	}

	Sprite.setPosition(Position);
}

void Player::collide(const Enemy& ActualEnemy)
{
	if(checkBounds(ActualEnemy) && HP != 0
	   && CollisionClock.getElapsedTime().asMilliseconds() > 500)
	{
		--HP;
		isBlinking = true;
		BlinkClock.restart();
		CollisionClock.restart();
	}
}

bool Player::checkBounds(const Enemy& ActualEnemy)
{
	bool wasCollisionDetected = false;
	if(ActualEnemy.getBounds().intersects(Sprite.getGlobalBounds()))
	{
		wasCollisionDetected = true;
	}

	return wasCollisionDetected;
}

const unsigned int Player::getHP()
{
	return HP;
}

void Player::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{

	if(isBlinking)
	{
		sf::Time  Delta = BlinkClock.getElapsedTime();

		if(Delta.asMilliseconds() % 100 == 0)
		{
			shouldBeDrawn = !shouldBeDrawn;
		}

		if(Delta.asMilliseconds() > 500)
		{
			isBlinking = false;
			shouldBeDrawn = true;
		}
	}

	if(shouldBeDrawn)
	{
		Target.draw(Sprite, States);
	}
}

Player::~Player()
{
}
