#include "special-bullet.hpp"


SpecialBullet::SpecialBullet(sf::Vector2f position, sf::Vector2u size, unsigned int speed, unsigned int damage) :
Bullet(position, size, speed, damage, sf::milliseconds(3000)){
    
}

SpecialBullet::~SpecialBullet(){

}

void SpecialBullet::onDeath(){

}

void SpecialBullet::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities){

}

void SpecialBullet::checkCollision(Entity* entity){
    
}