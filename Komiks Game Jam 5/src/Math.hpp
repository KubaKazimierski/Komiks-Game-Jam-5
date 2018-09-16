#pragma once
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Math
{
	sf::Vector2f calculateDirection(sf::Vector2f Input);
	float toRad(float Degrees);
}