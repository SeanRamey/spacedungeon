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


bool FloatLine::intersects(const sf::Vector2f& p1, const sf::Vector2f& p2, sf::Vector2f* pointOfCollision) {
    return intersects(p1.x, p1.y, p2.x, p2.y, pointOfCollision);
}


bool FloatLine::intersects(const FloatLine& otherLine, sf::Vector2f* pointOfCollision) {
    return intersects(otherLine.x1, otherLine.y1, otherLine.x2, otherLine.y2, pointOfCollision);
}


bool FloatLine::intersects(float x1, float y1, float x2, float y2, sf::Vector2f* pointOfCollision)
{

    // same start points always collide at the start point
    if(this->x1 == x1 && this->y1 == y1) {
        pointOfCollision->x = x1;
        pointOfCollision->y = y1;
        return true;
    }

    // same endpoints always collide at the end point
    if(this->y2 == y2 && this->x2 == x2) {
        pointOfCollision->x = x2;
        pointOfCollision->y = y2;
        return true;
    }

    float line1Width = this->x2 - this->x1;  // width of line1
    float line1Height = this->y2 - this->y1; // height of line1
    float line2Width = x2 - x1;              // width of line2
    float line2Height = y2 - y1;             // height of line2
    float xDistance = this->x1 - x1;      // width between the first points of both lines
    float yDistance = this->y1 - y1;     // height between the first points of both lines

    float denominator = (-line2Width * line1Height + line1Width * line2Height);

    // are lines parallel?
    if(denominator == 0) {

        float line1Slope = (line1Width) / (line1Height);
        float line2Slope = (line2Width) / (line2Height);
        float collinearSlope = (x1 - this->x1) / (y1 - this->y1); // slope of the first point on the first line to the first point on the second line

        float line1Length = this->length();
        float line2Length = sqrtf(pow(line2Width, 2) + pow(line2Height, 2));

        if(std::isinf(collinearSlope) && std::isinf(line1Slope) && std::isinf(line2Slope)) {
            line2Slope = line1Slope = collinearSlope = 0;
        }

        // are lines are collinear?
        if(line1Slope == line2Slope && collinearSlope == line1Slope) {
            
            // ensure line1Length always bigger
            if(line1Length < line2Length) {
                std::swap(line1Length, line2Length);
            }

			// determine if one of the lines is going the opposite direction
            bool isBackwards = x1 > x2 || y1 > y2;
            // find the point where collinear lines collide
            float diff = sqrtf(pow(std::fmax(x1, this->x1) - std::fmin(x1, this->x1), 2) + pow(std::fmax(y1, this->y1) - std::fmin(y1, this->y1), 2));
            float time = (diff)/(line1Length - (line2Length * (isBackwards ? -1 : 1)));
            if (time >= 0 && time <= 1){
                // Collision detected
                pointOfCollision->x = this->x1 + (time * line1Width);
                pointOfCollision->y = this->y1 + (time * line1Height);
                return true;
            } else {
                // Lines are parallel and co-linear, but don't intersect
                return false;
            }
	    }

        return false; // parallel lines that aren't co-linear will never intersect.
    }

    // s represents the percent of line1 from the start before the intersection.
    // t represents the percent of line2 from the start before the intersection.
    // for example, a line1 that is 10 units long with s = 0.5 will instersect with
    // line2 at 5 units from the starting point. Same applies to line2 and t.
    // s and t can be thought of in terms of time, as percent of total frame time.
    float s = (-line1Height * (xDistance) + line1Width * (yDistance)) / denominator;
    float t = ( line2Width * (yDistance) - line2Height * (xDistance)) / denominator;

    // for a line segment interection, s and t must be within 0.0 and 1.0.
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // Collision detected
        pointOfCollision->x = this->x1 + (t * line1Width);
        pointOfCollision->y = this->y1 + (t * line1Height);
        return true;
    }

    return false; // No collision
}


float FloatLine::length() {
    return sqrtf(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}




// psuedocode algorithm, might wanna keep this?
// float time = (difference in starting points)/(len_big - len_lil)
// if (time > 0 || time < 1){
//     // Collision detected
//     pointOfCollision->x = this->x1 + (time * line1Width);
//     pointOfCollision->y = this->y1 + (time * line1Height);
//     return true;
// } else {
//     no collision
//     std::cout << "Lines are parallel and co-linear, but don't intersect!\n";
//     return false;
// }
