#include "basic-bullet.hpp"
#include <iostream>
#include "input.hpp"
#include <othermath.h>
#include <cmath>
#include "player-ship.hpp"
#include "random-numbers.hpp"
#include "resources.hpp"
using namespace Input;

BasicBullet::BasicBullet(sf::Vector2f position, sf::Vector2u size, unsigned int MAX_SPEED, unsigned int DAMAGE, sf::Time maxTimeAlive):
Bullet(position, size, MAX_SPEED, DAMAGE, maxTimeAlive){
    offset = Util::GetRandomNumber(0, 8) - 4;
}

BasicBullet::~BasicBullet(){

}

void BasicBullet::checkCollision(Entity* entity){
    if(this->collisionBox.intersects(&entity->collisionBox)){
        if(entity->type == Entity::types::TILE){
            this->dead = true;
        } else if(entity->type == Entity::types::ALIEN_SHIP){
            // entity->damage(damage);
            this->dead = true;
        }
    }
}

void BasicBullet::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities){
    for(Entity* e : entities){
        if(e != this && dynamic_cast<PlayerShip*>(e) == nullptr){
            checkCollision(e);
        }
    }
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds()){
        this->dead = true;
    }
    addVelocity(sf::Vector2f(this->initialSpeed * cosf(degreesToRadians(angle - 90 + offset)), this->initialSpeed * sinf(degreesToRadians(angle - 90 + offset))));
    applyMovement(frameTime);
    collisionBox.update(position.x, position.y);
}


void BasicBullet::onDeath(){
    
}