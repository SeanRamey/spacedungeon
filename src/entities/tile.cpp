#include "stdpch.hpp"
//#include <iostream>
//#include <vector>
#include "tile.hpp"
#include "entity.hpp"


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

}

void Tile::update(sf::Time frameTime) {

}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}

const sf::Texture* Tile::getTexture() {
    return sprite.getTexture();
}

void Tile::setTexture(sf::Texture *texture){
    sprite.setTexture(*texture);
}

sf::Vector2f Tile::getPosition(){
	return this->position;
}

sf::FloatRect Tile::getCollisionRect(){
	//std::cout << position.x << "  " <<  position.y << "   " << size.x << "   " << size.y << std::endl;
    return sf::FloatRect(position.x, position.y, size.x, size.y);
}
