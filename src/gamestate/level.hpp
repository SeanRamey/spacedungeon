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
#include "game-state.hpp"

struct CollisionPair {
    Entity *entity1;
    Entity *entity2;
};


class Level : public GameState {
    private:

        std::vector<Entity*> entities;

        std::vector<Tile*> middleTiles;
        std::vector<Tile*> foreGroundTiles;
        
        PlayerShip* playerShip;
        std::vector<sf::Texture*> tileImages;

        sf::Sprite backGroundSprite;
        sf::Texture backGroundTexture;

        sf::Sprite middleGroundSprite;
        sf::Texture middleGroundTexture;

        sf::Sprite foreGroundSprite;
        sf::Texture foreGroundTexture;

        sf::Vector2u mapSize;
        unsigned int tileSize;

        bool hasWon;
        bool playerIsDead;
        
        UITextElement healthText;
        UIImageElement healthBar;

        UITextElement gameOver;

        std::string levelMapFileName;
        std::string tileImagesFileName;
        std::string levelDataFileName;

    public:
        void processCollisions();
        bool checkWon();
        bool checkLose();
        void loadEntites(std::string);
        void removeDestroyedEntities();
        PlayerShip* getPlayer();
        void setPlayer(PlayerShip* playerShip);
        void loadMap(std::string map, std::string images);
        void addEntity(Entity* entity);
        void deleteEntity(Entity* entity);

        void init();
        void clear();
        void update(sf::Time frameTime, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);

        Level(Game* game, std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize = 32);
        ~Level();
};
#endif