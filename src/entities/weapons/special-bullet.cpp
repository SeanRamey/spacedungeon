#include "special-bullet.hpp"
#include "player-ship.hpp"
#include "othermath.h"
#include <iostream>

SpecialBullet::SpecialBullet(sf::Vector2f position, sf::Vector2u size, unsigned int speed, unsigned int damage) :
Bullet(position, size, speed, damage, sf::milliseconds(3000)){
}

SpecialBullet::~SpecialBullet(){
}

void SpecialBullet::onDeath(){
    float degreeSplit = 360 / numSplits;
    for(int i = 0; i < numSplits; i++){
        sf::Vector2f finalPosition;
        finalPosition.x = position.x + 1;
    }
}

void SpecialBullet::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities){
    for(Entity* e : entities){
        if(e != this && dynamic_cast<PlayerShip*>(e) == nullptr){
            checkCollision(e);
        }
    }
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds()){
        this->dead = true;
    }
    addVelocity(sf::Vector2f(this->initialSpeed * cosf(degreesToRadians(angle - 90)), this->initialSpeed * sinf(degreesToRadians(angle - 90))));
    applyMovement(frameTime);
    collisionBox.update(position.x, position.y);
}

void SpecialBullet::checkCollision(Entity* entity){
     
}