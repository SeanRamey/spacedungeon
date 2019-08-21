#ifndef COLLISION_TESTS_HPP
#define COLLISION_TESTS_HPP

#include "allpch.hpp"

namespace Collision {

	bool TestMovingAABB(
		sf::FloatRect box1,
		sf::FloatRect box2,
		sf::Vector2f vel1,
		sf::Vector2f vel2,
		float* timeOfCollision );

}

#endif
