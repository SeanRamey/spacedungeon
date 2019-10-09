#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>
#include "entity.hpp"
#include "player-ship.hpp"
#include "tile.hpp"
#include "ui-text-element.hpp"
#include "ui-image-element.hpp"
#include "alien-ship.hpp"
#include "game-state.hpp"
#include "map.hpp"

struct CollisionPair {
	Entity *entity1;
	Entity *entity2;
	sf::Vector2f pointOfCollision;
	float time;
};

enum TILE_LAYER {
	FLOOR,
	WALL,
	NUM_LAYERS
};

class Level : public GameState {

	public:
	Level(Game* game, std::string levelDataFileName, std::string entityDataFileName, std::string wallImagesFileName, std::string floorImagesFileName, unsigned int tileSize = 32);
	~Level();
	void processCollisions();
	bool checkWon();
	bool checkLose();
	void loadEntites(std::string);
	void removeDestroyedEntities();
	PlayerShip* getPlayer();
	void setPlayer(PlayerShip* playerShip);
	void loadMap();
	void loadLayer(TILE_LAYER layer);
	void addEntity(Entity* entity);
	void deleteEntity(Entity* entity);

	void init();
	void clear();
	void update(sf::Time frameTime);
	void draw(sf::RenderWindow& window);

	private:
	Map map;
	std::vector<Entity*> entities;
	PlayerShip* playerShip;

	bool hasWon = false;
	bool playerIsDead = false;

	UITextElement healthText;
	UIImageElement healthBar;
	UITextElement gameOver;

	unsigned int tileSize = 32;
	const std::string floorImagesFileName;
	const std::string wallImagesFileName;
	const std::string levelDataFileName;
	const std::string entityDataFileName;
};
#endif
