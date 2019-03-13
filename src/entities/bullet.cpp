#include "bullet.hpp"
#include "input.hpp"
#include "random-numbers.hpp"
#include "SFML/System.hpp"
#include "resources.hpp"
Bullet::Bullet(sf::Vector2f position, sf::Vector2u size, unsigned int MAX_SPEED, unsigned int DAMAGE, sf::Time maxTimeAlive) : 
Entity(position.x, position.y, size.x, size.y, nullptr, nullptr){
    this->initialSpeed = MAX_SPEED;
    this->maxTimeAlive = maxTimeAlive;
    this->damage = DAMAGE;
    timeAlive = sf::Clock();
    dead = false;
    // finalPosition = sf::Vector2f(Input::mousePosition.x + window->getView().getCenter().x - window->getSize().x / 2, Input::mousePosition.y + window->getView().getCenter().y - window->getSize().y / 2);
    //(Resources::window->getView().getCenter().x); // - Resources::window->getSize().x / 2, Input::mousePosition.y + Resources::window->getView().getCenter().y - Resources::window->getSize().y / 2);
    face(sf::Vector2f(Input::mousePosition.x + Resources::window->getView().getCenter().x - Resources::window->getSize().x / 2, Input::mousePosition.y + Resources::window->getView().getCenter().y - Resources::window->getSize().y / 2));
}

Bullet::~Bullet(){
}

void Bullet::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities){
    
}

bool Bullet::isDead(){
    return dead;
}
