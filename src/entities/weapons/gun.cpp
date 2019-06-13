#include "stdpch.hpp"

#include "level.hpp"
#include "gun.hpp"
//#include <iostream>

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
                BasicBullet* bullet = new BasicBullet(owner->getPosition(), targetPosition, owner, owner->getLevel());
                Animation basicBulletAnimation = Animation(Resources::get(Resources::ID::BULLET), 10, sf::Vector2u(12,16));
                bullet->setAnimation(basicBulletAnimation);
                owner->getLevel()->addEntity(bullet);
                break;
            }
        case BIG_GUN:
            {
                SpecialBullet* specialBullet = new SpecialBullet(owner->getPosition(), targetPosition, owner, owner->getLevel());
                Animation specialBulletAnimation = Animation(Resources::get(Resources::ID::SPECIALBULLET), 15, sf::Vector2u(32,32));
                specialBullet->setAnimation(specialBulletAnimation);
                owner->getLevel()->addEntity(specialBullet);
                break;
        }
    }
}

void Gun::setType(Gun::Type gunType){
    this->gunType = gunType;
}