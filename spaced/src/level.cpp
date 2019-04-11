#include "level.hpp"
//#include "resources.hpp"
//#include "log.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

Level::Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize) :
view(),
tileSize(tileSize) {
    loadMap(levelMapFilename, tileImagesFilename);
}

Level::~Level(){
    for(Tile* tile : tiles) {
        delete tile;
    }
}


void Level::draw(sf::RenderWindow& window){
    for(Tile* tile : tiles) {
        window.draw(tile->getSprite());
        tile->draw(window);
    }
}

void Level::update(sf::Time frameTime, sf::RenderWindow& window){

    std::vector<sf::Event> events = Input::getEventList();
    for(sf::Event event : events) {
        if(event.type == sf::Event::Resized) {
            view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
        }
    }
    
    if(Input::checkKey(sf::Keyboard::Up)) {
        view.move(0,-16);
    }
    if(Input::checkKey(sf::Keyboard::Down)) {
        view.move(0,16);
    }
    if(Input::checkKey(sf::Keyboard::Left)) {
        view.move(-16,0);
    }
    if(Input::checkKey(sf::Keyboard::Right)) {
        view.move(16,0);
    }
    if(Input::checkKey(sf::Keyboard::PageUp)) {
        view.zoom(1.05);
    }
    if(Input::checkKey(sf::Keyboard::PageDown)) {
        view.zoom(0.95);
    }

    window.setView(view);



}

void Level::loadMap(std::string map, std::string images) {

    // Open the tile map data file for the level
    std::ifstream file(map); 

    if(!file.is_open()) {
        //Log::error("Failed to open file: " + map);
        exit(-1);
    }

    // Get the first two numbers from the file
    // (seperated by whitespace) and use them
    // for the dimensions of the map
    file >> mapSize.x >> mapSize.y;

    // Load the rest of the file, and store each byte in fileData
    std::vector<char> fileData;
    fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();

    // Parse the fileData into an array of bytes, seperated by spaces and newlines
    // for loop starts at 1 to skip the first newline character in the fileData
    std::string buffer;
    std::vector<unsigned char> mapData;
    for(int i = 1; i < fileData.size(); i++) {
        switch(fileData[i]) {
            case ' ':
                mapData.push_back((unsigned char)std::stoul(buffer)); // add the current buffer to mapData as an unsigned char
                buffer.clear();
                break;
            case '\n':
                mapData.push_back((unsigned char)std::stoul(buffer));
                buffer.clear();
                break;
            default:
                buffer += fileData[i];
        }
    }

    // Load the tileset source image
    sf::Image tilesetImage;
    if(!tilesetImage.loadFromFile(images)){
       //Log::error("big boy error, couldn't load tile map");
    }

    // Store how many tiles are in the tileset
    sf::Vector2u tileCount;
    tileCount.x = tilesetImage.getSize().x / tileSize; 
    tileCount.y = tilesetImage.getSize().y / tileSize; 

    // Store each tile graphic as a sf::Texture in an array
    for(unsigned int y = 0; y < tileCount.y; y++) {
        for(unsigned int x = 0; x < tileCount.x; x++) {
            tileImages.push_back(new sf::Texture());
            tileImages.at(y * tileCount.x + x)->loadFromImage(tilesetImage, sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
        }
    }

    // Create Tiles in the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(mapData.at(x + y * mapSize.x) != 0) {
                Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
                tiles.push_back(tile);
                tiles[tiles.size() - 1]->setTexture(tileImages[mapData[x + y * mapSize.x] - 1]);
            }
        }
    }
}