#ifndef TILE_HPP
#define TILE_HPP

//#include "sfmlpch.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Tile {
    public:
        void setTexture(sf::Texture* image);
        void update(sf::Time frameTime);
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
