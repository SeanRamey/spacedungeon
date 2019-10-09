#include "allpch.hpp"
#include "map.hpp"
#include "log.hpp"

std::shared_ptr<sf::Image> loadTileset(const std::string tilesetImageFile);
std::vector<std::unique_ptr<sf::Texture>> loadTilesetTextures(const sf::Image& tilesetImage, unsigned int tileWidth, unsigned int tileHeight);
sf::IntRect getCellRect(unsigned int cellIndex, unsigned int cellWidth, unsigned int cellHeight, unsigned int sourceWidth, unsigned int sourceHeight);

///////////////////////////
Map::Map() {

}

///////////////////////////
Map::Map(std::string dataFile, std::string wallImagesFile, std::string floorImagesFile, unsigned int tileWidth, unsigned int tileHeight)
: dataFile(dataFile)
, wallImageFile(wallImagesFile)
, floorImageFile(floorImagesFile)
, tileWidth(tileWidth)
, tileHeight(tileHeight) {

}

///////////////////////////
Map::~Map() {
}

///////////////////////////
void Map::load(std::string dataFile, std::string wallImagesFile, std::string floorImagesFile, unsigned int tileWidth, unsigned int tileHeight) {
	this->dataFile = dataFile;
	this->wallImageFile = wallImagesFile;
	this->floorImageFile = floorImagesFile;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	load();
}

///////////////////////////
void Map::load() {
	if(width != 0 || height != 0) {
		return; // Don't reload because not sure if that would cause memory issues with smart pointers.
	}

	std::ifstream file(dataFile);

	if(!file.is_open()){
		std::string message = "Failed to open file: " + dataFile;
		Log::error(message);
		exit(-1);
	}
	file >> width >> height;

	std::vector<char> fileData;
	fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	std::string buffer;
	std::vector<MapLayer> parsedData;
	bool isFloor = true; // floor data comes first
	MapLayer layerBuffer = {0};
	for(size_t i = 1; i < fileData.size(); i++) {
		switch(fileData[i]) {
			case '\n':
			case ' ':
			case ',':
				if(isFloor) {
					layerBuffer.floor = std::stoi(buffer);
					buffer.clear();
					isFloor = false; // we just stored the floor data, so next is wall data
				} else {
					layerBuffer.wall = std::stoi(buffer);
					parsedData.push_back(layerBuffer);
					buffer.clear();
					layerBuffer.floor = 0;
					layerBuffer.wall = 0;
					isFloor = true; // reset back to floor data
				}
				break;
			default:
				buffer.push_back(fileData[i]);
				break;
		}
	}

	std::shared_ptr<sf::Image> wallTilesetImage = loadTileset(wallImageFile);
	std::shared_ptr<sf::Image> floorTilesetImage = loadTileset(floorImageFile);

	wallTextures = loadTilesetTextures(*wallTilesetImage, tileWidth, tileHeight);
	floorTextures = loadTilesetTextures(*floorTilesetImage, tileWidth, tileHeight);

	// Create wall tiles in the map
	for(unsigned int y = 0; y < height; y++) {
		for(unsigned int x = 0; x < width; x++) {
			if(parsedData.at(x + y * width).wall != 0) {
				std::unique_ptr<Tile> tile = std::make_unique<Tile>(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
				tile->setTexture(wallTextures[parsedData[x + y * width].wall - 1].get());
				wallTiles.push_back(std::move(tile));
			}
		}
	}

	// Create floor tiles in the map
	for(unsigned int y = 0; y < height; y++) {
		for(unsigned int x = 0; x < width; x++) {
			if(parsedData.at(x + y * width).floor != 0) {
				std::unique_ptr<Tile> tile = std::make_unique<Tile>(x * tileWidth, y * tileHeight, tileWidth, tileHeight);
				tile->setTexture(floorTextures[parsedData[x + y * width].floor - 1].get());
				floorTiles.push_back(std::move(tile));
			}
		}
	}

	// sf::Image compiledFloorImage;
	// compiledFloorImage.create(width, height, sf::Color::Transparent);

	// // Compile floor image of the map
	// for(unsigned int y = 0; y < height; y++) {
	// 	for(unsigned int x = 0; x < width; x++) {
	// 		if(parsedData.at(x + y * width).floor != 0) {
	// 			// copy to image
	// 			sf::IntRect tileRect = getCellRect(parsedData.at(x + y * width).floor, tileWidth, tileHeight, floorTilesetImage->getSize().x, floorTilesetImage->getSize().y);
	// 			compiledFloorImage.copy(*floorTilesetImage, x * tileWidth, y * tileHeight, tileRect);
	// 			std::cout << "floor tile: " << parsedData.at(x + y * width).floor << " tileRect: " << tileRect.left << "," << tileRect.top << " " << tileRect.width << "," << tileRect.height << "\n";
	// 		}
	// 	}
	// }
	// if(!compiledFloorTexture.loadFromImage(compiledFloorImage)) {
	// 	Log::error("Unable to load map floor texture");
	// 	exit(-1);
	// }
	// floorSprite.setTexture(compiledFloorTexture);
}

///////////////////////////
std::shared_ptr<sf::Image> loadTileset(const std::string tilesetImageFile) {

	// Load the tileset source image
	std::shared_ptr<sf::Image> tilesetImage = std::make_shared<sf::Image>();
	if(!tilesetImage->loadFromFile(tilesetImageFile)){
		Log::error("Failed to load a tileset image from file: " + tilesetImageFile);
		exit(-1);
	}

	return tilesetImage;
}

///////////////////////////
std::vector<std::unique_ptr<sf::Texture>> loadTilesetTextures(const sf::Image& tilesetImage, unsigned int tileWidth, unsigned int tileHeight) {

	std::vector<std::unique_ptr<sf::Texture>> tileTextures;

	// Store how many tiles are in the tileset
	sf::Vector2u tileCount;
	tileCount.x = tilesetImage.getSize().x / tileWidth;
	tileCount.y = tilesetImage.getSize().y / tileHeight;

	// Store each tile graphic as a sf::Texture in an array
	for(unsigned int y = 0; y < tileCount.y; y++) {
		for(unsigned int x = 0; x < tileCount.x; x++) {
			tileTextures.push_back(std::make_unique<sf::Texture>());
			tileTextures.at(y * tileCount.x + x)->loadFromImage(tilesetImage, sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
		}
	}

	return tileTextures;
}

///////////////////////////
sf::IntRect getCellRect(unsigned int cellIndex, unsigned int cellWidth, unsigned int cellHeight, unsigned int sourceWidth, unsigned int sourceHeight) {
	sf::IntRect targetRect;

	// get x,y coordinates of current cell
	unsigned int cellX;
	unsigned int cellY;
	sf::Vector2u numCells;
	numCells.x = sourceWidth / cellWidth;
	numCells.y = sourceHeight / cellHeight;
	cellX = cellIndex % numCells.x;
	if(cellIndex - cellX > 0) {
		cellY = (cellIndex - cellX) / numCells.x;
	} else {
		cellY = 0;
	}

	targetRect.left = cellX * cellWidth;
	targetRect.top = cellY * cellHeight;
	targetRect.width = cellWidth;
	targetRect.height = cellHeight;

	return targetRect;

}

///////////////////////////
unsigned int Map::getWidth() {
	return width;
}

///////////////////////////
unsigned int Map::getHeight() {
	return height;
}

///////////////////////////
const std::vector<std::unique_ptr<Tile>>& Map::getWallTiles() {
	return wallTiles;
}

///////////////////////////
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//target.draw(floorSprite, states);
	for(auto tile = floorTiles.begin(); tile != floorTiles.end(); ++tile) {
		target.draw(*tile->get(),states);
	}
	for(auto tile = wallTiles.begin(); tile != wallTiles.end(); ++tile) {
		target.draw(*tile->get(),states);
	}
}
