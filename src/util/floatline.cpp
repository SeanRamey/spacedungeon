#include "floatline.hpp"
#include "stdpch.hpp"

FloatLine::FloatLine(float x1, float y1, float x2, float y2)
: x1(x1)
, y1(y1)
, x2(x2)
, y2(y2)
{
}

FloatLine::FloatLine(sf::Vector2f point1, sf::Vector2f point2)
: x1(point1.x)
, y1(point1.y)
, x2(point2.x)
, y2(point2.y)
{
}

FloatLine::FloatLine(const FloatLine& line)
: x1(line.x1)
, y1(line.y1)
, x2(line.x2)
, y2(line.y2)
{
}

bool FloatLine::intersects(float x1, float y1, float x2, float y2, sf::Vector2f* pointOfCollision) {

    // return no point of collision by default
    pointOfCollision->x = 0;
    pointOfCollision->y = 0;

    float A1 = y2- y1;
    float B1 = x1 - x2;
    float C1 = A1 * x1 + B1 * y1;
    float A2 = this->y2 - this->y1;
    float B2 = this->x1 - this->x2;
    float C2 = A2 * this->x1 + B2 * this->y1;
    float denominator = A1 * B2 - A2 * B1;

    if(denominator == 0) {
        return false;
    }

    float intersectX = (B2 * C1 - B1 * C2) / denominator;
    float intersectY = (A1 * C2 - A2 * C1) / denominator;
    float rx0 = (intersectX - x1) / (x2 - x1);
    float ry0 = (intersectY - y1) / (y2 - y1);
    float rx1 = (intersectX - this->x1) / (this->x2 - this->x1);
    float ry1 = (intersectY - this->y1) / (this->y2 - this->y1);

    if(((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) && ((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1))) {
        pointOfCollision->x = intersectX;
        pointOfCollision->y = intersectY;
        return true;
	} else {
        return false;
    }
}

bool FloatLine::intersects(const sf::Vector2f& p1, const sf::Vector2f& p2, sf::Vector2f* pointOfCollision) {

    // return no point of collision by default
    pointOfCollision->x = 0;
    pointOfCollision->y = 0;

    float A1 = p2.y - p1.y;
    float B1 = p1.x - p2.x;
    float C1 = A1 * p1.x + B1 * p1.y;
    float A2 = y2 - y1;
    float B2 = x1 - x2;
    float C2 = A2 * x1 + B2 * y1;
    float denominator = A1 * B2 - A2 * B1;

    if(denominator == 0) {
        return false;
    }

    float intersectX = (B2 * C1 - B1 * C2) / denominator;
    float intersectY = (A1 * C2 - A2 * C1) / denominator;
    float rx0 = (intersectX - p1.x) / (p2.x - p1.x);
    float ry0 = (intersectY - p1.y) / (p2.y - p1.y);
    float rx1 = (intersectX - x1) / (x2 - x1);
    float ry1 = (intersectY - y1) / (y2 - y1);

    if(((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) && ((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1))) {
        pointOfCollision->x = intersectX;
        pointOfCollision->y = intersectY;
        return true;
	} else {
        return false;
    }
}

bool FloatLine::intersects(const FloatLine& otherLine, sf::Vector2f* pointOfCollision) {

    // return no point of collision by default
    pointOfCollision->x = 0;
    pointOfCollision->y = 0;

    float A1 = otherLine.y2 - otherLine.y1;
    float B1 = otherLine.x1 - otherLine.x2;
    float C1 = A1 * otherLine.x1 + B1 * otherLine.y1;
    float A2 = y2 - y1;
    float B2 = x1 - x2;
    float C2 = A2 * x1 + B2 * y1;
    float denominator = A1 * B2 - A2 * B1;

    if(denominator == 0) {
        return false;
    }

    float intersectX = (B2 * C1 - B1 * C2) / denominator;
    float intersectY = (A1 * C2 - A2 * C1) / denominator;
    float rx0 = (intersectX - otherLine.x1) / (otherLine.x2 - otherLine.x1);
    float ry0 = (intersectY - otherLine.y1) / (otherLine.y2 - otherLine.y1);
    float rx1 = (intersectX - x1) / (x2 - x1);
    float ry1 = (intersectY - y1) / (y2 - y1);

    if(((rx0 >= 0 && rx0 <= 1) || (ry0 >= 0 && ry0 <= 1)) && ((rx1 >= 0 && rx1 <= 1) || (ry1 >= 0 && ry1 <= 1))) {
        pointOfCollision->x = intersectX;
        pointOfCollision->y = intersectY;
        return true;
	} else {
        return false;
    }
}

float FloatLine::length() {
    return sqrtf(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

FloatLine FloatLine::operator+(const FloatLine& line) {
    
}

FloatLine FloatLine::operator-(const FloatLine& line) {
    
}