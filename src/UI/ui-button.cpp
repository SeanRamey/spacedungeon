#include "ui-button.hpp"
#include "resources.hpp"
#include "input.hpp"
#include "main-menu.hpp"
#include <iostream>
#include "log.hpp"

UIButton::UIButton(sf::Vector2f position, sf::Texture* texture, GameState* parent, void (*callback)(MainMenu*)) :
UIElement(position){
	this->parent = parent;	
	this->callback = callback;
    if(texture != nullptr){
        setTexture(texture);
    }
}

UIButton::~UIButton(){

}

void UIButton::setProperties(unsigned int fontSize, sf::Color color, std::string fontPath, sf::Vector2f position){
	if(!font.loadFromFile(fontPath)){
		Log::error("failed to load font in button");
	} else {
    	this->text.setFont(this->font);
	}
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(color);
    this->text.setPosition(position);
}

void UIButton::update(){
    sprite.setPosition(position);
    sprite.setOrigin(sf::Vector2f(size.x/2, size.y/2));
	sf::FloatRect rect(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y);
	sf::Vector2f mousePosition = Resources::window->mapPixelToCoords(Input::mousePosition);

	if(rect.contains(mousePosition) && Input::checkMouse(sf::Mouse::Left)){
		callback((MainMenu*)parent);
		return;
	}
    text.setPosition(position);
	sf::FloatRect textrect = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(textrect.left + textrect.width/2,textrect.top + textrect.height/2));
	text.setOutlineColor(sf::Color::Black);
}

void UIButton::setSize(sf::Vector2u size){
    this->size = size;
}
void UIButton::setText(std::string text){
	this->text.setString(text);
}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
    target.draw(text, states);
}
