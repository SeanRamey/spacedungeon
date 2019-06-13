#ifndef UI_TEXT_ELEMENT_HPP
#define UI_TEXT_ELEMENT_HPP

#include "ui-element.hpp"

class UITextElement : public UIElement {
    private:
        sf::Text text;
        sf::Font font;

    public:
        void load();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setText(std::string text);
        void setPosition(sf::Vector2f position);
        UITextElement(sf::Vector2f position, std::string fontPath, std::string text);
        ~UITextElement();
};
#endif