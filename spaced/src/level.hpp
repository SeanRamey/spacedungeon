#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include "tile.hpp"
#include "input.hpp"
#include "SFML/Graphics.hpp"

struct tileLayers {
    // a temporary struct to store the data of the layers of a tile map
    // used in file parsing
    unsigned char backGround, middleGround, foreGround;
    tileLayers(unsigned char bg, unsigned char mg, unsigned char fg){
        this->backGround = bg;
        this->middleGround = mg;
        this->foreGround = fg;
    }
};



class Level {
    private:
    
        std::vector<Tile*> backGroundTiles;
        std::vector<Tile*> middleTiles;
        std::vector<Tile*> foreGroundTiles;
        
        std::vector<sf::Texture*> tileImages;

        sf::Sprite backGroundSprite;
        sf::Texture backGroundTexture;

        sf::Vector2u mapSize;
        unsigned int tileSize;
        unsigned int brushSize;

        sf::View view;
        float zoomLevel;
        float prevZoomLevel;
        sf::Vector2i lastMousePosition;

        unsigned int selectedTileType;

        sf::Clock keyTimer;
        const unsigned int keyDelay = 50;
        sf::Sprite currentTileVisual;
        bool saving;

    public:
        void loadMap(std::string map, std::string images);
        void saveMap(std::string map);
        void update(sf::Time frameTime, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        void changeTile(sf::Vector2i pos,  unsigned int tileTypeIndex);
        sf::View getView() {return view;};
        void setView(sf::View view) {this->view = view;};
        Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize = 32);
        ~Level();
};
#endif