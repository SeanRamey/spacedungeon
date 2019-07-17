#include "sfmlpch.hpp"
#include <doctest/doctest.h>
#include "floatline.hpp"

TEST_CASE( "FloatLine intersection test") {
    // 50 unit horizontal line
    FloatLine floatline1(sf::Vector2f(0,15), sf::Vector2f(20,15));
    // 50 unit vertical line
    FloatLine floatline2(sf::Vector2f(10,25), sf::Vector2f(10,5));
    sf::Vector2f pointOfCollision(0,0);

    CHECK(floatline1.intersects(floatline2, &pointOfCollision) == true);
    CHECK(pointOfCollision == sf::Vector2f(10,15));
}