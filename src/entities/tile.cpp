#include <iostream>
#include <vector>
#include "tile.hpp"
void Tile::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities){

}

void Tile::checkCollision(Entity* entity){

}

const sf::Texture* Tile::getTexture(){
    return this->sprite.getTexture();
}

Tile::Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h) :
Entity(x, y, w, h),
collisionBox(x, y, w, h){
    sprite.setPosition(x, y);
}

Tile::~Tile(){

}

void Tile::setImage(sf::Texture *image){
    sprite.setTexture(*image);
}