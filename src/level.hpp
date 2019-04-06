#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include "entity.hpp"
#include "player-ship.hpp"
#include "tile.hpp"
#include "alien-ship.hpp"
#include "UI-text-element.hpp"

class Level{
    private:

        std::vector<Entity*> entities;
        std::vector<Tile*> tiles;
        
        PlayerShip* playerShip;
        std::vector<sf::Texture*> tileImages;

        sf::Vector2u mapSize;
        unsigned int tileSize;

        sf::View view;

        bool hasWon;
        bool playerIsDead;

        // healthbar
        UITextElement healthBar;

    public:
        //virtual void updateView() = 0;
        void handleCollisions();
        bool checkWon();
        void addEntity(Entity* entity);
        void removeEntity(Entity* entity);
        void loadEntites(std::string);
        PlayerShip* getPlayer();
        void loadMap(std::string map, std::string images);
        void update(sf::Time frameTime, sf::RenderWindow* window);
        void draw(sf::RenderWindow* window);
        
        Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize);
        ~Level();
};
#endif