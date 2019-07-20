#include "sfmlpch.hpp"
#include <doctest/doctest.h>
#include "floatline.hpp"

TEST_CASE( "FloatLine perpendicular intersection test") {
    FloatLine floatline1(sf::Vector2f(0,15), sf::Vector2f(20,15));
    FloatLine floatline2(sf::Vector2f(10,25), sf::Vector2f(10,5));
    sf::Vector2f pointOfCollision(0,0);

    CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
    CHECK(pointOfCollision.x == 10);
    CHECK(pointOfCollision.y == 15);
}

TEST_CASE( "FloatLine parrallel intersection test") {
    sf::Vector2f pointOfCollision(0,0);

    SUBCASE( "horizontal parrallel intersection") {
        FloatLine floatline1(sf::Vector2f(0,15), sf::Vector2f(20,15));
        FloatLine floatline2(sf::Vector2f(0,15), sf::Vector2f(20,15));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 0);
        CHECK(pointOfCollision.y == 15);
    }

    SUBCASE( "vertical parrallel intersection") {
        FloatLine floatline1(sf::Vector2f(10,5), sf::Vector2f(10,25));
        FloatLine floatline2(sf::Vector2f(10,5), sf::Vector2f(10,25));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 10);
        CHECK(pointOfCollision.y == 5);
    }

    SUBCASE( "horizontal parrallel non-intersection") {
        FloatLine floatline1(sf::Vector2f(0,16), sf::Vector2f(20,16));
        FloatLine floatline2(sf::Vector2f(0,15), sf::Vector2f(20,15));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == false);
    }

    SUBCASE( "vertical parrallel non-intersection") {
        FloatLine floatline1(sf::Vector2f(11,5), sf::Vector2f(11,25));
        FloatLine floatline2(sf::Vector2f(10,5), sf::Vector2f(10,25));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == false);
    }
}

TEST_CASE( "FloatLine 45 degree intersection test") {
    FloatLine floatline1(sf::Vector2f(0,25), sf::Vector2f(20,5));
    FloatLine floatline2(sf::Vector2f(20,25), sf::Vector2f(0,5));
    sf::Vector2f pointOfCollision(0,0);

    CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
    CHECK(pointOfCollision.x == 10);
    CHECK(pointOfCollision.y == 15);
}