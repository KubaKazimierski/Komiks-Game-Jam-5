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