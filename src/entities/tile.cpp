#include <iostream>
#include <vector>
#include "tile.hpp"
void Tile::update(sf::Time frameTime, sf::RenderWindow* window){

}

void Tile::checkCollision(Entity* entity){

}

const sf::Texture* Tile::getTexture(){
    return this->sprite.getTexture();
}

Tile::Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Level* level):
Entity(x, y, w, h, level),
collisionBox(x, y, w, h){
    sprite.setPosition(x, y);
}

Tile::~Tile(){

}

void Tile::setImage(sf::Texture *image){
    sprite.setTexture(*image);
}
