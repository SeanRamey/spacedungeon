#include "ui-image-element.hpp"
#include <iostream>
#include <cmath>

void UIImageElement::update(){
	sprite.setPosition(sf::Vector2f(position));
}

void UIImageElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
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

void UIImageElement::updateSize(sf::Vector2f size){
	sprite.setTextureRect(sf::IntRect((sprite.getTexture()->getSize().x - (sprite.getTexture()->getSize().x * size.x)) / 2,
	(sprite.getTexture()->getSize().y - (sprite.getTexture()->getSize().y * size.y)) / 2,
	floor(sprite.getTexture()->getSize().x * size.x),
	floor(sprite.getTexture()->getSize().y * size.y)));
}

sf::Vector2u UIImageElement::getSize(){
	return sf::Vector2u(size.x * scale.x, size.y * scale.y);
}

sf::Vector2f UIImageElement::getPosition(){
	return this->sprite.getPosition();
}

void UIImageElement::setPosition(sf::Vector2f position){
	this->position = position;
	sprite.setPosition(position);
	sf::FloatRect textRect = sprite.getLocalBounds();
	sprite.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
	// centering text within point of given position
}

UIImageElement::UIImageElement(sf::Vector2f position, sf::Texture* texture):
UIElement(position){
	if(texture != nullptr){
		setTexture(texture);
	}
}

UIImageElement::~UIImageElement(){

}
