#include <iostream>
#include <vector>
#include "tile.hpp"
<<<<<<< HEAD
=======
void Tile::update(sf::Time frameTime, sf::RenderWindow* window){
>>>>>>> master

Tile::Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h) :
position(x,y),
size(w,h)
{
}

Tile::Tile(sf::Vector2f position, sf::Vector2u size) :
position(position),
size(size)
{
}

Tile::~Tile() {

<<<<<<< HEAD
=======
Tile::Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h, Level* level):
Entity(x, y, w, h, level),
collisionBox(x, y, w, h){
    sprite.setPosition(x, y);
>>>>>>> master
}

void Tile::update(sf::Time frameTime) {

}

const sf::Texture* Tile::getTexture() {
    return sprite.getTexture();
}

<<<<<<< HEAD
void Tile::setTexture(sf::Texture *texture){
    sprite.setTexture(*texture);
}
=======
void Tile::setImage(sf::Texture *image){
    sprite.setTexture(*image);
}
>>>>>>> master
