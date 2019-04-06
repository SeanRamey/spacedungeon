#include "UI-element.hpp"

void UIElement::setTexture(sf::Texture texture){
    sprite.setTexture(texture);
}
void UIElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}

void UIElement::setPosition(sf::Vector2i position){
    this->position = position;
}

UIElement::UIElement(sf::Vector2i position){
    this->position = position;
}

UIElement::~UIElement(){

}