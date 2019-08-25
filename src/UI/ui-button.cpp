#include "ui-button.hpp"
#include "resources.hpp"
#include "input.hpp"
#include "main-menu.hpp"
#include <iostream>
#include "log.hpp"

UIButton::UIButton(sf::Vector2f position, sf::Texture* texture, GameState* parent, void (*callback)(MainMenu*)) :
UIElement(position),
text(position),
parent(parent),
callback(callback){
	if(texture != nullptr){
		setTexture(texture);
	}
}

UIButton::~UIButton(){

}

void UIButton::update(){
	sprite.setPosition(position);
	sprite.setOrigin(sf::Vector2f(size.x/2, size.y/2));
	sf::FloatRect rect(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y);
	sf::Vector2f mousePosition = Resources::window->mapPixelToCoords(Input::mousePosition);

	text.setPosition(position);

	if(rect.contains(mousePosition) && Input::checkMouse(sf::Mouse::Left)){
		callback((MainMenu*)parent);
		return;
	}
}

void UIButton::setSize(sf::Vector2u size){
	this->size = size;
}

UITextElement& UIButton::getText(){
	return this->text;
}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
	target.draw(text, states);
}
