#include "ui-element.hpp"
#include <iostream>

void UIElement::setTexture(sf::Texture* texture){
    if(texture != nullptr) {
        this->size = texture->getSize();
        sprite.setTexture(*texture);
    }
}
void UIElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void UIElement::setPosition(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2));
}

UIElement::UIElement(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(sf::Vector2f(position));
}

sf::Vector2f UIElement::getPosition(){
	return this->position;
}

sf::Vector2u UIElement::getSize(){
	return this->size;
}

UIElement::~UIElement(){

}
