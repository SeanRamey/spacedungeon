#include "basic-bullet.hpp"
#include <iostream>
#include "input.hpp"
#include "othermath.h"
#include <cmath>
#include "player-ship.hpp"
#include "random-numbers.hpp"
#include "resources.hpp"
using namespace Input;

BasicBullet::BasicBullet(sf::Vector2f position, sf::Vector2u size, unsigned int MAX_SPEED, unsigned int DAMAGE, Level* level):
Bullet(position, size, MAX_SPEED, DAMAGE, sf::milliseconds(3000), level){
    offset = Util::GetRandomNumber(0, 8) - 4;
}

BasicBullet::~BasicBullet(){

}

<<<<<<< HEAD:src/entities/basic-bullet.cpp
void BasicBullet::update(sf::Time frameTime) {
=======
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

void BasicBullet::update(sf::Time frameTime, sf::RenderWindow* window){
>>>>>>> master:src/entities/weapons/basic-bullet.cpp
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds()){
        this->dead = true;
    }
    accelerate(sf::Vector2f(this->initialSpeed * cosf(getRotation() - 90 + offset), this->initialSpeed * sinf(getRotation() - 90 + offset)));
}
