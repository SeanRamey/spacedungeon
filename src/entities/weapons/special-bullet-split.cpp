#include "special-bullet-split.hpp"
#include "othermath.h"
#include "entity.hpp"
#include "player-ship.hpp"
#include "cmath"

void SpecialBulletShrapnel::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities){
    for(Entity* e : entities){
        if(e != this && dynamic_cast<PlayerShip*>(e) == nullptr){
            checkCollision(e);
        }
    }
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds() || this->position == finalPosition){
        this->dead = true;
    }
    addVelocity(sf::Vector2f(this->initialSpeed * cosf(degreesToRadians(angle - 90)), this->initialSpeed * sinf(degreesToRadians(angle - 90))));
    applyMovement(frameTime);
    collisionBox.update(position.x, position.y); 
}

SpecialBulletShrapnel::SpecialBulletShrapnel(sf::Vector2f position, sf::Vector2u size, unsigned int speed, unsigned int damage) :
Bullet(position, size, speed, damage, sf::milliseconds(5000)){

}

SpecialBulletShrapnel::~SpecialBulletShrapnel(){

}


