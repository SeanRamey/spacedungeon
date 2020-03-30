#include "menu.hpp"

///////////////////////////
void Menu::addButton(UIButton* button){
	buttons.push_back(button);
}

///////////////////////////
void Menu::addImage(UIImageElement* image){
	images.push_back(image);
}

///////////////////////////
void Menu::addText(UITextElement* text){
	texts.push_back(text);
}

///////////////////////////
UIButton* Menu::getButton(int index){
	return buttons.at(index);
}

///////////////////////////
UIImageElement* Menu::getImage(int index){
	return images.at(index);
}

///////////////////////////
UITextElement* Menu::getText(int index){
	return texts.at(index);
}

///////////////////////////
void Menu::clear(){
	buttons.clear();
	images.clear();
	texts.clear();
}

///////////////////////////
void Menu::update(sf::Time frameTime){
	for(UIButton* button : buttons){
		button->update();
	}
	for(UIImageElement* image : images){
		image->update();
	}
	for(UITextElement* text : texts){
		text->update();
	}
}

///////////////////////////
void Menu::draw(sf::RenderWindow& window){
	for(UIButton* button : buttons){
		window.draw(*button);
	}
	for(UIImageElement* image : images){
		window.draw(*image);
	}
	for(UITextElement* text : texts){
		window.draw(*text);
	}
}

///////////////////////////
Menu::Menu(){
	clear();
}

///////////////////////////
Menu::~Menu(){
	clear();
}
