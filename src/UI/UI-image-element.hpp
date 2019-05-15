#ifndef UI_IMAGE_ELEMENT_HPP
#define UI_IMAGE_ELEMENT_HPP
#include "UI-element.hpp"

class UIImageElement : public UIElement {

    private:
        sf::Image image;
        sf::Texture* texture;
        sf::Sprite sprite;
        sf::Vector2f scale;

    public:
        UIImageElement(sf::Vector2f position, sf::Texture* texture);
        ~UIImageElement();
        sf::Vector2u getSize();
        sf::Vector2f getPosition();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void load();
        void update();
        void setTexture(sf::Texture* texture);
        void updateScale(sf::Vector2f scale);
        void updateSize(sf::Vector2f size);
        void setPosition(sf::Vector2f position);

}; 

#endif