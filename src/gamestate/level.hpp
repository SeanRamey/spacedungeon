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
	private:

		std::vector<Entity*> entities;

		std::vector<Tile*> floorTiles;
		std::vector<Tile*> wallTiles;

		PlayerShip* playerShip;
		std::vector<sf::Texture*> floorImages;
		std::vector<sf::Texture*> wallImages;

		sf::Sprite floorSprite;
		sf::Texture floorTexture;

		sf::Sprite wallSprite;
		sf::Texture wallTexture;

		sf::Sprite shadowSprite;
		sf::Texture shadowTexture;

		sf::Vector2u mapSize;
		unsigned int tileSize;

		bool hasWon = false;
		bool playerIsDead = false;

		UITextElement healthText;
		UIImageElement healthBar;

		UITextElement gameOver;

		const std::string shadowFileName;
		const std::string floorFileName;
		const std::string wallFileName;
		const std::string shadowImagesFileName;
		const std::string floorImagesFileName;
		const std::string wallImagesFileName;
		const std::string levelDataFileName;

	public:
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

		Level(Game* game, std::string floorMapFileName, std::string wallMapFileName, std::string floorImagesFileName, std::string wallImagesFileName, std::string levelDataFileName, unsigned int tileSize);
		~Level();
};
#endif
