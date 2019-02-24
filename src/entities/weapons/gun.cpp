#ifndef GUN_CPP
#define GUN_CPP
#include "gun.hpp"
#include <iostream>
#include "basic-bullet.hpp"
#include "special-bullet.hpp"
#include "resources.hpp"
#include "input.hpp"
#include <future>

using namespace Resources;
using namespace Input;

void Gun::update(sf::Time frameTime, sf::RenderWindow* window){
    for(int i = 0; i < bullets.size(); i++){
        bullets[i]->update(frameTime, window);
        if(bullets[i]->isDead()){
            auto r = std::async(std::launch::async, bullets[i]->onDeath());
            r.get();
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Gun::shoot(){
    switch(type){
        case 0:
            {
                BasicBullet* bullet = new BasicBullet(parent->getPosition(), basicBulletSize, basicBulletSpeed, basicBulletDamage, parent->getLevel());
                bullet->setTexture(Resources::get(Resources::ID::BULLET));
                bullets.push_back(bullet);
                break;
            }
        case 1:
            {
                SpecialBullet* specialBullet = new SpecialBullet(parent->getPosition(), specialBulletSize, specialBulletSpeed, specialBulletDamage, parent->getLevel());
                specialBullet->setTexture(Resources::get(Resources::ID::SPECIALBULLET));
                bullets.push_back(specialBullet);
                std::cout << "special bullet shot" << std::endl;
                break;
        }
    }
}

void Gun::draw(sf::RenderWindow* window){
    for(int i = 0; i < bullets.size(); i++){
        bullets[i]->draw(window);
    }
}

void Gun::setType(unsigned int type){
    this->type = type;
}

Gun::Gun(Entity* parent, unsigned int type){
    this->parent = parent;
    this->type = type;
    this->basicBulletSpeed = 1500;
    this->basicBulletSize = sf::Vector2u(16, 8);
    this->basicBulletDamage = 1;

    this->specialBulletSpeed = 500;
    this->specialBulletSize = sf::Vector2u(32, 32);
    this->specialBulletDamage = 2;
}


Gun::~Gun(){
    for(int i = 0; i < bullets.size(); i++){
        delete bullets[i];
        bullets.resize(bullets.size() - 1);
    }
}
#endif
