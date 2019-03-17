#include "level.hpp"
#include "gun.hpp"
#include <iostream>

#include "resources.hpp"
#include "log.hpp"

using namespace Resources;
using namespace Input;

Gun::Gun(Entity* owner, Gun::Type gunType){
    this->owner = owner;
    this->gunType = gunType;
}

Gun::~Gun(){

}

void Gun::shoot(sf::Vector2f targetPosition){
    switch(gunType){
        case BASIC_GUN:
            {
                // TODO: Fix animations
                BasicBullet* bullet = new BasicBullet(owner->getPosition(), targetPosition, owner, owner->getLevel());
                //Bullet* bullet = new Bullet(owner->getPosition(), targetPosition, owner, sf::Vector2u(8,16), 1000, 1, owner->getLevel());
                // sf::Image image;
                // if(!image.loadFromFile("data/graphics/bullet_test.png")){
                //     Log::error("failed to load normal bullet texture");
                // }
                // Animation basicBulletAnimation = Animation(image, sf::Vector2u(8,16), basicBulletStateLengths);
                // bullet->setAnimation(basicBulletAnimation);
                // bullet->setDelay(sf::milliseconds(50));
                // bullet->setState(0);
                owner->getLevel()->addEntity(bullet);
                break;
            }
        case BIG_GUN:
            {
                SpecialBullet* specialBullet = new SpecialBullet(owner->getPosition(), targetPosition, owner, owner->getLevel());
                // sf::Image image;
                // if(!image.loadFromFile("data/graphics/big-bullet_test.png")){
                //     Log::error("failed to load special bullet texture");     
                // }
                // Animation specialBulletAnimation = Animation(image, sf::Vector2u(32,32), specialBulletStateLengths);
                // specialBullet->setAnimation(specialBulletAnimation);
                // specialBullet->setDelay(sf::milliseconds(100));
                // specialBullet->setState(0);
                owner->getLevel()->addEntity(specialBullet);
                break;
        }
    }
}

void Gun::setType(Gun::Type gunType){
    this->gunType = gunType;
}