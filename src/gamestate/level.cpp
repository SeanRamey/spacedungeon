#include "level.hpp"
#include "resources.hpp"
#include "log.hpp"
#include "game.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h>

Level::Level(Game* game, std::string levelMapFileName, std::string tileImagesFileName, std::string levelDataFileName, unsigned int tileSize) :
GameState(game),
tileSize(tileSize),
healthText(sf::Vector2f(0, 0), "data/graphics/Void_2058.ttf", ""),
healthBar(sf::Vector2f(0, 0), nullptr),
gameOver(sf::Vector2f(0, 0), "data/graphics/Void_2058.ttf", "Game Over"),
levelMapFileName(levelMapFileName),
tileImagesFileName(tileImagesFileName),
levelDataFileName(levelDataFileName) {
    
    Resources::load();
    //this->playerShip = new PlayerShip(50, 50, 32, 32, Resources::get(Resources::ID::PLAYER_SHIP), this, 100);
    //entities.push_back(this->playerShip);
    healthBar.setTexture(Resources::get(Resources::ID::HEALTH_BAR));
    playerIsDead = false;

}

Level::~Level(){
    for(Entity* entity : entities) {
        delete entity;
    }
    for(Tile* tile : middleTiles) {
        delete tile;
    }
    for(Tile* tile : foreGroundTiles) {
        delete tile;
    }
    for(sf::Texture* texture : tileImages) {
        delete texture;
    }
}

bool Level::checkWon(){
    return false;
}

bool Level::checkLose(){
    return playerIsDead;
}

PlayerShip* Level::getPlayer(){
    return this->playerShip;
}

void Level::draw(sf::RenderWindow& window){
    window.draw(backGroundSprite);
    window.draw(middleGroundSprite);
    for(unsigned int i = 0; i < entities.size(); ++i) {
        if(!(entities.at(i) == playerShip && playerIsDead)){
            window.draw(*entities.at(i));
        }
    }
    window.draw(foreGroundSprite);
    if(!playerIsDead){
        window.draw(healthBar);
        window.draw(healthText);
    } else {
        window.draw(gameOver);
    }

}

void Level::update(sf::Time frameTime, sf::RenderWindow& window){
	//std::cout << playerShip->getHitpoints() << "  " << playerShip<< std::endl;
    view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    if(!playerIsDead){
         view.setCenter(playerShip->getPosition().x, playerShip->getPosition().y);
    }
    window.setView(view);

    if(!playerIsDead){
        float xscale = playerShip->getHitpoints() / 100.0; // percent of total
        healthBar.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - view.getSize().y / 2 + 16 * 1.2));
        healthBar.updateSize(sf::Vector2f(xscale, 1));
        healthBar.update();
        healthText.setPosition(healthBar.getPosition()); // sets position of text to center of health bar
        healthText.setText(std::to_string(playerShip->getHitpoints()));
        healthText.update();
    } else {
        gameOver.setPosition(view.getCenter());
    }


    removeDestroyedEntities();

    for(Tile* tile : middleTiles){
        tile->update(frameTime);
    }
    for(Tile* tile : foreGroundTiles){
        tile->update(frameTime);
    }

    for(unsigned int i = 0; i < entities.size(); ++i) {
        if(!(entities.at(i) == playerShip && playerIsDead)){
            entities.at(i)->update(frameTime);
        }
    }
    processCollisions();
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
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end()); // removes entity pointer from list
    entities.shrink_to_fit();
    if(entity == playerShip) { // player dies
        playerIsDead = true;
        return;
    }

    if(entity != nullptr) {
        delete entity; // delete the entity before removal
    }
}

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

void Level::loadMap(std::string map, std::string images){
    std::ifstream file(map);

    if(!file.is_open()){
        Log::error("Failed to open file: " + map);
        exit(-1);
    }
    file >> mapSize.x >> mapSize.y;  

    std::vector<char> fileData;
    fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();

    std::vector<std::string> buffer;
    std::vector<struct tileLayers> mapData;
    for(int i = 1; i < fileData.size(); i++) {
            switch(fileData[i]) {
                case '\n':
                case ' ':
                    mapData.push_back(tileLayers((unsigned char)std::stoul(buffer[0]), (unsigned char)std::stoul(buffer[1]), (unsigned char)std::stoul(buffer[2]))); // add the current buffer to mapData as an unsigned char
                    buffer.clear();
                    break;
                default:
                    int j = 0;
                    buffer.push_back(std::string());
                    while(true){
 
                        if(fileData[i] == ',' || fileData[i] == ' ' || fileData[i] == '\n') {
                            j++;
                            if(j == 3)  {
                                i--; 
                                break;
                            }
                            if(fileData[i] == ','){
                                i++;
                                buffer.push_back(std::string());
                            }
                        }
                        buffer[j] += fileData[i];
                        i++;
                    }
        }
    }

    // Load the tileset source image
    sf::Image tilesetImage;
    if(!tilesetImage.loadFromFile(images)){
       Log::error("failed load tile map");
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

    // Create an image of the entire map so that only 1 draw call is needed for the whole map
    sf::Image backGroundImage;
    backGroundImage.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Transparent);

    // Create background image of the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(mapData.at(x + y * mapSize.x).backGround != 0) {
                backGroundImage.copy(tileImages[mapData[x + y * mapSize.x].backGround - 1]->copyToImage(), x * tileSize, y * tileSize);
            }
        }
    }
    
    // Create middle tiles in the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(mapData.at(x + y * mapSize.x).middleGround != 0) {
                Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
                middleTiles.push_back(tile);
                middleTiles[middleTiles.size() - 1]->setTexture(tileImages[mapData[x + y * mapSize.x].middleGround - 1]);
            }
        }
    }

    // Create foreground tiles in the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(mapData.at(x + y * mapSize.x).foreGround != 0) {
                Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
                foreGroundTiles.push_back(tile);
                foreGroundTiles[foreGroundTiles.size() - 1]->setTexture(tileImages[mapData[x + y * mapSize.x].foreGround - 1]);
            }
        }
    }

    backGroundTexture.loadFromImage(backGroundImage); 
    backGroundSprite.setTexture(backGroundTexture);

    sf::Image middleGroundImage;
    middleGroundImage.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Transparent);

    for(Tile* tile : middleTiles) {
        middleGroundImage.copy(tile->getTexture()->copyToImage(), tile->position.x, tile->position.y);
    }

    middleGroundTexture.loadFromImage(middleGroundImage); 
    middleGroundSprite.setTexture(middleGroundTexture);

    sf::Image foreGroundImage;
    foreGroundImage.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Transparent);

    for(Tile* tile : foreGroundTiles) {
        foreGroundImage.copy(tile->getTexture()->copyToImage(), tile->position.x, tile->position.y);
    }

    foreGroundTexture.loadFromImage(foreGroundImage); 
    foreGroundSprite.setTexture(foreGroundTexture);
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
            switch(std::stoi(buffer[2])) { // third element is type of entiy
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

void Level::init() {
	std::cout << "level initialized: " << this << std::endl;
    playerIsDead = false;
    loadMap(levelMapFileName, tileImagesFileName);
    loadEntites(levelDataFileName);    
}

void Level::clear(){
    // memory management
    for(Entity* entity : entities){
        if(entity != playerShip){
            delete entity;
        }
    }
    entities.clear();
    for(Tile* tile : foreGroundTiles){
        delete tile;
    }
    foreGroundTiles.clear();
    for(Tile* tile : middleTiles){
        delete tile;
    }
    middleTiles.clear();
    for(sf::Texture* tileImage : tileImages){
        delete tileImage;
    }
    tileImages.clear();
}

void Level::setPlayer(PlayerShip* playerShip){
    entities.erase(std::remove(entities.begin(), entities.end(), this->playerShip), entities.end());
    entities.shrink_to_fit();
    this->playerShip = playerShip;
    playerIsDead = false;
    entities.push_back(this->playerShip);
}
