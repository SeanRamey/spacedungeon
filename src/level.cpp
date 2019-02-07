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
    //for(Tile* tile : tiles){
     //   tile->draw(window);
    //}
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
    //for(Tile* tile : tiles){
     //   tile->update(frameTime, window, entities);
    //}
    for(Entity* entity : entities){
        if(entity != playerShip){
            entity->update(frameTime, window, entities);
        }
    }
}

void handleCollisions() {
    
}

void Level::loadMap(std::string map, std::string images) {

    std::vector<char> fileData;
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

    fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();

    std::string buffer;
    std::vector<std::string> finalData;
    for(int i = 1; i < fileData.size(); i++){
        switch(fileData[i]){
            case ' ':
                // add to final data the proper number read from the file
                finalData.push_back(buffer); 
                buffer.clear();
                break;
            case '\n':
                finalData.push_back(buffer);
                buffer.clear();
                break;
            default:
                buffer.push_back(fileData[i]);
        }
    }
    // image loading and setting up
    sf::Vector2u tileCount;
    sf::Image tileImage;
    if(!tileImage.loadFromFile(images)){
       Log::error("big boy error, couldn't load tile map");
    }

    tileCount.x = tileImage.getSize().x / tileSize; 
    tileCount.y = tileImage.getSize().y / tileSize; 

    for(unsigned int y = 0; y < tileCount.y; y++) {
        for(unsigned int x = 0; x < tileCount.x; x++) {
            tileImages.push_back(new sf::Texture());
            tileImages.at(y * tileCount.x + x)->loadFromImage(tileImage, sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
        }
    }

    sf::Image backGroundImage;
    backGroundImage.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Black);

    // Create Tiles in the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(std::stoi(finalData.at(x + y * mapSize.x)) != std::stoi("0")) {
                Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
                tiles.push_back(tile);
                tiles[tiles.size() - 1]->setImage(tileImages[std::stoi(finalData[x + y * mapSize.x]) - 1]);
            }
        }
    }
    // loading backGround
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