#include "allpch.hpp"
#include <doctest/doctest.h>
#include "collision-tests.hpp"

TEST_CASE( "Collision::TestMovingAABB() intersection") {
	float time = 0.0f;

	SUBCASE( "perpendicular paths") {
		sf::FloatRect box1(5,0,1,1);
		sf::FloatRect box2(0,5,1,1);
		sf::Vector2f vel1(0,10);
		sf::Vector2f vel2(10,0);
		CHECK(Collision::TestMovingAABB(box1, box2, vel1, vel2, &time) == true);
		CHECK(time == 0.4f);
	}

	SUBCASE( "reverse perpendicular paths") {
		sf::FloatRect box1(8,16,4,4);
		sf::FloatRect box2(16,8,4,4);
		sf::Vector2f vel1(0,-20);
		sf::Vector2f vel2(-20,0);
		CHECK(Collision::TestMovingAABB(box1, box2, vel1, vel2, &time) == true);
		CHECK(time == 0.2f);
	}

	SUBCASE( "same start points") {
		sf::FloatRect box1(8,16,4,4);
		sf::FloatRect box2(8,16,4,4);
		sf::Vector2f vel1(-20,0);
		sf::Vector2f vel2(-20,0);
		CHECK(Collision::TestMovingAABB(box1, box2, vel1, vel2, &time) == true);
		CHECK(time == 0.0f);
	}

	SUBCASE( "equal singular axis velocities") {
		sf::FloatRect box1(20,16,4,4);
		sf::FloatRect box2(0,16,4,4);
		sf::Vector2f vel1(-20,0);
		sf::Vector2f vel2(20,0);
		CHECK(Collision::TestMovingAABB(box1, box2, vel1, vel2, &time) == true);
		CHECK(time == 0.4f);
	}

	SUBCASE( "same end points") {
		sf::FloatRect box1(0,10,4,4);
		sf::FloatRect box2(10,0,4,4);
		sf::Vector2f vel1(10,0);
		sf::Vector2f vel2(0,10);
		CHECK(Collision::TestMovingAABB(box1, box2, vel1, vel2, &time) == true);
		CHECK(time == 0.6f);
	}
}


TEST_CASE( "Collision::TestMovingAABB() non-intersection") {
	float time = 0.0f;

	SUBCASE( "parallel paths") {
		sf::FloatRect box1(0,0,4,4);
		sf::FloatRect box2(5,0,4,4);
		sf::Vector2f vel1(10,10);
		sf::Vector2f vel2(10,10);
		CHECK(Collision::TestMovingAABB(box1, box2, vel1, vel2, &time) == false);
		CHECK(time == 0.0f);
	}

	SUBCASE( "collinear paths") {
		sf::FloatRect box1(0,0,4,4);
		sf::FloatRect box2(5,5,4,4);
		sf::Vector2f vel1(10,10);
		sf::Vector2f vel2(10,10);
		CHECK(Collision::TestMovingAABB(box1, box2, vel1, vel2, &time) == false);
		CHECK(time == 0.0f);
	}
}
