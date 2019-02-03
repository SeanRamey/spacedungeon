#include "level.hpp"
#include "resources.hpp"
#include "log.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h>

Level::Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize) :
playerShip(nullptr),
tileSize(tileSize) {
    loadMap(levelMapFilename, tileImagesFilename);
    Resources::load();
    loadEntites(levelDataFilename);
    playerShip = new PlayerShip(50, 50, 32, 32);
    entities.push_back(playerShip);
}

Level::~Level(){
    for(Entity* entity : entities) {
        delete entity;
    }
    for(Tile* tile : tiles) {
        delete tile;
    }
    for(sf::Texture* texture : tileImages) {
        delete texture;
    }
}

bool Level::checkWon(){
    return false;
}


void Level::draw(sf::RenderWindow* window){
    for(Tile* tile : tiles){
        tile->draw(window);
    }
    playerShip->draw(window);
    for(Entity* entity : entities){
        entity->draw(window);
    }
}

void Level::update(sf::Time frameTime, sf::RenderWindow* window){
    view.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    view.setCenter(playerShip->getPosition().x, playerShip->getPosition().y);
    window->setView(view);
    playerShip->update(frameTime, window, entities);
    for(Tile* tile : tiles){
        tile->update(frameTime, window, entities);
    }
    for(Entity* entity : entities){
        if(entity != playerShip){
            entity->update(frameTime, window, entities);
        }
    }
}

void handleCollisions() {
    
}

void Level::loadMap(std::string map, std::string images) {

    // Open the tile map data file for the level
    std::ifstream file(map); 

    if(!file.is_open()) {
        Log::error("Failed to open file: " + map);
        exit(-1);
    }

    // Get the first two numbers from the file
    // (seperated by whitespace) and use them
    // for the dimensions of the map
    file >> mapSize.x >> mapSize.y;


    // Load the rest of the file, and store each byte in data
    std::vector<char> data;
    data.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    file.close();

    // Format the file data by removing unwanted data (spaces and newlines)
    for(unsigned int i = 0; i < data.size(); i++){
        char ch = data[i];
        if(ch == ' ' || ch == '\n') {
            data.erase(data.begin() + i);
        }
    }

    data.shrink_to_fit();

    // Load the graphic data for the tiles
    sf::Image tilesImage;
    if(!tilesImage.loadFromFile(images)){
        Log::error("Map tile images failed to load");
        exit(-1);
    }

    // Divide the image into tiles and store the count in each dimension
    sf::Vector2u tileCount;
    tileCount.x = tilesImage.getSize().x / tileSize;
    tileCount.y = tilesImage.getSize().y / tileSize;
    
    // Load the tiles into seperate Textures from the image
    for(unsigned int y = 0; y < tileCount.y; y++) {
        for(unsigned int x = 0; x < tileCount.x; x++) {
            tileImages.push_back(new sf::Texture());
            tileImages.at(y * tileCount.x + x)->loadFromImage(tilesImage, sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
        }
    }

    // Create Tiles in the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(data[x + y * mapSize.x] != '0') {
                Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
                tiles.push_back(tile);
                tiles[tiles.size() - 1]->setImage(tileImages[data[x + y * mapSize.x] - '0' - 1]);
            } 
        }
    }
}

void Level::loadEntites(std::string path){
    std::vector<char> fileData;
    std::ifstream file;
    file.open(path);
    fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();

    std::vector<std::string> buffer;
    std::string number;
    Entity* entity;
    for(int i = 0; i < fileData.size(); i++){
        if(std::isdigit(fileData[i])){
            number += fileData[i];
        } else if(fileData[i] == '\n'){
            buffer.push_back(number);
            number = "";
            switch(std::stoi(buffer[2])) {
                case Entity::ALIEN_SHIP:
                entity = new AlienShip(std::stoi(buffer[0]), std::stoi(buffer[1]), 32, 32);
                ((AlienShip*)entity)->setTexture(Resources::get(Resources::ID::AlienShip));
            }

            entities.push_back(entity);
            buffer.clear();
        } else {
            // comma
            buffer.push_back(number);
            number = "";
        }
    }
}