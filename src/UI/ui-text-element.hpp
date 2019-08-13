#ifndef UI_TEXT_ELEMENT_HPP
#define UI_TEXT_ELEMENT_HPP

#include "ui-element.hpp"

class UITextElement : public UIElement {
    private:
        sf::Text text;
        sf::Font font;

    public:
        void setProperties(std::string fontPath, unsigned int fontSize = 35, sf::Color color = sf::Color::Black);
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setPosition(sf::Vector2f position);
		sf::Text& getText();
        UITextElement(sf::Vector2f position, std::string fontPath, std::string text, unsigned int fontSize = 35, sf::Color color = sf::Color::Black);
		UITextElement(sf::Vector2f position);
        ~UITextElement();
};
#endif
