#ifndef MAP_HPP
#define MAP_HPP
#include "allpch.hpp"
#include "tile.hpp"

struct MapLayer {
	int floor;
	int wall;
};

// TODO: rewrite map class to work with ldtk editor
class Map : public sf::Drawable {
	public:
	Map();
	Map(std::string dataFile, std::string wallImagesFile, std::string floorImagesFile, unsigned int tileWidth = 32, unsigned int tileHeight = 32);
	~Map();
	void load(std::string dataFile, std::string wallImagesFile, std::string floorImagesFile, unsigned int tileWidth = 32, unsigned int tileHeight = 32);
	void load();
	unsigned int getWidth();
	unsigned int getHeight();
	const std::vector<std::unique_ptr<Tile>>& getWallTiles();

	private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int tileWidth = 32;
	unsigned int tileHeight = 32;
	std::string dataFile;
	std::string floorImageFile;
	std::string wallImageFile;
	std::vector<std::unique_ptr<sf::Texture>> wallTextures;
	std::vector<std::unique_ptr<sf::Texture>> floorTextures;
	std::vector<std::unique_ptr<Tile>> wallTiles;
	std::vector<std::unique_ptr<Tile>> floorTiles;
	sf::Texture compiledFloorTexture;
	sf::Sprite floorSprite;
};

#endif
