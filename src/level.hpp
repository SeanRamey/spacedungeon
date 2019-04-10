#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include "entity.hpp"
#include "player-ship.hpp"
#include "tile.hpp"
#include "UI-text-element.hpp"
#include "UI-image-element.hpp"
#include "alien-ship.hpp"

struct CollisionPair {
    Entity *entity1;
    Entity *entity2;
};


class Level {
    private:

        std::vector<Entity*> entities;
        std::vector<Tile*> tiles;
        
        PlayerShip* playerShip;
        std::vector<sf::Texture*> tileImages;

        sf::Sprite backGroundSprite;
        sf::Texture backGroundTexture;

        sf::Vector2u mapSize;
        unsigned int tileSize;

        sf::View view;

        bool hasWon;
        bool playerIsDead;
        
        UITextElement healthText;
        UIImageElement healthBar;

        UITextElement gameOver;

    public:
        void processCollisions();
        bool checkWon();
        void loadEntites(std::string);
        void removeDestroyedEntities();
        PlayerShip* getPlayer();
        void loadMap(std::string map, std::string images);
        void addEntity(Entity* entity);
        void deleteEntity(Entity* entity);
        void update(sf::Time frameTime, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        sf::View getView() {return view;};
        Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize = 32);
        ~Level();
};
#endif