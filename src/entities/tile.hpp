#ifndef TILE_HPP
#define TILE_HPP

#include "allpch.hpp"
//#include <SFML/Graphics.hpp>
//#include <vector>

class Tile : public sf::Drawable{
    public:
        void setTexture(sf::Texture* image);
        void update(sf::Time frameTime);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        const sf::Texture* getTexture();

        Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
        Tile(sf::Vector2f position, sf::Vector2u size);
        ~Tile();

        sf::Vector2u position;
        sf::Vector2u size;

    private:
        sf::Sprite sprite;
};
#endif
