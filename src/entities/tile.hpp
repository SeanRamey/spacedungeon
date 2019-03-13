#ifndef TILE_HPP
#define TILE_HPP

//#include "sfmlpch.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.hpp"

class Tile {
    public:
<<<<<<< HEAD
        void setTexture(sf::Texture* image);
        void update(sf::Time frameTime);
        const sf::Texture* getTexture();

        Tile(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
        Tile(sf::Vector2f position, sf::Vector2u size);
=======
        CollisionBox collisionBox;
        void setImage(sf::Texture* image);
        void checkCollision(Entity* entity);
        void update(sf::Time frameTime, sf::RenderWindow* window);
        const sf::Texture* getTexture();    

        Tile(unsigned int, unsigned int, unsigned int, unsigned int, Level* level);
>>>>>>> master
        ~Tile();

        sf::Vector2u position;
        sf::Vector2u size;

    private:
        sf::Sprite sprite;
};
#endif
