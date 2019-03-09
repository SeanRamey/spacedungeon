#include "level.hpp"
#include "gun.hpp"
#include <iostream>

#include "resources.hpp"
#include <future>
#include "log.hpp"

using namespace Resources;
using namespace Input;

void Gun::update(sf::Time frameTime, sf::RenderWindow* window){
    for(int i = 0; i < bullets.size(); i++){
        if(bullets[i]->isDead()){
            bullets[i]->onDeath();
            parent->getLevel()->removeEntity(bullets[i]);
            bullets.erase(std::find(bullets.begin(), bullets.end(), bullets[i])); 
            bullets.shrink_to_fit();
        }
    }
}

void Gun::shoot(){
    switch(type){
        case 0:
            {
                BasicBullet* bullet = new BasicBullet(parent->getPosition(), basicBulletSize, basicBulletSpeed, basicBulletDamage, parent->getLevel());
                bullet->setTexture(Resources::get(Resources::ID::BULLET));
                parent->getLevel()->addEntity(bullet);
                bullets.push_back(bullet);
                break;
            }
        case 1:
            {
                SpecialBullet* specialBullet = new SpecialBullet(parent->getPosition(), specialBulletSize, specialBulletSpeed, specialBulletDamage, parent->getLevel());
                sf::Image image;
                if(!image.loadFromFile("data/graphics/big-bullet_test.png")){
                    Log::error("failed to load special bullet texture");     
                }
                specialBullet->setAnimation(image, specialBulletSize, specialBulletStateLengths);
                specialBullet->setDelay(sf::milliseconds(100));
                specialBullet->setState(0);
                parent->getLevel()->addEntity(specialBullet);
                bullets.push_back(specialBullet);
                break;
        }
    }
}

void Gun::draw(sf::RenderWindow* window){

}

void Gun::setType(unsigned int type){
    this->type = type;
}

Gun::Gun(Entity* parent, unsigned int type){
    this->parent = parent;
    this->type = type;
    this->basicBulletSpeed = 1000;
    this->basicBulletSize = sf::Vector2u(16, 8);
    this->basicBulletDamage = 1;

    this->specialBulletSpeed = 500;
    this->specialBulletSize = sf::Vector2u(32, 32);
    this->specialBulletDamage = 2;
}

std::vector<Bullet*>* Gun::getBullets(){
    return &this->bullets;
}

Gun::~Gun(){

}