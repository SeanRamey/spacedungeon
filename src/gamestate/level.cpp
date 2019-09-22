#include "stdpch.hpp"
#include "level.hpp"
#include "resources.hpp"
#include "log.hpp"
#include "game.hpp"
#include "collision-tests.hpp"

Level::Level(Game* game, std::string floorMapFileName, std::string wallMapFileName, std::string floorImagesFileName, std::string wallImagesFileName, std::string levelDataFileName, unsigned int tileSize) :
GameState(game),
tileSize(tileSize),
healthText(sf::Vector2f(0, 0), "data/graphics/Void_2058.ttf", ""),
healthBar(sf::Vector2f(0, 0), nullptr),
gameOver(sf::Vector2f(0, 0), "data/graphics/Void_2058.ttf", "Game Over"),
floorFileName(floorMapFileName),
wallFileName(wallMapFileName),
floorImagesFileName(floorImagesFileName),
wallImagesFileName(wallImagesFileName),
levelDataFileName(levelDataFileName){
	this->playerShip = new PlayerShip(50, 50, 32, 32, Resources::getTexture(Resources::TEXTURE_ID::PLAYER_SHIP), this, 100);
	entities.push_back(this->playerShip);
	healthBar.setTexture(Resources::getTexture(Resources::TEXTURE_ID::HEALTH_BAR));
}

Level::~Level(){
	for(Entity* entity : entities) {
		delete entity;
	}
	for(Tile* tile : floorTiles) {
		delete tile;
	}
	for(Tile* tile : wallTiles) {
		delete tile;
	}
	for(sf::Texture* texture : floorImages) {
		delete texture;
	}
	for(sf::Texture* texture : wallImages) {
		delete texture;
	}
}

// TODO implement checkWon function
bool Level::checkWon(){
	return false;
}

bool Level::checkLose(){
	// CLANG COMPILER BUG
	// if(playerIsDead) {
	//     return true;
	// }
	return playerIsDead;
}

PlayerShip* Level::getPlayer(){
	return this->playerShip;
}

void Level::draw(sf::RenderWindow& window){
	window.draw(floorSprite);
	window.draw(shadowSprite);
	for(unsigned int i = 0; i < entities.size(); ++i) {
		if(!(entities.at(i) == playerShip && playerIsDead)){
			window.draw(*entities.at(i));
		}
	}
	window.draw(wallSprite);
	if(!playerIsDead){
		window.draw(healthBar);
		window.draw(healthText);
	} else {
		window.draw(gameOver);
	}

}

void Level::update(sf::Time frameTime){
	view.setSize(sf::Vector2f(Resources::window->getSize().x, Resources::window->getSize().y));
	if(!checkLose()){
		view.setCenter(playerShip->getPosition().x, playerShip->getPosition().y);
	}
	Resources::window->setView(view);

	// Draw healthbar or gameover
	if(!checkLose()){
		float xscale = playerShip->getHitpoints() / 100.0; // percent of total
		healthBar.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - view.getSize().y / 2 + 16 * 1.2));
		healthBar.updateSize(sf::Vector2f(xscale, 1));
		healthBar.update();
		healthText.setPosition(healthBar.getPosition()); // sets position of text to center of health bar
		healthText.setText(std::to_string(playerShip->getHitpoints()));
		healthText.update();
	} else {
		gameOver.setPosition(view.getCenter());
		// exit level
		game->popState();
	}

	removeDestroyedEntities();
	for(Tile* tile : wallTiles) {
		tile->update(frameTime);
	}
	for(Tile* tile : floorTiles) {
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

Entity* getMatchingEntity(CollisionPair pair, Entity::Type type)
{
	if(pair.entity1->type == type)
	{
		return pair.entity1;
	}
	else
	if(pair.entity2->type == type)
	{
		return pair.entity2;
	}
	else
	{
		return nullptr;
	}

}

void Level::processCollisions() {

	// Implement line collisions
	// Need to iterate through all objects creating a line from their previous position
	// to their current one, then compare each line to all other objects' lines.
	// Find all the collisions and put them in a container.
	//
	// Iterate over all the collisions and get the time of collision and position of collision.
	// Handle each collision at the position of collision one at a time starting with the first chonological collision.
	// Each time a collision is handled, the remainder of frame time must be calculated from the amount of time
	// it took to reach each collision subtracted from the full frame time.
	// Then all the other colliding object must be updated again with the remaining frame time.
	// Keep doing this until the full frame time and collisions are accounted for.

	// Iterate over all entities and create pairs of Entities that are colliding.
	std::vector<CollisionPair> collisions;
	for(size_t i = 0; i < entities.size(); i++){
		for(size_t j = i; j < entities.size(); j++){
			Entity* entity1 = entities.at(i);
			Entity* entity2 = entities.at(j);

			CollisionPair collision = {entity1, entity2, sf::Vector2f(0,0), 0.0f};
			if(entity1 != entity2 &&
				Collision::TestMovingAABB(entity1->getCollisionRect(), entity2->getCollisionRect(), entity1->getFrameVelocity(), entity2->getFrameVelocity(), &collision.time)
			) {
				collisions.push_back(collision);
			}
		}
	}

	// Iterate over all colliding Entities and handle each appropriately.
	for(CollisionPair pair : collisions) {

		if(typeMatches(pair, Entity::Type::PLAYER_SHIP, Entity::Type::ALIEN_SHIP)) {
			((PlayerShip*)getMatchingEntity(pair, Entity::Type::PLAYER_SHIP))->damage(1);
			((AlienShip*)getMatchingEntity(pair, Entity::Type::ALIEN_SHIP))->destroy();
			Resources::playSound(Resources::SOUND_ID::SND_HIT);
		}

		if(typeMatches(pair, Entity::Type::ALIEN_SHIP, Entity::Type::BULLET)) {
			if(!((Bullet*)getMatchingEntity(pair, Entity::Type::BULLET))->isDestroyed()) {
				((AlienShip*)getMatchingEntity(pair, Entity::Type::ALIEN_SHIP))->destroy();
				((Bullet*)getMatchingEntity(pair, Entity::Type::BULLET))->destroy();
			}
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

/*
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
*/

void Level::loadMap() {
	for(size_t i = 0; i < TILE_LAYER::NUM_LAYERS; ++i) {
		loadLayer((TILE_LAYER)i);
	}
}

void Level::loadLayer(TILE_LAYER layer) {
	std::string mapFile, imageFile;
	std::vector<sf::Texture*>* tileImages;
	sf::Texture* textureToLoad;
	sf::Sprite* spriteToLoad;
	std::vector<Tile*>* tilesToLoad;

	switch(layer) {
		case WALL:
			mapFile = wallFileName;
			imageFile = wallImagesFileName;
			tileImages = &wallImages;
			textureToLoad = &wallTexture;
			spriteToLoad = &wallSprite;
			tilesToLoad = &wallTiles;
			break;
		case FLOOR:
			mapFile = floorFileName;
			imageFile = floorImagesFileName;
			tileImages = &floorImages;
			textureToLoad = &floorTexture;
			spriteToLoad = &floorSprite;
			tilesToLoad = &floorTiles;
			break;
		default:
			Log::error("Unhandled layer in map loading!");
			return;
	}

	std::ifstream file(mapFile);

	if(!file.is_open()){
		Log::error("Failed to open file: " + mapFile);
		exit(-1);
	}

	// read in map dimensions
	file >> mapSize.x >> mapSize.y;

	std::vector<char> fileData;
	fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	std::string buffer;
	std::vector<int> parsedData;
	for(size_t i = 1; i < fileData.size(); i++) {
		switch(fileData[i]) {
			case '\n':
			case ' ':
				parsedData.push_back(std::stoi(buffer));
				buffer.clear();
				break;
			default:
				buffer.push_back(fileData[i]);
				break;
		}
	}

	// Load the tileset source image
	sf::Image tilesetImage;
	if(!tilesetImage.loadFromFile(imageFile)){
		Log::error("failed load tile map image");
	}

	// counting amount of tiles in the image
	sf::Vector2u tileCount;
	tileCount.x = tilesetImage.getSize().x / tileSize;
	tileCount.y = tilesetImage.getSize().y / tileSize;
	// Store each tile graphic as a sf::Texture in an array
	for(unsigned int y = 0; y < tileCount.y; y++) {
		for(unsigned int x = 0; x < tileCount.x; x++) {
			tileImages->push_back(new sf::Texture());
			tileImages->at(y * tileCount.x + x)->loadFromImage(tilesetImage, sf::IntRect(x * tileSize, y * tileSize, tileSize, tileSize));
		}
	}

	// create a temporary image to create textures
	sf::Image image;
	image.create(mapSize.x * tileSize, mapSize.y * tileSize, sf::Color::Transparent);

	// Create background image of the map
	for(unsigned int y = 0; y < mapSize.y; y++) {
		for(unsigned int x = 0; x < mapSize.x; x++) {
			if(parsedData.at(x + y * mapSize.x) != 0) {
				// copy to image
				image.copy(tileImages->at(parsedData[x + y * mapSize.x] - 1)->copyToImage(), x * tileSize, y * tileSize);

				// create tile
				Tile *tile = new Tile(x * tileSize, y * tileSize, tileSize, tileSize);
				tilesToLoad->push_back(tile);
				tilesToLoad->back()->setTexture(tileImages->at(parsedData[x + y * mapSize.x] - 1));
			}
		}
	}

	for(Tile* tile : *tilesToLoad) {
		image.copy(tile->getTexture()->copyToImage(), tile->position.x, tile->position.y);
	}

	textureToLoad->loadFromImage(image);
	spriteToLoad->setTexture(*textureToLoad);
}
/*
void Level::loadMap(std::string map, std::string floorImages, std::string shadowImages, ){
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
	for(size_t i = 1; i < fileData.size(); i++) {
			switch(fileData[i]) {
				case '\n':
				case ' ':
					mapData.push_back(tileLayers((unsigned char)std::stoi(buffer[0]), (unsigned char)std::stoi(buffer[1]), (unsigned char)std::stoi(buffer[2]))); // add the current buffer to mapData as an unsigned char
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
*/

void Level::loadEntites(std::string path){
	std::vector<char> fileData;
	std::ifstream file;
	file.open(path);
	fileData.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	std::vector<std::string> buffer;
	std::string number;
	Entity* entity;
	for(size_t i = 0; i < fileData.size(); i++) {
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
				entity = new AlienShip(entityPosition.x, entityPosition.y, 32, 32, Resources::getTexture(Resources::TEXTURE_ID::ALIEN_SHIP), this);
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
	playerIsDead = false;
	loadMap();
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

	for(Tile* tile : floorTiles){
		delete tile;
	}
	for(Tile* tile : wallTiles){
		delete tile;
	}
	floorTiles.clear();
	wallTiles.clear();

	for(sf::Texture* tileImage : floorImages){
		delete tileImage;
	}
	for(sf::Texture* tileImage : wallImages){
		delete tileImage;
	}
	floorImages.clear();
	wallImages.clear();
}

void Level::setPlayer(PlayerShip* playerShip){
	entities.erase(std::remove(entities.begin(), entities.end(), this->playerShip), entities.end());
	entities.shrink_to_fit();
	this->playerShip = playerShip;
	playerIsDead = false;
	entities.push_back(playerShip);
}
