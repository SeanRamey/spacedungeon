#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "collision-box.hpp"
#include <vector>
#include "entity.hpp"

class Tile : public Entity {
    public:
        CollisionBox collisionBox;
        void setImage(sf::Texture* image);
        void checkCollision(Entity* entity);
        void update(sf::Time frameTime, sf::RenderWindow* window);
        const sf::Texture* getTexture();    

        Tile(unsigned int, unsigned int, unsigned int, unsigned int, Level* level);
        ~Tile();
};
#endif