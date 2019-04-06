#include "bullet.hpp"
#include "input.hpp"
#include "random-numbers.hpp"
#include "SFML/System.hpp"
#include "resources.hpp"
#include <iostream>
#include <cmath>
#include "othermath.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f targetPosition, Entity* owner, sf::Vector2u size, unsigned int initialSpeed, unsigned int damage, Level* level, sf::Time maxTimeAlive) :
Entity(position, size, nullptr, level){
    this->type = Entity::Type::BULLET;
    this->initialSpeed = initialSpeed;
    this->maxTimeAlive = maxTimeAlive;
    this->damage = damage;
    timeAlive = sf::Clock();
    face(targetPosition);
    unsigned int offset = Util::GetRandomNumber(0, 8) - 4;
    accelerate(sf::Vector2f(initialSpeed * cosf(degreesToRadians(getRotation() - 90)), initialSpeed * sinf(degreesToRadians(getRotation() - 90 ))));
}

Bullet::~Bullet(){
}

void Bullet::update(sf::Time frameTime){
    if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds()){
        destroy();
    }
    Entity::update(frameTime);
}

unsigned int Bullet::getDamage() {
    return damage;
}