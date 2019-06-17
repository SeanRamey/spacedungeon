#ifndef FLOATLINE_HPP
#define FLOATLINE_HPP

#include "sfmlpch.hpp"

class FloatLine {

public:
    FloatLine(float x1, float y1, float x2, float y2);
    FloatLine(sf::Vector2f point1, sf::Vector2f point2);
    FloatLine(const FloatLine& line);

    bool intersects(float x1, float y1, float x2, float y2);
    bool intersects(const FloatLine& otherLine);
    float length();
    FloatLine operator+(const FloatLine& line);
    FloatLine operator-(const FloatLine& line);

    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = 0;
};

#endif