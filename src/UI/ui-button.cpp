#include "ui-button.hpp"
#include "resources.hpp"
#include "input.hpp"
#include "main-menu.hpp"
#include <iostream>

UIButton::UIButton(sf::Vector2f position, sf::Texture* texture, void* parent, void (*callback)(MainMenu*)) :
UIElement(position){
	this->parent = parent;	
	this->callback = callback;
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
    sprite.setOrigin(sf::Vector2f(position.x + size.x / 2, position.y + size.y / 2));
	sf::FloatRect rect = sf::FloatRect(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y);
	sf::Vector2f mousePosition = Resources::window->mapPixelToCoords(Input::mousePosition);

	if(rect.contains(mousePosition) && Input::checkMouse(sf::Mouse::Left)){
		callback((MainMenu*)parent);
	}
    //text.setPosition(sprite.getOrigin());
    //text.setOrigin(sprite.getOrigin());
}

void UIButton::setSize(sf::Vector2u size){
    this->size = size;
}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
    target.draw(text);
}
