#include "gun.hpp"
#include <iostream>
#include "basic-bullet.hpp"
#include "level.hpp"
#include "resources.hpp"
#include "input.hpp"

Gun::Gun(Entity* parent, unsigned int type) {
    this->parent = parent;
    this->type = type;
}

Gun::~Gun() {
    for(int i = 0; i < bullets.size(); i++) {
        delete bullets[i];
        bullets.resize(bullets.size() - 1);
    }
}

void Gun::update(sf::Time frameTime) {
    for(int i = 0; i < bullets.size(); i++) {
        if(bullets[i]->isDead()) {
            bullets[i]->onDeath();
            
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Gun::shoot() {
}

void Gun::setType(unsigned int type) {
    this->type = type;
}