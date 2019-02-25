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
		return Degrees / 180.0f * static_cast<float>(M_PI);
	}
}