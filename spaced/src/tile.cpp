#include <iostream>
#include <vector>
#include "tile.hpp"

Tile::Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h) :
position(x,y),
size(w,h),
sprite()
{
    sprite.setPosition(sf::Vector2f(position));
}

Tile::Tile(sf::Vector2f position, sf::Vector2u size) :
position(position),
size(size),
sprite()
{
    sprite.setPosition(sf::Vector2f(position));
}

Tile::~Tile() {

}

void Tile::update(sf::Time frameTime) {

}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

const sf::Texture* Tile::getTexture() {
    return sprite.getTexture();
}

void Tile::setTexture(sf::Texture *texture){
    sprite.setTexture(*texture);
}

sf::Sprite Tile::getSprite(){
    return sprite;
}