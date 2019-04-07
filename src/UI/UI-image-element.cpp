#include "UI-image-element.hpp"
#include <iostream>

void UIImageElement::update(){
    sprite.setPosition(sf::Vector2f(position));
}

void UIImageElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}


void UIImageElement::setTexture(sf::Texture* texture){
    if(texture != nullptr){
        sprite.setTexture(*texture);
    }
}

void UIImageElement::updateScale(sf::Vector2f scale){
    sprite.setScale(scale);
}

UIImageElement::UIImageElement(sf::Vector2i position, sf::Texture* texture):
UIElement(position){
    if(texture != nullptr){
        sprite.setTexture(*texture);
    }
}

UIImageElement::~UIImageElement(){

}