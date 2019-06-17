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
, x2(line.x2)
, y1(line.y1)
, y2(line.y2)
{
}

bool FloatLine::intersects(float x1, float y1, float x2, float y2) {
	// FloatLine v(y)  [ d[0]-c[0], d[1]-c[1] ];
	// float u = [ b[0]-a[0], b[1]-a[1] ];

	// float d = u[0]*v[1] - u[1]*v[0];
	// float r = ((a[1]-c[1])*v[0] - (a[0]-c[0])*v[1]) / d;
	// float s = ((a[1]-c[1])*u[0] - (a[0]-c[0])*u[1]) / d;

	// return (0<=r && r<=1 && 0<=s && s<=1);

////////////////////

    //Cross Product (hope I got it right here)
    // float fC= (B.x*C.y) - (B.y*C.x); //<0 == to the left, >0 == to the right
    // float fD= (B.x*D.y) - (B.y*D.x);

    // if( (fc<0) && (fd<0)) //both to the left  -> No Cross!
    // if( (fc>0) && (fd>0)) //both to the right -> No Cross!


//////////////////////

    // denom = ((LineB2.Y – LineB1.Y) * (LineA2.X – LineA1.X)) – ((LineB2.X – LineB1.X) * (LineA2.Y - LineA1.Y))
	// if (denom == 0)
	// 	return null
	// else
	// 	ua = (((LineB2.X – LineB1.X) * (LineA1.Y – LineB1.Y)) –
	// 		((LineB2.Y – LineB1.Y) * (LineA1.X – LineB1.X))) / denom
	// 	/* The following 3 lines are only necessary if we are checking line
	// 		segments instead of infinite-length lines */
	// 	ub = (((LineA2.X – LineA1.X) * (LineA1.Y – LineB1.Y)) –
	// 		((LineA2.Y – LineA1.Y) * (LineA1.X – LineB1.X))) / denom
	// 	if (ua < 0) || (ua > 1) || (ub < 0) || (ub > 1)
	// 		return null

	// 	return LineA1 + ua * (LineA2 – LineA1)

    float denominator = ((y2 - y1) * (this->x2 - this->x1)) - ((x2 - x1) * (this->y2 - this->y1));

    if(denominator == 0) {
        return false;
    }

    float ua = (((x2 - x1) * (this->y1 - y1)) - ((y2 - y1) * (this->x1 - x1))) / denominator;
    float ub = (((this->x2 - this->x1) * (this->y1 - y1)) - ((this->y2 - this->y1) * (this->x1 - x1))) / denominator;

    if(ua < 0 || ua > 1 || ub < 0 || ub > 1) {
        return false;
    }

    return true;
    //return LineA1 + ua * (LineA2 – LineA1) // returns point of collision
}

bool FloatLine::intersects(const FloatLine& otherLine) {

    float denominator = ((otherLine.y2 - otherLine.y1) * (this->x2 - this->x1)) - ((otherLine.x2 - otherLine.x1) * (this->y2 - this->y1));

    if(denominator == 0) {
        return false;
    }

    float ua = (((otherLine.x2 - otherLine.x1) * (this->y1 - otherLine.y1)) - ((otherLine.y2 - otherLine.y1) * (this->x1 - otherLine.x1))) / denominator;
    float ub = (((this->x2 - this->x1) * (this->y1 - otherLine.y1)) - ((this->y2 - this->y1) * (this->x1 - otherLine.x1))) / denominator;

    if(ua < 0 || ua > 1 || ub < 0 || ub > 1) {
        return false;
    }

    return true;
    //return LineA1 + ua * (LineA2 – LineA1) // returns point of collision
}

float length() {
    return sqrtf(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

FloatLine FloatLine::operator+(const FloatLine& line) {
    if(line.length() > this->length()) {
        return  line.length() - this->length();
    } else {
        return this->length() - line.length();
    }
}

FloatLine FloatLine::operator-(const FloatLine& line) {

}