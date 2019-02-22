#include "bullet.hpp"
#include "input.hpp"
#include "random-numbers.hpp"
#include "SFML/System.hpp"
#include "resources.hpp"
Bullet::Bullet(sf::Vector2f position, sf::Vector2u size, unsigned int MAX_SPEED, unsigned int DAMAGE, sf::Time maxTimeAlive, Level* level) : 
Entity(position.x, position.y, size.x, size.y, level){
    this->initialSpeed = MAX_SPEED;
    this->maxTimeAlive = maxTimeAlive;
    this->damage = DAMAGE;
    timeAlive = sf::Clock();
    dead = false;
    face(sf::Vector2f(Input::mousePosition.x + Resources::window->getView().getCenter().x - Resources::window->getSize().x / 2, Input::mousePosition.y + Resources::window->getView().getCenter().y - Resources::window->getSize().y / 2));
    this->MAX_SPEED = MAX_SPEED;
}

Bullet::~Bullet(){
}

void Bullet::update(sf::Time frameTime, sf::RenderWindow* window){
    
}

bool Bullet::isDead(){
    return dead;
}
