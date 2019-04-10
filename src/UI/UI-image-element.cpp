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
        this->size = texture->getSize();
    }
}

void UIImageElement::updateScale(sf::Vector2f scale){
    this->scale = scale;
    sprite.setScale(scale);
    sprite.setOrigin(size.x / 2, size.y / 2);
}

sf::Vector2u UIImageElement::getSize(){
    // std::cout << sf::Vector2u(size.x * sprite.getScale().x, size.y * sprite.getScale().y).x << std::endl;
    return sf::Vector2u(size.x * scale.x, size.y * scale.y);
}

UIImageElement::UIImageElement(sf::Vector2f position, sf::Texture* texture):
UIElement(position){
    if(texture != nullptr){
        setTexture(texture);
    }
}

UIImageElement::~UIImageElement(){

}