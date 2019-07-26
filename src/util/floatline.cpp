#include "floatline.hpp"
#include "stdpch.hpp"
#include <cfloat>

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

    float A1 = y2 - y1;
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

bool FloatLine::get_line_intersection(float x1, float y1, float x2, float y2, sf::Vector2f* pointOfCollision)
{

    // start point collision
    if(this->x1 == x1 && this->y1 == y1) {
        std::cout << "Lines start at same point!\n";
        pointOfCollision->x = x1;
        pointOfCollision->y = y1;
        return true;
    }

    // last point collision endcase
    if(this->y2 == y2 && this->x2 == x2) {
        std::cout << "Lines end at same point!\n";
        pointOfCollision->x = x2;
        pointOfCollision->y = y2;
        return true;
    }

    float width1 = this->x2 - this->x1; // width of line1
    float height1 = this->y2 - this->y1; // height of line1
    float width2 = x2 - x1;             // width of line2
    float height2 = y2 - y1;             // height of line2
    float width1_1 = this->x1 - x1;     // width between the first points of both lines
    float height1_1 = this->y1 - y1;    // height between the first points of both lines

    float denominator = (-width2 * height1 + width1 * height2);

    // handle parallel lines
    if(denominator == 0) {

        float slope1 = (width1) / (height1);
        float slope2 = (width2) / (height2);
        float slope1_1 = (x1 - this->x1) / (y1 - this->y1); // slope of the first point on the first line to the first point on the second line

        float length1 = this->length(); //sqrtf(pow(width1, 2) + pow(height1, 2));
        float length2 = sqrtf(pow(width2, 2) + pow(height2, 2));

        // hack to avoid division by zero
        // if(height1 == 0 || width1 == 0) slope1 = 0;
        // if(height2 == 0 || width2 == 0) slope2 = 0;
        // if(height1_1 == 0 || width1_1 == 0) slope1_1 = 0;

        std::cout << "slope1=" << slope1 << "\n";
        std::cout << "slope1_1=" << slope1_1 << "\n";
        std::cout << "slope2=" << slope2 << "\n";

        // test if lines are collinear
        if(slope1 == slope2 && slope1_1 == slope1) {
            std::cout << "Lines are collinear!\n";

            // float time = (difference in starting points)/(len_big - len_lil)
            // if (time > 0 || time < 1){
            //     // Collision detected
            //     pointOfCollision->x = this->x1 + (time * width1);
            //     pointOfCollision->y = this->y1 + (time * height1);
            //     return true;
            // } else {
            //     no collision
            //     std::cout << "Lines are parallel and co-linear, but don't intersect!\n";
            //     return false;
            // }
            
            float swpLength;
            if(length1 < length2) {
                swpLength = length2;
                length2 = length1;
                length1 = swpLength;
                std::cout << "lengths swapped\n";
            }

            std::cout << "length1=" << length1 << "\n";
            std::cout << "length2=" << length2 << "\n";

            float diff = x1 - this->x1;
            float time = (diff)/(length1 - length2);
            if (time > 0 || time < 1){
                // Collision detected
                std::cout << "time=" << time << "\n";
                pointOfCollision->x = this->x1 + (time * width1);
                pointOfCollision->y = this->y1 + (time * height1);
                return true;
            } else {
                //no collision
                std::cout << "Lines are parallel and co-linear, but don't intersect!\n";
                return false;
            }

	    }

        std::cout << "Lines are parallel and not co-linear!\n";
        return false; // parallel lines that aren't co-linear will never intersect.
    }

    // s represents the percent of line1 from the start before the intersection.
    // t represents the percent of line2 from the start before the intersection.
    // for example, a line1 that is 10 units long with s = 0.5 will instersect with
    // line2 at 5 units from the starting point. Same applies to line2 and t.
    // s and t can be thought of in terms of time, as percent of total frame time.
    float s = (-height1 * (width1_1) + width1 * (height1_1)) / denominator;
    float t = ( width2 * (height1_1) - height2 * (width1_1)) / denominator;

    // for a line segment interection, s and t must be within 0.0 and 1.0.
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // Collision detected
        pointOfCollision->x = this->x1 + (t * width1);
        pointOfCollision->y = this->y1 + (t * height1);
        return true;
    }

    return false; // No collision
}

float FloatLine::length() {
    return sqrtf(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

FloatLine FloatLine::operator+(const FloatLine& line) {
    
}

FloatLine FloatLine::operator-(const FloatLine& line) {
    
}
