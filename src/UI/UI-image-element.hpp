#ifndef UI_IMAGE_ELEMENT_HPP
#define UI_IMAGE_ELEMENT_HPP
#include "UI-element.hpp"

class UIImageElement : public UIElement {

    private:
        sf::Image image;
        sf::Texture* texture;
        sf::Sprite sprite;

    public:
        UIImageElement(sf::Vector2i position, sf::Texture* texture);
        ~UIImageElement();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void load();
        void update();
        void setTexture(sf::Texture* texture);
        void updateScale(sf::Vector2f scale);

}; 

#endif