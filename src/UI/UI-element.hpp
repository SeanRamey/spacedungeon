#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class UIElement : public sf::Drawable {
    protected:
        sf::Vector2i position;
        sf::Texture texture;
        sf::Sprite sprite;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        void setTexture(sf::Texture texture);
        virtual void update() = 0;
        void setPosition(sf::Vector2i position);
    
        UIElement(sf::Vector2i position);
        virtual ~UIElement();
    
};
#endif