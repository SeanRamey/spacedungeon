#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include "entity.hpp"
#include "player-ship.hpp"
#include "tile.hpp"
#include "alien-ship.hpp"

<<<<<<< HEAD
struct CollisionPair {
    Entity *entity1;
    Entity *entity2;
};


class Level {
=======
class Level{
>>>>>>> master
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

    public:
        void processCollisions();
        bool checkWon();
        void addEntity(Entity* entity);
        void removeEntity(Entity* entity);
        void loadEntites(std::string);
        PlayerShip* getPlayer();
        void loadMap(std::string map, std::string images);
<<<<<<< HEAD
        void addEntity(Entity* entity);
        void deleteEntity(Entity* entity);
        void update(sf::Time frameTime, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        sf::View getView() {return view;};
        Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize = 32);
=======
        void update(sf::Time frameTime, sf::RenderWindow* window);
        void draw(sf::RenderWindow* window);
        
        Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize);
>>>>>>> master
        ~Level();
};
#endif