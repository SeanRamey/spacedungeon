#ifndef UI_TEXT_ELEMENT_HPP
#define UI_TEXT_ELEMENT_HPP

#include "sfmlpch.hpp"
#include "ui-element.hpp"


class UITextElement : public UIElement {
	private:
		sf::Text text;
		sf::Font* font;
		unsigned int fontSize = 35;
		sf::Color textColor = sf::Color::White;

	public:
		void load();
		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void setText(std::string text);
		void setPosition(sf::Vector2f position);
		UITextElement(sf::Vector2f position, sf::Font* font, std::string text, unsigned int fontSize = 32, sf::Color textColor = sf::Color::White);
		~UITextElement();
};
#endif
