#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class UIElement : public sf::Drawable {
    protected:
        sf::Vector2f position;
        sf::Sprite sprite;
        sf::Vector2u size;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        void setTexture(sf::Texture* texture);
        virtual void update() = 0;
        virtual void setPosition(sf::Vector2f position);
		sf::Vector2f  getPosition();
        sf::Vector2u getSize();
    
        UIElement(sf::Vector2f position);
        virtual ~UIElement();
    
};
#endif
