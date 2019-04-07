#ifndef UI_TEXT_ELEMENT_HPP
#define UI_TEXT_ELEMENT_HPP

#include "UI-element.hpp"

class UITextElement : public UIElement {
    private:
        sf::Text text;
        sf::Font font;

    public:
        void load();
        void update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setText(std::string text);
        UITextElement(sf::Vector2i position, std::string fontPath, std::string text);
        ~UITextElement();
};
#endif