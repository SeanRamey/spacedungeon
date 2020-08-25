#include "stdpch.hpp"

#include "player-ship.hpp"
#include "input.hpp"
#include "math-util.hpp"
#include "resources.hpp"
#include "log.hpp"
#include "level.hpp"
#include "object-factories.hpp"
#include "entity-command.hpp"

///////////////////////////
PlayerShip::PlayerShip(float x, float y, unsigned int w, unsigned int h, Level* level)
: Entity(x, y, w, h, level)
, gun(this, Gun::Type::BASIC_GUN)
, specialGun(this, Gun::Type::BIG_GUN) {
	init();
}

///////////////////////////
PlayerShip::PlayerShip(sf::Vector2f position, sf::Vector2u size, Level* level)
: Entity(position, size, level)
, gun(this, Gun::Type::BASIC_GUN)
, specialGun(this, Gun::Type::BIG_GUN) {
	init();
}

///////////////////////////
PlayerShip::~PlayerShip() {

}

///////////////////////////
void PlayerShip::init() {
	type = Entity::Type::PLAYER_SHIP;
	hitpoints.set(EntityData::PlayerShip::HITPOINTS);
	hitpoints.setMax(EntityData::PlayerShip::MAX_HITPOINTS);
	setAnimation(AnimationFactory::createAnimation(AnimationFactory::AnimationType::PLAYER_IDLE));

	std::shared_ptr<EntityCommand<PlayerShip>> moveUpCommand = std::make_shared<EntityCommand<PlayerShip>> (this, &PlayerShip::moveUp);
	addKeyboardAction(sf::Keyboard::Scancode::ScanW, std::dynamic_pointer_cast<Command>(moveUpCommand));

	std::shared_ptr<EntityCommand<PlayerShip>> moveDownCommand = std::make_shared<EntityCommand<PlayerShip>> (this, &PlayerShip::moveDown);
	addKeyboardAction(sf::Keyboard::Scancode::ScanS, std::dynamic_pointer_cast<Command>(moveDownCommand));

	std::shared_ptr<EntityCommand<PlayerShip>> moveLeftCommand = std::make_shared<EntityCommand<PlayerShip>> (this, &PlayerShip::moveLeft);
	addKeyboardAction(sf::Keyboard::Scancode::ScanA, std::dynamic_pointer_cast<Command>(moveLeftCommand));

	std::shared_ptr<EntityCommand<PlayerShip>> moveRightCommand = std::make_shared<EntityCommand<PlayerShip>> (this, &PlayerShip::moveRight);
	addKeyboardAction(sf::Keyboard::Scancode::ScanD, std::dynamic_pointer_cast<Command>(moveRightCommand));

	std::shared_ptr<EntityCommand<PlayerShip>> teleport = std::make_shared<EntityCommand<PlayerShip>> (this, &PlayerShip::teleport);
	addKeyboardAction(sf::Keyboard::Scancode::ScanSpace, std::dynamic_pointer_cast<Command>(teleport));

	std::shared_ptr<EntityCommand<PlayerShip>> fireCommand = std::make_shared<EntityCommand<PlayerShip>> (this, &PlayerShip::firePrimary);
	addMouseAction(sf::Mouse::Button::Left, std::dynamic_pointer_cast<Command>(fireCommand));

	std::shared_ptr<EntityCommand<PlayerShip>> fireSpecialCommand = std::make_shared<EntityCommand<PlayerShip>> (this, &PlayerShip::fireSpecial);
	addMouseAction(sf::Mouse::Button::Right, std::dynamic_pointer_cast<Command>(fireSpecialCommand));
}

//////////////////////////
void PlayerShip::update(sf::Time frameTime) {
	if(teleportTimer.getElapsedTime().asMilliseconds() > (int)EntityData::PlayerShip::BLINK_DELAY) {
		canBlink = true;
	}
	state = State::STILL; // always default to STILL because user input will change state to MOVING
	handleUserInput();
	//sf::Vector2f mousePosition(Input::mousePosition.x + level->getView().getCenter().x - level->getView().getSize().x / 2, Input::mousePosition.y + level->getView().getCenter().y - level->getView().getSize().y / 2);
	sf::Vector2f mousePosition(Resources::window->mapPixelToCoords(sf::Vector2i(Input::mousePosition.x, Input::mousePosition.y)));
	face(mousePosition);
	// slow down ship
	if(state == State::STILL) {
		velocity *= EntityData::PlayerShip::FRICTION;
	}
	limitVelocity(EntityData::PlayerShip::MAX_SPEED);
	Entity::update(frameTime);
}

///////////////////////////
void PlayerShip::moveUp() {
	accelerate(sf::Vector2f(0, -(float)EntityData::PlayerShip::ACCELERATION));
	state = State::MOVING;
}

///////////////////////////
void PlayerShip::moveDown() {
	accelerate(sf::Vector2f(0, (float)EntityData::PlayerShip::ACCELERATION));
	state = State::MOVING;
}

///////////////////////////
void PlayerShip::moveLeft() {
	accelerate(sf::Vector2f(-(float)EntityData::PlayerShip::ACCELERATION, 0));
	state = State::MOVING;
}

///////////////////////////
void PlayerShip::moveRight() {
	accelerate(sf::Vector2f((float)EntityData::PlayerShip::ACCELERATION, 0));
	state = State::MOVING;
}

///////////////////////////
void PlayerShip::teleport() {
	if(canBlink) {
		sf::Vector2f nextPosition;
		nextPosition.x += EntityData::PlayerShip::BLINK_DISTANCE * cosf(degreesToRadians(getRotation() - 90));
		nextPosition.y += EntityData::PlayerShip::BLINK_DISTANCE * sinf(degreesToRadians(getRotation() - 90));
		move(nextPosition);
		canBlink = false;
		teleportTimer.restart();
	}

}

///////////////////////////
void PlayerShip::firePrimary() {
	if(shootTimer.getElapsedTime().asMilliseconds() > (int)EntityData::PlayerShip::SHOOT_DELAY){
		sf::Vector2f mousePosition(Input::mousePosition.x + level->getView().getCenter().x - level->getView().getSize().x / 2, Input::mousePosition.y + level->getView().getCenter().y - level->getView().getSize().y / 2);
		gun.shoot(mousePosition);
		Resources::playSound(Resources::SoundID::SND_PLAYER_SHOOT);
		shootTimer.restart();
	}
}

///////////////////////////
void PlayerShip::fireSpecial() {
	if(specialShootTimer.getElapsedTime().asMilliseconds() > (int)EntityData::PlayerShip::SPECIAL_SHOOT_DELAY) {
		sf::Vector2f mousePosition(Input::mousePosition.x + level->getView().getCenter().x - level->getView().getSize().x / 2, Input::mousePosition.y + level->getView().getCenter().y - level->getView().getSize().y / 2);
		specialGun.shoot(mousePosition);
		Resources::playSound(Resources::SoundID::SND_PLAYER_SHOOT);
		specialShootTimer.restart();
	}
}

///////////////////////////
void PlayerShip::giveSpecialAmmo(unsigned int amount) {

}

///////////////////////////
void PlayerShip::giveSpecialWeapon() {

}

///////////////////////////
Gun* PlayerShip::getPrimaryWeapon(){
	return &this->gun;
}

///////////////////////////
Gun* PlayerShip::getSecondaryWeapon(){
	return &this->specialGun;
}
