#include "special-bullet-split.hpp"
#include "othermath.h"
#include "entity.hpp"
#include "player-ship.hpp"
#include "cmath"

void SpecialBulletShrapnel::update(sf::Time frameTime, sf::RenderWindow* window){
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds() || this->position == finalPosition){
        this->dead = true;
    }
    addVelocity(sf::Vector2f(this->initialSpeed * cosf(degreesToRadians(angle - 90)), this->initialSpeed * sinf(degreesToRadians(angle - 90))));
    applyMovement(frameTime);
    collisionBox.update(position.x, position.y); 
}

SpecialBulletShrapnel::SpecialBulletShrapnel(sf::Vector2f position, sf::Vector2f finalPosition, sf::Vector2u size, unsigned int speed, unsigned int damage, Level* level) :
Bullet(position, finalPosition, size, speed, damage, sf::milliseconds(10), level){
    this->finalPosition = finalPosition;
}

SpecialBulletShrapnel::~SpecialBulletShrapnel(){

}


