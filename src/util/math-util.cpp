#include "math-util.hpp"

namespace Math {

	float calculateAngleFromTo(sf::Vector2f fromPosition, sf::Vector2f toPosition) {
		sf::Vector2f temp;
		temp.x = fromPosition.x - toPosition.x;
		temp.y = fromPosition.y - toPosition.y;
		float newAngle = 0;
		if(temp.x == 0) temp.x += FLT_MIN;
		if(temp.y == 0) temp.y += FLT_MIN;
		if(temp.x != 0 && temp.y != 0) {
			newAngle = radiansToDegrees(atanf((temp.y) / (temp.x)));
			if(toPosition.x > fromPosition.x){
				newAngle += 180;
			}
		} else
		if(temp.x > 0) {
			newAngle = 300;
		}
		return newAngle;
	}
}
