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

void BasicBullet::checkCollision(Entity* entity){

}

void BasicBullet::update(sf::Time frameTime, sf::RenderWindow* window){
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds()){
        this->dead = true;
    }
    addVelocity(sf::Vector2f(this->initialSpeed * cosf(degreesToRadians(angle - 90 + offset)), this->initialSpeed * sinf(degreesToRadians(angle - 90 + offset))));
    applyMovement(frameTime);
    collisionBox.update(position.x, position.y);
}
