#include "Math.hpp"

namespace Math
{
	sf::Vector2f calculateDirection(sf::Vector2f Input)
	{
		float Angle = 0;

		if(Input.y != 0)
		{
			if(Input.y == -1)
			{
				Angle = 90;
			}
			else
			{
				Angle = 270;
			}

			if(Input.x != 0)
			{
				if(Angle < 180)
				{
					Input.x *= -1;
				}

				Angle += 45 * Input.x;
			}

		}
		else if(Input.x != 0)
		{
			if(Input.x == -1)
			{
				Angle = 180;
			}
		}

		Angle = toRad(Angle);
		return sf::Vector2f(cos(Angle), -sin(Angle));
	}

	float toRad(float Degrees)
	{
		return Degrees / 180 * M_PI;
	}
}