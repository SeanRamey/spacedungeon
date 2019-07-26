#include "sfmlpch.hpp"
#include <doctest/doctest.h>
#include "floatline.hpp"
#include <cmath>
#include <iostream>

TEST_CASE( "FloatLine perpendicular intersection test") {
    sf::Vector2f pointOfCollision(0,0);

    SUBCASE( "basic perpendicular intersection") {
        FloatLine floatline1(sf::Vector2f(2,0), sf::Vector2f(2,4));
        FloatLine floatline2(sf::Vector2f(0,2), sf::Vector2f(4,2));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 2);
        CHECK(pointOfCollision.y == 2);
    }

    SUBCASE( "fast perpendicular intersection") {
        FloatLine floatline1(sf::Vector2f(75,0), sf::Vector2f(75,150));
        FloatLine floatline2(sf::Vector2f(0,75), sf::Vector2f(150,75));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 75);
        CHECK(pointOfCollision.y == 75);
    }

    SUBCASE( "basic perpendicular intersection (endpoint)") {
        FloatLine floatline1(sf::Vector2f(4,0), sf::Vector2f(4,4));
        FloatLine floatline2(sf::Vector2f(0,2), sf::Vector2f(4,2));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 4);
        CHECK(pointOfCollision.y == 2);
    }

    SUBCASE( "diagonal perpendicular intersection") {
        FloatLine floatline1(sf::Vector2f(0,0), sf::Vector2f(4,4));
        FloatLine floatline2(sf::Vector2f(4,0), sf::Vector2f(0,4));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 2);
        CHECK(pointOfCollision.y == 2);
	}
}

TEST_CASE( "FloatLine parrallel intersection test") {
    sf::Vector2f pointOfCollision(0,0);

    SUBCASE( "horizontal indentical parrallel intersection") {
        FloatLine floatline1(sf::Vector2f(0,15), sf::Vector2f(20,15));
        FloatLine floatline2(sf::Vector2f(0,15), sf::Vector2f(20,15));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 0);
        CHECK(pointOfCollision.y == 15);
    }

    SUBCASE( "vertical identical parrallel intersection") {
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

	SUBCASE( "horizontal parrallel non-identical intersection") {
        FloatLine floatline1(sf::Vector2f(0,0), sf::Vector2f(30,0));
        FloatLine floatline2(sf::Vector2f(15,0), sf::Vector2f(30,0));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 30);
        CHECK(pointOfCollision.y == 0);
	}

    SUBCASE( "horizontal parrallel non-identical intersection 2") {
        FloatLine floatline1(sf::Vector2f(0,0), sf::Vector2f(5,0));
        FloatLine floatline2(sf::Vector2f(1,0), sf::Vector2f(3,0));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(std::roundf(pointOfCollision.x) == 2);
        CHECK(pointOfCollision.y == 0);
	}

    SUBCASE( "horizontal parallel non-identical intersection (backwards)") {
        FloatLine floatline1(sf::Vector2f(0,0), sf::Vector2f(5,0));
        FloatLine floatline2(sf::Vector2f(3,0), sf::Vector2f(1,0));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(std::roundf(pointOfCollision.x) == 2);
        CHECK(pointOfCollision.y == 0);
	}

    SUBCASE( "vertical parrallel non-identical intersection") {
        FloatLine floatline1(sf::Vector2f(0,0), sf::Vector2f(0,30));
        FloatLine floatline2(sf::Vector2f(0,15), sf::Vector2f(0,30));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 0);
        CHECK(pointOfCollision.y == 30);
	}

    SUBCASE( "diagonal parallel intersection") {
        FloatLine floatline1(sf::Vector2f(0,0), sf::Vector2f(4,4));
        FloatLine floatline2(sf::Vector2f(0,0), sf::Vector2f(4,4));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 0);
        CHECK(pointOfCollision.y == 0);
	}

    SUBCASE( "diagonal parallel non-identical intersection") {
        FloatLine floatline1(sf::Vector2f(0,0), sf::Vector2f(4,4));
        FloatLine floatline2(sf::Vector2f(2,2), sf::Vector2f(4,4));
        CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
        CHECK(pointOfCollision.x == 4);
        CHECK(pointOfCollision.y == 4);
	}

}

TEST_CASE( "FloatLine diagonal intersection test") {
    FloatLine floatline1(sf::Vector2f(0,25), sf::Vector2f(20,5));
    FloatLine floatline2(sf::Vector2f(20,25), sf::Vector2f(0,5));
    sf::Vector2f pointOfCollision(0,0);

    CHECK(floatline1.get_line_intersection(floatline2.x1, floatline2.y1, floatline2.x2, floatline2.y2, &pointOfCollision) == true);
    CHECK(pointOfCollision.x == 10);
    CHECK(pointOfCollision.y == 15);
}
