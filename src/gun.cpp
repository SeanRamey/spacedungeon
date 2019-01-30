#ifndef GUN_CPP
#define GUN_CPP
#include "gun.hpp"
#include <iostream>
#include "basic-bullet.hpp"
#include "resources.hpp"
#include "input.hpp"

using namespace Resources;
using namespace Input;

void Gun::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities){
    for(int i = 0; i < bullets.size(); i++){
        bullets[i]->update(frameTime, window, entities);
        if(bullets[i]->isDead()){
            bullets[i]->onDeath();
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Gun::shoot(){
    // std::cout << "bullet shot" << std::endl;
    switch(type){
        case 0:
            BasicBullet* bullet = new BasicBullet(parent->getPosition(), sf::Vector2u(8, 16), 1500, 1, sf::milliseconds(3000));
            bullet->setTexture(Resources::get(Resources::ID::Bullet));
            bullets.push_back(bullet);

    }
}

void Gun::draw(sf::RenderWindow* window){
    for(int i = 0; i < bullets.size(); i++){
        bullets[i]->draw(window);
    }
}

Gun::Gun(Entity* parent, unsigned int type){
    this->parent = parent;
    this->type = type;
}


Gun::~Gun(){
    for(int i = 0; i < bullets.size(); i++){
        delete bullets[i];
        bullets.resize(bullets.size() - 1);
    }
}
#endif