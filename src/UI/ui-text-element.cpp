#include "ui-text-element.hpp"
#include "log.hpp"

sf::Text& UITextElement::getText(){
	return this->text;
}

void UITextElement::setProperties(std::string fontPath, unsigned int fontSize, sf::Color color){
	if(!font.loadFromFile(fontPath)){
        Log::error("Failed to load font for text element");
		std::cout << "failed " << std::endl;
    }
    this->text.setFont(font);
    this->text.setCharacterSize(fontSize);
    this->text.setFillColor(sf::Color::Green);
}

void UITextElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->text);
}

void UITextElement::update(){
	setPosition(position);
}

void UITextElement::setPosition(sf::Vector2f position){
	this->position = position;
    text.setPosition(position);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
}


UITextElement::UITextElement(sf::Vector2f position, std::string fontPath, std::string text, unsigned int fontSize, sf::Color textColor): 
UIElement(position)
{
    if(!font.loadFromFile(fontPath)){
        Log::error("Failed to load font for text element");
		std::cout << "failed " << std::endl;
    }
    this->text.setString(text); 
	this->text.setFont(font);
	this->text.setCharacterSize(fontSize);
	this->text.setFillColor(textColor);
	setPosition(position);
}
UITextElement::UITextElement(sf::Vector2f position) :
UIElement(position){

}

UITextElement::~UITextElement(){

}
