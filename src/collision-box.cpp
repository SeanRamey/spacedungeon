#include "collision-box.hpp"
CollisionBox::CollisionBox(float x = 0, float y = 0, unsigned int w = 0, unsigned int h = 0){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

CollisionBox::~CollisionBox(){

}

void CollisionBox::update(float x, float y){

    this->x = x - w / 2;
    this->y = y - h / 2;
}

bool CollisionBox::intersects(CollisionBox* comparer){
        return this->x < comparer->x + comparer->w &&
        this->x + this->w > comparer->x &&
        this->y < comparer->y + comparer->h &&
        this->y + this->h > comparer->y;
}

