#include "player-ship.hpp"
#include "input.hpp"
#include "othermath.h"
#include "resources.hpp"
#include "log.hpp"
#include "level.hpp"
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

PlayerShip::PlayerShip(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level) 
: Entity(x, y, w, h, texture, level, 25),
  gun(this, Gun::Type::BASIC_GUN),
  specialGun(this, Gun::Type::BIG_GUN) {
    type = Entity::Type::PLAYER_SHIP;
}

PlayerShip::PlayerShip(sf::Vector2f position, sf::Vector2u size, sf::Texture* texture, Level* level) 
: Entity(position, size, texture, level, 25),
  gun(this, Gun::Type::BASIC_GUN),
  specialGun(this, Gun::Type::BIG_GUN) {
      type = Entity::Type::PLAYER_SHIP;
}

PlayerShip::~PlayerShip() {

}

void PlayerShip::update(sf::Time frameTime) {
    if(teleportTimer.getElapsedTime().asMilliseconds() > (int)BLINK_DELAY) {
        canBlink = true;
    }

    handleUserInput();
    sf::Vector2f mousePosition(Input::mousePosition.x + level->getView().getCenter().x - level->getView().getSize().x / 2, Input::mousePosition.y + level->getView().getCenter().y - level->getView().getSize().y / 2);
    face(mousePosition);
    // slow down ship
    if(!up && !down && !left && !right) {
        velocity *= FRICTION;
    }
    Entity::update(frameTime);
    limitVelocity(MAX_SPEED);
}

void PlayerShip::handleUserInput() {
    
    if(up = Input::checkKey(sf::Keyboard::W)) {
        accelerate(sf::Vector2f(0, -(float)ACCELERATION));
    }
    if(left = Input::checkKey(sf::Keyboard::A)) {
        accelerate(sf::Vector2f(-(float)ACCELERATION, 0));
    }
    if(down = Input::checkKey(sf::Keyboard::S)) {
        accelerate(sf::Vector2f(0, (float)ACCELERATION));
    }
    if(right = Input::checkKey(sf::Keyboard::D)) {
        accelerate(sf::Vector2f((float)ACCELERATION,0));
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

void PlayerShip::teleport(float angle) {
    if(canBlink) {
        sf::Vector2f nextPosition;
        nextPosition.x += BLINK_DISTANCE * cosf(degreesToRadians(angle - 90));
        nextPosition.y += BLINK_DISTANCE * sinf(degreesToRadians(angle - 90));
        move(nextPosition);
        canBlink = false;
        teleportTimer.restart();
    }
    
}

void PlayerShip::firePrimary() {
    if(shootTimer.getElapsedTime().asMilliseconds() > (int)SHOOT_DELAY){
        sf::Vector2f mousePosition(Input::mousePosition.x + level->getView().getCenter().x - level->getView().getSize().x / 2, Input::mousePosition.y + level->getView().getCenter().y - level->getView().getSize().y / 2);
        gun.shoot(mousePosition);
        shootTimer.restart();
    }
}

void PlayerShip::fireSpecial() {
    if(specialShootTimer.getElapsedTime().asMilliseconds() > (int)SPECIAL_SHOOT_DELAY) {
        sf::Vector2f mousePosition(Input::mousePosition.x + level->getView().getCenter().x - level->getView().getSize().x / 2, Input::mousePosition.y + level->getView().getCenter().y - level->getView().getSize().y / 2);
        specialGun.shoot(mousePosition);
        specialShootTimer.restart();
    }
}

void PlayerShip::giveSpecialAmmo(unsigned int amount) {

}

void PlayerShip::giveSpecialWeapon() {

}

Gun* PlayerShip::getPrimaryWeapon(){
    return &this->gun;
}

Gun* PlayerShip::getSecondaryWeapon(){
    return &this->specialGun;
}