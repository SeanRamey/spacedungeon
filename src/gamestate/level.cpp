#include "stdpch.hpp"
#include "level.hpp"
#include "resources.hpp"
#include "log.hpp"
#include "game.hpp"
#include "collision-tests.hpp"

///////////////////////////
Level::Level(Game* game, std::string levelDataFileName, std::string entityDataFileName, std::string wallImagesFileName, std::string floorImagesFileName, unsigned int tileSize) :
GameState(game),
healthText(sf::Vector2f(0, 0), Resources::getFont(Resources::FontID::VOID), ""),
healthBar(sf::Vector2f(0, 0), nullptr),
gameOver(sf::Vector2f(0, 0), Resources::getFont(Resources::FontID::VOID), "Game Over"),
tileSize(tileSize),
floorImagesFileName(floorImagesFileName),
wallImagesFileName(wallImagesFileName),
levelDataFileName(levelDataFileName),
entityDataFileName(entityDataFileName) {
	this->playerShip = new PlayerShip(50, 50, 32, 32, this);
	entities.push_back(this->playerShip);
	healthBar.setTexture(Resources::getTexture(Resources::TextureID::HEALTH_BAR));
}

///////////////////////////
Level::~Level(){
	for(Entity* entity : entities) {
		delete entity;
	}
}

///////////////////////////
// TODO implement checkWon function
bool Level::checkWon(){
	return false;
}

///////////////////////////
bool Level::checkLose(){
	// CLANG COMPILER BUG
	// if(playerIsDead) {
	//     return true;
	// }
	return playerIsDead;
}

///////////////////////////
PlayerShip* Level::getPlayer(){
	return this->playerShip;
}

///////////////////////////
void Level::draw(sf::RenderWindow& window){
	//window.draw(floorSprite);
	//window.draw(shadowSprite);
	window.draw(map);
	for(unsigned int i = 0; i < entities.size(); ++i) {
		if(!(entities.at(i) == playerShip && playerIsDead)){
			window.draw(*entities.at(i));
		}
	}
	//window.draw(wallSprite);
	if(!playerIsDead){
		window.draw(healthBar);
		window.draw(healthText);
	} else {
		window.draw(gameOver);
	}

}

///////////////////////////
void Level::update(sf::Time frameTime){
	view.setSize(sf::Vector2f(Resources::window->getSize().x, Resources::window->getSize().y));
	if(!checkLose()){
		view.setCenter(playerShip->getPosition().x, playerShip->getPosition().y);
	}
	Resources::window->setView(view);

	// Draw healthbar or gameover
	if(!checkLose()){
		float xscale = playerShip->getHitpoints().getAmount() / 100.f; // God, wtf?? No idea why this has to be divided by 100. Should just use getAsPercent()
		healthBar.setPosition(sf::Vector2f(view.getCenter().x, view.getCenter().y - view.getSize().y / 2 + 16 * 1.2));
		healthBar.updateSize(sf::Vector2f(xscale, 1));
		healthBar.update();
		healthText.setPosition(healthBar.getPosition()); // sets position of text to center of health bar
		healthText.setText(std::to_string(playerShip->getHitpoints().getAmount()));
		healthText.update();
	} else {
		gameOver.setPosition(view.getCenter());
		// exit level
		game->popState();
	}

	removeDestroyedEntities();

	for(unsigned int i = 0; i < entities.size(); ++i) {
		if(!(entities.at(i) == playerShip && playerIsDead)){
			entities.at(i)->update(frameTime);
		}
	}

	processCollisions();
}

///////////////////////////
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

///////////////////////////
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

///////////////////////////
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
			PlayerShip* player = (PlayerShip*)getMatchingEntity(pair, Entity::Type::PLAYER_SHIP);
			AlienShip* alien = (AlienShip*)getMatchingEntity(pair, Entity::Type::ALIEN_SHIP);
			player->damage(1);
			alien->destroy();
			Resources::playSound(Resources::SoundID::SND_HIT);
		}

		if(typeMatches(pair, Entity::Type::ALIEN_SHIP, Entity::Type::BULLET)) {
			Bullet* bullet = (Bullet*)getMatchingEntity(pair, Entity::Type::BULLET);
			AlienShip* alien = (AlienShip*)getMatchingEntity(pair, Entity::Type::ALIEN_SHIP);
			if(!bullet->isDestroyed()) {
				alien->damage(20);
				bullet->destroy();
				if(alien->isDestroyed()) {
					Resources::playSound(Resources::SoundID::SND_ENEMY_EXPLODE);
				} else {
					Resources::playSound(Resources::SoundID::SND_HIT);
				}
			}
		}
	}
}

///////////////////////////
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

///////////////////////////
void Level::addEntity(Entity* entity) {
	if(entity == nullptr) {
		return; // not valid pointer
	}
	entities.push_back(entity);
}

///////////////////////////
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

///////////////////////////
void Level::loadMap() {
	map.load(levelDataFileName, wallImagesFileName, floorImagesFileName, tileSize, tileSize);
}

///////////////////////////
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
				entity = new AlienShip(entityPosition.x, entityPosition.y, 32, 32, this);
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

///////////////////////////
void Level::init() {
	playerIsDead = false;
	loadMap();
	loadEntites(entityDataFileName);
}

///////////////////////////
void Level::clear(){
	// memory management
	for(Entity* entity : entities){
		if(entity != playerShip){
			delete entity;
		}
	}
	entities.clear();
}

///////////////////////////
void Level::setPlayer(PlayerShip* playerShip){
	entities.erase(std::remove(entities.begin(), entities.end(), this->playerShip), entities.end());
	entities.shrink_to_fit();
	this->playerShip = playerShip;
	playerIsDead = false;
	entities.push_back(playerShip);
}
