#include "stdpch.hpp"

#include "player-ship.hpp"
#include "input.hpp"
#include "math-util.hpp"
#include "resources.hpp"
#include "log.hpp"
#include "level.hpp"
#include "object-factories.hpp"

using namespace std;

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
	setAnimation(AnimationFactory::createAnimation(AnimationFactory::AnimationType::PLAYER_IDLE));
}

///////////////////////////
void PlayerShip::update(sf::Time frameTime) {
	if(teleportTimer.getElapsedTime().asMilliseconds() > (int)EntityData::PlayerShip::BLINK_DELAY) {
		canBlink = true;
	}

	handleUserInput();
	sf::Vector2f mousePosition(Input::mousePosition.x + level->getView().getCenter().x - level->getView().getSize().x / 2, Input::mousePosition.y + level->getView().getCenter().y - level->getView().getSize().y / 2);
	face(mousePosition);
	//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
	// slow down ship
	if(!up && !down && !left && !right) {
		velocity *= EntityData::PlayerShip::FRICTION;
	}
	Entity::update(frameTime);
	limitVelocity(EntityData::PlayerShip::MAX_SPEED);
}

///////////////////////////
void PlayerShip::handleUserInput() {

	if(up = Input::checkKey(sf::Keyboard::W)) {
		accelerate(sf::Vector2f(0, -(float)EntityData::PlayerShip::ACCELERATION));
	}
	if(left = Input::checkKey(sf::Keyboard::A)) {
		accelerate(sf::Vector2f(-(float)EntityData::PlayerShip::ACCELERATION, 0));
	}
	if(down = Input::checkKey(sf::Keyboard::S)) {
		accelerate(sf::Vector2f(0, (float)EntityData::PlayerShip::ACCELERATION));
	}
	if(right = Input::checkKey(sf::Keyboard::D)) {
		accelerate(sf::Vector2f((float)EntityData::PlayerShip::ACCELERATION,0));
	}
	if(Input::checkKey(sf::Keyboard::Space)) {
	   teleport(getRotation());
	}
	if(Input::checkMouse(sf::Mouse::Left)){
		firePrimary();
	}
	if(Input::checkMouse(sf::Mouse::Right)){
		fireSpecial();
	}
}

///////////////////////////
void PlayerShip::teleport(float angle) {
	if(canBlink) {
		sf::Vector2f nextPosition;
		nextPosition.x += EntityData::PlayerShip::BLINK_DISTANCE * cosf(degreesToRadians(angle - 90));
		nextPosition.y += EntityData::PlayerShip::BLINK_DISTANCE * sinf(degreesToRadians(angle - 90));
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
