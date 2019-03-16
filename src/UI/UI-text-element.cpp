#include "UI-text-element.hpp"
#include "log.hpp"

void UITextElement::setText(std::string text){
    this->text.setString(text);
    load();
}

void UITextElement::load(){
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::White);
    this->text.setFont(font);
    this->text.setPosition(sf::Vector2f(position));
}

void UITextElement::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(text);
}

void UITextElement::update(){

}


UITextElement::UITextElement(sf::Vector2i position, std::string fontPath, std::string text): 
UIElement(position){
    if(!font.loadFromFile(fontPath)){
        Log::error("Failed to load font for text element");
    }
    if(!text.empty()){
        this->text.setString(text); 
        load();
    }
}

UITextElement::~UITextElement(){

}