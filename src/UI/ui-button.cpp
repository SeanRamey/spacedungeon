#include "ui-button.hpp"

UIButton::UIButton(sf::Vector2f position, sf::Texture* texture) :
UIElement(position){
    if(texture != nullptr){
        setTexture(texture);
    }
}

UIButton::~UIButton(){

}

void UIButton::setProperties(unsigned int fontSize, sf::Color color, sf::Font* font, sf::Vector2f position){
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(color);
    if(font != nullptr) {
        this->text.setFont(*font);
    } else {
        this->text.setFont(this->font);
    }
    this->text.setPosition(position);
}

void UIButton::update(){
    sprite.setPosition(position);
    sprite.setOrigin(sf::Vector2f(position.x + size.x, position.y + size.y));
    text.setPosition(sprite.getOrigin());
    text.setOrigin(sprite.getOrigin());
}

void UIButton::setSize(sf::Vector2u size){
    this->size = size;
}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
    target.draw(text);
}