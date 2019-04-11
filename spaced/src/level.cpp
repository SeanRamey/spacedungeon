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
//playerShip(nullptr),
view(),
tileSize(tileSize) {
    loadMap(levelMapFilename, tileImagesFilename);
    //Resources::load();
    //loadEntites(levelDataFilename);
    //playerShip = new PlayerShip(50, 50, 32, 32, Resources::get(Resources::ID::PLAYER_SHIP), this);
    //entities.push_back(playerShip);

}

Level::~Level(){
    // for(Entity* entity : entities) {
    //     delete entity;
    // }
    for(Tile* tile : tiles) {
        delete tile;
    }
    // for(sf::Texture* texture : tileImages) {
    //     delete texture;
    // }
}

// bool Level::checkWon(){
//     return false;
// }

// PlayerShip* Level::getPlayer(){
//     return this->playerShip;
// }

void Level::draw(sf::RenderWindow& window){
    //window.draw(backGroundSprite);

    //window.draw(playerShip);
    // for(Tile* tile : tiles){
    //     //window.draw(*tile);
    //     tile->draw(window);
    // }

    // Create an image of the entire map so that only 1 draw call is needed for the whole map
    sf::Image backGroundImage;
    backGroundImage.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Black);

    for(Tile* tile : tiles) {
        backGroundImage.copy(tile->getTexture()->copyToImage(), tile->position.x, tile->position.y);
    }

    backGroundTexture.loadFromImage(backGroundImage); 
    backGroundSprite.setTexture(backGroundTexture);
    window.draw(backGroundSprite);

    // for(unsigned int i = 0; i < tiles.size(); ++i) {
    //     //tiles.at(i)->draw(window);
    //     sf::Sprite tileSprite = sf::Sprite(*tiles.at(i)->getTexture());
    //     std::cout << (void*)tiles.at(i)->getTexture() << "\n";
    //     window.draw(tileSprite);
    // }
    // for(Entity* entity : entities){
    //     window.draw(*entity);
    // }
    // for(unsigned int i = 0; i < entities.size(); ++i) {
    //     window.draw(*entities.at(i));
    // }


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



    //removeDestroyedEntities();

    // for(Tile* tile : tiles){
    //     tile->update(frameTime);
    // }
    // for(unsigned int i = 0; i < entities.size(); ++i) {
    //     entities.at(i)->update(frameTime);
    // }
    //processCollisions();

    //std::cout << entities.size() << std::endl;
}

// void Level::addEntity(Entity* entity) {
//     if(entity == nullptr) {
//         return; // not valid pointer
//     }
//     entities.push_back(entity);
// }

// void Level::deleteEntity(Entity* entity) {
//     if(entity == playerShip) {
//         playerIsDead = true;
//         playerShip = nullptr;
//     }
//     if(entity != nullptr) {
//         delete entity; // delete the entity before removal
//     }
//     entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end()); // removes entity pointer from list
//     entities.shrink_to_fit();
// }

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

    // // Create an image of the entire map so that only 1 draw call is needed for the whole map
    // sf::Image backGroundImage;
    // backGroundImage.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Black);

    // for(Tile* tile : tiles) {
    //     backGroundImage.copy(tile->getTexture()->copyToImage(), tile->position.x, tile->position.y);
    // }

    // backGroundTexture.loadFromImage(backGroundImage); 
    // backGroundSprite.setTexture(backGroundTexture);
}

// void Level::loadEntites(std::string path){
//     std::vector<char> fileData;
//     std::ifstream file;
//     file.open(path);
//     fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
//     file.close();


//     std::vector<std::string> buffer;
//     std::string number;
//     Entity* entity;
//     for(int i = 0; i < fileData.size(); i++) {
//         sf::Vector2u entityPosition;
//         if(std::isdigit(fileData[i])) {
//             number += fileData[i];
//         } else if(fileData[i] == '\n'){
//             buffer.push_back(number);
//             number.clear();
//             entityPosition.x = std::stoi(buffer[0]);
//             entityPosition.y = std::stoi(buffer[1]);
//             switch(std::stoi(buffer[2])) {
//                 case 1:
//                 entity = new AlienShip(entityPosition.x, entityPosition.y, 32, 32, Resources::get(Resources::ID::ALIEN_SHIP), this);
//             }

//             entities.push_back(entity);
//             buffer.clear();
//         } else {
//             // comma
//             buffer.push_back(number);
//             number.clear();
//         }
//     }
// }