#ifndef MATH_UTIL
#define MATH_UTIL

#include "allpch.hpp"

#ifndef M_PI
#define M_PI 3.1415926535
#endif

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

namespace Math {
	float calculateAngleFromTo(sf::Vector2f fromPosition, sf::Vector2f toPosition);
}

#endif
