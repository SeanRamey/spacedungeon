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
#include <cmath>
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

Level::Level(std::string levelMapFilename, std::string tileImagesFilename, std::string levelDataFilename, unsigned int tileSize) :
view(),
tileSize(tileSize),
zoomLevel(1.0),
prevZoomLevel(1.0),
lastMousePosition(Input::mousePosition),
selectedTileType(1),
brushSize(1),
saving(false) {
    loadMap(levelMapFilename, tileImagesFilename);
}

Level::~Level(){
    for(Tile* tile : backGroundTiles) {
        delete tile;
    }
    for(Tile* tile : middleTiles) {
        delete tile;
    }
    for(Tile* tile : foreGroundTiles) {
        delete tile;
    }
}


void Level::draw(sf::RenderWindow& window){
    for(Tile* tile : backGroundTiles) {
        tile->draw(window);
    }
    for(Tile* tile : middleTiles) {
        tile->draw(window);
    }
    for(Tile* tile : foreGroundTiles) {
        tile->draw(window);
    }

    sf::Vector2f originalPos = currentTileVisual.getPosition();

    for(unsigned int y = 0; y < brushSize; y++) {
        for(unsigned int x = 0; x < brushSize; x++) {
            currentTileVisual.setPosition(x * tileSize + Input::mouseWorldPosition.x, y * tileSize + Input::mouseWorldPosition.y);
            window.draw(currentTileVisual);
        }
    }
    currentTileVisual.setPosition(originalPos);
}

void Level::update(sf::Time frameTime, sf::RenderWindow& window){

    currentTileVisual.setPosition(sf::Vector2f(Input::mouseWorldPosition));
    currentTileVisual.setTexture(*tileImages.at(selectedTileType));
    currentTileVisual.setOrigin(currentTileVisual.getTextureRect().width / 2, currentTileVisual.getTextureRect().height / 2);

    std::vector<sf::Event> events = Input::getEventList();
    for(sf::Event event : events) {
        if(event.type == sf::Event::Resized) {
            //view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
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
        zoomLevel += 0.05;
    }
    if(Input::checkKey(sf::Keyboard::PageDown)) {
        zoomLevel -= 0.05;
    }
    if((Input::checkKey(sf::Keyboard::LControl) || Input::checkKey(sf::Keyboard::RControl)) && Input::checkKey(sf::Keyboard::S)) {
        saveMap("TestSave.map");
    }
    if(keyTimer.getElapsedTime().asMilliseconds() > keyDelay) {
        keyTimer.restart();
        if(Input::checkKey(sf::Keyboard::Equal)) {
            brushSize++;
        }
        if(Input::checkKey(sf::Keyboard::Hyphen)) {
            brushSize--;
        }
        if(Input::checkKey(sf::Keyboard::LBracket)) {
            selectedTileType--;
            if(selectedTileType < 0) {
                selectedTileType = 0;
            }
            if(selectedTileType > tileImages.size()) {
                selectedTileType = 0;
            }
        }
        if(Input::checkKey(sf::Keyboard::RBracket)) {
            selectedTileType++;
            if(selectedTileType > tileImages.size()) {
                selectedTileType = tileImages.size();
            }
        }
    }
    if(Input::checkMouse(sf::Mouse::Button::Left)) {
        for(unsigned int y = 0; y < brushSize; y++) {
            for(unsigned int x = 0; x < brushSize; x++) {
                changeTile((sf::Vector2i)Input::mouseWorldPosition + sf::Vector2i(y * tileSize, x * tileSize), selectedTileType);
            }
        }
    }

    if(Input::checkMouse(sf::Mouse::Button::Middle)) {
        view.move((lastMousePosition.x - Input::mousePosition.x) * zoomLevel * 2, (lastMousePosition.y - Input::mousePosition.y) * zoomLevel * 2);
        lastMousePosition = Input::mousePosition;
    } else {
        lastMousePosition = Input::mousePosition;
    }

    zoomLevel += -(Input::mouseWheelScrollDelta * 0.05f);

    if(zoomLevel < 0.05) {
        zoomLevel = 0.05;
    } else if(zoomLevel > 5) {
        zoomLevel = 5;
    }

    view.zoom(zoomLevel - prevZoomLevel + 1);
    prevZoomLevel = zoomLevel;
    

    window.setView(view);


}

void Level::changeTile(sf::Vector2i pos, unsigned int tileTypeIndex) {
    if(pos.x < 0 || pos.y < 0) {
        return;
    }
    if(tileTypeIndex > tileImages.size()) {
        tileTypeIndex = tileImages.size();
    }
    if(tileTypeIndex < 0) {
        tileTypeIndex = 0;
    }
    if(pos.x > 0 && pos.y > 0) {
        pos.x = std::trunc(pos.x / tileSize) * tileSize;
        pos.y = std::trunc(pos.y / tileSize) * tileSize;
    }
    for(Tile* tile : backGroundTiles) {
        if(tile->position == (sf::Vector2u)pos) {
            //*tile = Tile(pos, sf::Vector2u(tileSize, tileSize));
            tile->setTexture(tileImages.at(tileTypeIndex), tileTypeIndex);
            return;
        }
    }

    // if there wasn't a tile at the selected position, create a new one
    Tile* otherNewTile = new Tile((sf::Vector2u)pos, sf::Vector2u(tileSize, tileSize));
    otherNewTile->setTexture(tileImages.at(tileTypeIndex), tileTypeIndex);
    backGroundTiles.push_back(otherNewTile);

    if(mapSize.x < (pos.x / tileSize) || mapSize.y < (pos.y / tileSize)) {
        mapSize.x < (pos.x / tileSize) ? mapSize.x = (pos.x / tileSize) : mapSize.y = (pos.y / tileSize);
    }

    std::cout << mapSize.x << ", " << mapSize.y << "\n";
}

void Level::loadMap(std::string map, std::string images) {
   std::ifstream file(map);

    if(!file.is_open()){
        //Log::error("Failed to open file: " + map);
        exit(-1);
    }
    file >> mapSize.x >> mapSize.y;  

    std::vector<char> fileData;
    fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    file.close();

    std::vector<std::string> buffer;
    std::vector<struct tileLayers> mapData;
    std::cout << fileData.size();
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
       //Log::error("failed load tile map");
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

    // Create background tiles in the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(mapData.at(x + y * mapSize.x).backGround != 0) {
                Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
                backGroundTiles.push_back(tile);
                backGroundTiles[backGroundTiles.size() - 1]->setTexture(tileImages[mapData[x + y * mapSize.x].backGround - 1], mapData[x + y * mapSize.x].backGround - 1);
            }
        }
    }

    // Create middle tiles in the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(mapData.at(x + y * mapSize.x).middleGround != 0) {
                Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
                middleTiles.push_back(tile);
                middleTiles[middleTiles.size() - 1]->setTexture(tileImages[mapData[x + y * mapSize.x].middleGround - 1], mapData[x + y * mapSize.x].middleGround - 1);
            }
        }
    }

    // Create foreground tiles in the map
    for(unsigned int y = 0; y < mapSize.y; y++) {
        for(unsigned int x = 0; x < mapSize.x; x++) {
            if(mapData.at(x + y * mapSize.x).foreGround != 0) {
                Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
                foreGroundTiles.push_back(tile);
                foreGroundTiles[foreGroundTiles.size() - 1]->setTexture(tileImages[mapData[x + y * mapSize.x].foreGround - 1], mapData[x + y * mapSize.x].foreGround - 1);
            }
        }
    }
}


void Level::saveMap(std::string map) {
    std::ofstream file(map, std::ios::binary);

    if(!file.is_open()){
        //Log::error("Failed to open file: " + map);
        exit(-1);
    }

    file << mapSize.x << "\n" << mapSize.y << "\n";

    // each position in the map has 3 bytes, 1 byte per layer.
    // each byte is a reference to the tile graphic that represents
    // the tile at that position of that layer.
    std::vector<unsigned char> fileData(mapSize.x * mapSize.y * 3, (unsigned char)0);
    std::vector<unsigned char> backgroundMapData(mapSize.x * mapSize.y, (unsigned char)0);
    std::vector<unsigned char> middlegroundMapData(mapSize.x * mapSize.y, (unsigned char)0);
    std::vector<unsigned char> foregroundMapData(mapSize.x * mapSize.y, (unsigned char)0);

    for(Tile* tile : backGroundTiles) {
        backgroundMapData.at((tile->position.y / 32) * mapSize.x + tile->position.x / 32) = tile->index;
    }
    for(Tile* tile : middleTiles) {
        middlegroundMapData.at((tile->position.y / 32) * mapSize.x + tile->position.x / 32) = tile->index;
    }
    for(Tile* tile : foreGroundTiles) {
        foregroundMapData.at((tile->position.y / 32) * mapSize.x + tile->position.x / 32) = tile->index;
    }


    for(unsigned int i = 0; i < mapSize.x * mapSize.y; i++) {
        fileData.at(i*3) = backgroundMapData.at(i);
        fileData.at(i*3+1) = middlegroundMapData.at(i);
        fileData.at(i*3+2) = foregroundMapData.at(i);
    }

    file.write(reinterpret_cast<char*>(fileData.data()), fileData.size());

}