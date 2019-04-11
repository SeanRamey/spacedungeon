#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include "tile.hpp"
#include "input.hpp"
#include "SFML/Graphics.hpp"



class Level {
    private:

        std::vector<Tile*> tiles;
        
        std::vector<sf::Texture*> tileImages;

        sf::Sprite backGroundSprite;
        sf::Texture backGroundTexture;

        sf::Vector2u mapSize;
        unsigned int tileSize;

        sf::View view;
        float zoomLevel;
        float prevZoomLevel;
        sf::Vector2i lastMousePosition;

    public:
        void loadMap(std::string map, std::string images);
        void update(sf::Time frameTime, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        void changeTile(Tile& oldTile, Tile& newTile);
        sf::View getView() {return view;};
        void setView(sf::View view) {this->view = view;};
        Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize = 32);
        ~Level();
};
#endif