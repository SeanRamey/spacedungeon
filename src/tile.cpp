#include <iostream>
#include <vector>
#include "tile.hpp"
void Tile::update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities){

}

void Tile::checkCollision(Entity* entity){

}

void Tile::draw(sf::RenderWindow* window){  
    // std::cout << position.x << "  " << position.y << std::endl;
    sprite.setPosition(position.x, position.y);
    window->draw(sprite);
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