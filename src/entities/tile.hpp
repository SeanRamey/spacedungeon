#ifndef TILE_HPP
#define TILE_HPP

//#include "sfmlpch.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.hpp"

class Tile : public Entity {
    public:
        void setImage(sf::Texture* image);
        void checkCollision(Entity* entity);
        void update(sf::Time frameTime, sf::RenderWindow* window, std::vector<Entity*> entities);
        const sf::Texture* getTexture();    

        Tile(unsigned int, unsigned int, unsigned int, unsigned int);
        ~Tile();
};
#endif