#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "floatline.hpp"
#include "sfmlpch.hpp"

// 50 unit horizontal line
    FloatLine floatline1(sf::Vector2f(0,15), sf::Vector2f(20,15));
    // 50 unit vertical line
    FloatLine floatline2(sf::Vector2f(10,25), sf::Vector2f(10,5));
    sf::Vector2f pointOfCollision(0,0);

TEST_CASE( "FloatLine intersection", "[floatline]" ) {
    REQUIRE(floatline1.intersects(floatline2, &pointOfCollision) == true);
    REQUIRE(pointOfCollision == sf::Vector2f(10,15));
}