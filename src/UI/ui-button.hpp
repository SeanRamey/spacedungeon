#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP
#include "ui-element.hpp"

class UIButton : public UIElement {
    private:
        sf::Text text;
        sf::Font font;

    public:
        UIButton(sf::Vector2f position, sf::Texture* texture);
        ~UIButton();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void update(); // setting text to center of sprite
        void setSize(sf::Vector2u size);
        void setProperties(unsigned int fontSize = 35, sf::Color color = sf::Color::White, sf::Font* font = nullptr, sf::Vector2f position = sf::Vector2f(0, 0));

};
#endif
