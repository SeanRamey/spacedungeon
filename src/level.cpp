#include "level.hpp"
#include "resources.hpp"
#include "log.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h>

Level::Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize) :
playerShip(nullptr),
tileSize(tileSize) ,
healthBar(sf::Vector2i(100, 100), "data/graphics/arial.ttf", ""){
    loadMap(levelMapFilename, tileImagesFilename);
    Resources::load();
    loadEntites(levelDataFilename);
    playerShip = new PlayerShip(50, 50, 32, 32, Resources::get(Resources::ID::PLAYER_SHIP), this);
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

PlayerShip* Level::getPlayer(){
    return this->playerShip;
}

void Level::draw(sf::RenderWindow& window){
    window.draw(backGroundSprite);

    //window.draw(playerShip);
    // for(Tile* tile : tiles){
    //     window.draw(*tile);
    // }
    // for(Entity* entity : entities){
    //     window.draw(*entity);
    // }
    for(unsigned int i = 0; i < entities.size(); ++i) {
        window.draw(*entities.at(i));
    }


}

void Level::update(sf::Time frameTime, sf::RenderWindow& window){
  
    view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    if(!playerIsDead) {
         view.setCenter(playerShip->getPosition().x, playerShip->getPosition().y);
    }
    window.setView(view);

    removeDestroyedEntities();

    for(Tile* tile : tiles){
        tile->update(frameTime);
    }
    for(unsigned int i = 0; i < entities.size(); ++i) {
        entities.at(i)->update(frameTime);
    }
    processCollisions();

    //std::cout << entities.size() << std::endl;
}

bool typeMatches(CollisionPair& pair, Entity::Type type1, Entity::Type type2) {
    if(pair.entity1->type == type1 && pair.entity2->type == type2) {
        return true;
    }
    else if(pair.entity1->type == type2 && pair.entity2->type == type1) {
        Entity* tempEntity = pair.entity1;
        pair.entity1 = pair.entity2;
        pair.entity2 = tempEntity;
        return true;
    }
    else {
        return false;
    }
}

void Level::processCollisions() {

    // std::vector<CollisionPair> collisions;
    // for(Entity* entity1 : entities) {
    //     for(Entity* entity2 : entities) {
    //         if(entity1 != entity2 && entity1->getCollisionRect().intersects(entity2->getCollisionRect())) {
    //             std::cout << "Collision found!\n";
    //             if(collisions.empty()) {
    //                 CollisionPair collisionPair = {entity1, entity2};
    //                 collisions.push_back(collisionPair);
    //                 std::cout << "first collision added\n";
    //             }
    //             for(CollisionPair pair : collisions) {
    //                 if((pair.entity1 == entity1 && pair.entity2 == entity2) || (pair.entity1 == entity2 && pair.entity2 == entity1)) {
    //                     CollisionPair collisionPair = {entity1, entity2};
    //                     collisions.push_back(collisionPair);
    //                     std::cout << "collision added\n";
    //                 }
    //             }
    //         }
    //     }
    // }

    std::vector<CollisionPair> collisions;
    for(int i = 0; i < entities.size(); i++){
        for(int j = i; j < entities.size(); j++){
            Entity* entity1 = entities.at(i);
          
            Entity* entity2 = entities.at(j);
            if(entity1 != entity2 && entity1->getCollisionRect().intersects(entity2->getCollisionRect())){
                collisions.push_back(CollisionPair{entity1, entity2});
            }
        }
    }

    for(CollisionPair pair : collisions) {
        if(typeMatches(pair, Entity::Type::PLAYER_SHIP, Entity::Type::ALIEN_SHIP)) {
            pair.entity1->damage(1); // damage player ship
            pair.entity2->destroy(); // destroy alien ship
        }

        if(typeMatches(pair, Entity::Type::ALIEN_SHIP, Entity::Type::BULLET)) {
            if(!pair.entity2->isDestroyed()) {
                pair.entity1->destroy();
            }
            pair.entity2->destroy();
        }
    }
    

    /* TODO: make sure to add player health as opposed to entities.size()
    for after merge with collisions where health was added */
    healthBar.setPosition(sf::Vector2i(floor(view.getCenter().x - view.getSize().x / 2), floor(view.getCenter().y - view.getSize().y / 2)));
    healthBar.setText(std::to_string(entities.size()));
}

void Level::removeDestroyedEntities() {
    // Create a list of entities to delete
    // THEN remove them, because deleting
    // entities while iterating over the
    // container that holds them doesn't
    // play nice.
    std::vector<Entity*> entitiesToRemove;
    for(Entity* entity : entities) {
        if(entity->isDestroyed()) {
            entitiesToRemove.push_back(entity);
        }
    }

    for(Entity* entity : entitiesToRemove) {
        deleteEntity(entity);
    }
}

void Level::addEntity(Entity* entity) {
    if(entity == nullptr) {
        return; // not valid pointer
    }
    entities.push_back(entity);
}

void Level::deleteEntity(Entity* entity) {
    if(entity == playerShip) {
        playerIsDead = true;
        playerShip = nullptr;
    }
    if(entity != nullptr) {
        delete entity; // delete the entity before removal
    }
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end()); // removes entity pointer from list
    entities.shrink_to_fit();
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
       Log::error("failed to load tile map image: " + images);
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

    // Create an image of the entire map so that only 1 draw call is needed for the whole map
    sf::Image backGroundImage;
    backGroundImage.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Black);

    for(Tile* tile : tiles) {
        backGroundImage.copy(tile->getTexture()->copyToImage(), tile->position.x, tile->position.y);
    }

    backGroundTexture.loadFromImage(backGroundImage); 
    backGroundSprite.setTexture(backGroundTexture);
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
    for(int i = 0; i < fileData.size(); i++) {
        sf::Vector2u entityPosition;
        if(std::isdigit(fileData[i])) {
            number += fileData[i];
        } else if(fileData[i] == '\n'){
            buffer.push_back(number);
            number.clear();
            entityPosition.x = std::stoi(buffer[0]);
            entityPosition.y = std::stoi(buffer[1]);
            switch(std::stoi(buffer[2])) {
                case 1:
                entity = new AlienShip(entityPosition.x, entityPosition.y, 32, 32, Resources::get(Resources::ID::ALIEN_SHIP), this);
            }

            entities.push_back(entity);
            buffer.clear();
        } else {
            // comma
            buffer.push_back(number);
            number.clear();
        }
    }
}