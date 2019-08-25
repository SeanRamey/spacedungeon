#ifndef MENU_HPP
#define MENU_HPP
#include "stdpch.hpp"
#include "ui-element.hpp"
#include "ui-button.hpp"
#include "ui-text-element.hpp"
#include "ui-image-element.hpp"
#include "game-state.hpp"
#include "game.hpp"
class Menu {
	public:
		void update(sf::Time frameTime);
		void draw(sf::RenderWindow& window);
		void addButton(UIButton* button);
		void addImage(UIImageElement* images);
		void addText(UITextElement* text);
		UIButton* getButton(int index);
		UIImageElement* getImage(int index);
		UITextElement* getText(int index);
		void clear();

		Menu();
		~Menu();

	protected:
		std::vector<UIButton*> buttons;
		std::vector<UIImageElement*> images;
		std::vector<UITextElement*> texts;
};

#endif
