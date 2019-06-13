#include <iostream>
#include <vector>
#include "tile.hpp"

Tile::Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h) :
position(x,y),
size(w,h),
sprite(),
index(0)
{
    sprite.setPosition(sf::Vector2f(position));
}

Tile::Tile(sf::Vector2u position, sf::Vector2u size) :
position(position),
size(size),
sprite(),
index(0)
{
    sprite.setPosition(sf::Vector2f(position));
}

Tile::Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h, sf::Texture* texture, unsigned int index) :
position(x,y),
size(w,h),
sprite(),
index(0)
{
    sprite.setPosition(sf::Vector2f(position));
    setTexture(texture, index);
}

Tile::Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture, unsigned int index) :
position(position),
size(size),
sprite(),
index(0)
{
    sprite.setPosition(sf::Vector2f(position));
    setTexture(texture, index);
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

void Tile::setTexture(sf::Texture *texture, unsigned int newIndex){
    sprite.setTexture(*texture);
    index = index;
}

sf::Sprite Tile::getSprite(){
    return sprite;
}