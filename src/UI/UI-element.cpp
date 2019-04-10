#include "UI-element.hpp"
#include <iostream>

void UIElement::setTexture(sf::Texture* texture){
    if(texture != nullptr) {
        this->size = texture->getSize();
        sprite.setTexture(*texture);
    }
}
void UIElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}

void UIElement::setPosition(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(sf::Vector2f(position));
}

UIElement::UIElement(sf::Vector2f position){
    this->position = position;
    sprite.setPosition(sf::Vector2f(position));
}

UIElement::~UIElement(){

}