#include "basic-bullet.hpp"
#include <iostream>
#include "input.hpp"
#include "othermath.h"
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

void BasicBullet::update(sf::Time frameTime) {
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds()){
        this->dead = true;
    }
    accelerate(sf::Vector2f(this->initialSpeed * cosf(getRotation() - 90 + offset), this->initialSpeed * sinf(getRotation() - 90 + offset)));
}


void BasicBullet::onDeath(){
    
}