#include "special-bullet.hpp"
#include "resources.hpp"
#include "player-ship.hpp"
#include "othermath.h"
#include <iostream>
#include "level.hpp"
#include "random-numbers.hpp"

SpecialBullet::SpecialBullet(sf::Vector2f position, sf::Vector2u size, unsigned int speed, unsigned int damage, Level* level) :
Bullet(position, size, speed, damage, sf::milliseconds(1000), level){
    numSplits = 8;
}

SpecialBullet::~SpecialBullet(){
}

void SpecialBullet::onDeath(){
    double degreeSplit = 360 / numSplits; // 45
    for(int i = 0; i < numSplits; i++){
        sf::Vector2f finalPosition;
        finalPosition.x = position.x + cosf(degreesToRadians(i * (degreeSplit + Util::GetRandomNumber(-5, 5))));
        finalPosition.y = position.y + sinf(degreesToRadians(i * (degreeSplit + Util::GetRandomNumber(-5, 5))));
        SpecialBulletShrapnel* shrapnel = new SpecialBulletShrapnel(position, finalPosition, sf::Vector2u(10, 10), 1500, 1, level); 
        shrapnel->setTexture(Resources::get(Resources::ID::SHRAPNEL));
        level->addEntity(shrapnel);
        level->getPlayer()->getSecondaryWeapon()->getBullets()->push_back(shrapnel);
    }
}

void SpecialBullet::update(sf::Time frameTime, sf::RenderWindow* window){ 
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds()){
        this->dead = true;
    }
    addVelocity(sf::Vector2f(this->initialSpeed * cosf(degreesToRadians(angle - 90)), this->initialSpeed * sinf(degreesToRadians(angle - 90))));
    applyMovement(frameTime);
    collisionBox.update(position.x, position.y);
}

void SpecialBullet::checkCollision(Entity* entity){
     
}
