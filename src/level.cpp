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
    window->draw(backGroundSprite);
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
       Log::error("big boy error, couldn't load tile map");
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
                tiles[tiles.size() - 1]->setImage(tileImages[mapData[x + y * mapSize.x] - 1]);
            }
        }
    }

    // Create an image of the entire map so that only 1 draw call is needed for the whole map
    sf::Image backGroundImage;
    backGroundImage.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Black);

    for(Tile* tile : tiles){
        backGroundImage.copy(tile->getTexture()->copyToImage(), tile->getPosition().x, tile->getPosition().y);
    }

    backGround.loadFromImage(backGroundImage); 
    backGroundSprite.setTexture(backGround);
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
                ((AlienShip*)entity)->setTexture(Resources::get(Resources::ID::ALIENSHIP));
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