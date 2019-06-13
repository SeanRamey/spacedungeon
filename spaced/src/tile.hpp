#ifndef TILE_HPP
#define TILE_HPP

//#include "sfmlpch.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Tile{
    public:
        void setTexture(sf::Texture* image, unsigned int newIndex);
        void update(sf::Time frameTime);
        void draw(sf::RenderWindow& window);
        const sf::Texture* getTexture();
        sf::Sprite getSprite();

        Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
        Tile(sf::Vector2u position, sf::Vector2u size);
        Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h, sf::Texture* texture, unsigned int index);
        Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture, unsigned int index);
        ~Tile();

        sf::Vector2u position;
        sf::Vector2u size;
        unsigned int index;

    private:
        sf::Sprite sprite;
};
#endif
