#include "allpch.hpp"
#include <doctest/doctest.h>
#include "collision-tests.hpp"

TEST_CASE( "Collision::TestMovingAABB() intersection") {
    float time = 0.0f;

    SUBCASE( "perpendicular paths") {
        sf::FloatRect box1(5,0,3,3);
        sf::FloatRect box2(0,5,3,3);
        sf::Vector2f vel1(0,10);
        sf::Vector2f vel2(10,0);
        CHECK(Collision::TestMovingAABB(box1, box2, vel1, vel2, &time) == true);
        CHECK(time == 0.5f);
    }
}
