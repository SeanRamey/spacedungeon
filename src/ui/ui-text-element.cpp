#include "sfmlpch.hpp"
#include "ui-text-element.hpp"
#include "log.hpp"

///////////////////////////
void UITextElement::setText(std::string text){
	this->text.setString(text);
	load();
}

///////////////////////////
void UITextElement::load(){
	this->text.setCharacterSize(fontSize);
	this->text.setFillColor(sf::Color::White);
	this->text.setFont(*font);
	this->text.setPosition(sf::Vector2f(position));
}

///////////////////////////
void UITextElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);
}

///////////////////////////
void UITextElement::update(){

}

///////////////////////////
void UITextElement::setPosition(sf::Vector2f position){
	this->position = position;
	text.setPosition(position);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
				   textRect.top + textRect.height / 2.0f);
	// centering text within point of given position
}

///////////////////////////
UITextElement::UITextElement(sf::Vector2f position, sf::Font* font, std::string text, unsigned int fontSize, sf::Color textColor):
UIElement(position){
	if(font == nullptr){
		Log::error("Given font is null for text: " + text);
	}
	this->font = font;
	this->text.setString(text);
	this->fontSize = fontSize;
	this->textColor = textColor;
	load();
}

///////////////////////////
UITextElement::~UITextElement(){

}
