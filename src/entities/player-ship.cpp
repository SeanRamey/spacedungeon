#include "player-ship.hpp"
#include "input.hpp"
#include "othermath.h"
#include "resources.hpp"
#include "log.hpp"
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

PlayerShip::PlayerShip(float x, float y, unsigned int w, unsigned int h, sf::Texture* texture, Level* level) 
: Entity(x, y, w, h, level),
  gun(this, 0U), 
  specialGun(this, 1U) {
    sprite.setTexture(*texture);
    type = Entity::types::PLAYER_SHIP;
}

PlayerShip::PlayerShip(float x, float y, unsigned int w, unsigned int h, Level* level) 
: Entity(x, y, w, h, level),
  gun(this, 0U), 
  specialGun(this, 1U) {
    setTexture(Resources::get(Resources::ID::PLAYERSHIP));

}

PlayerShip::~PlayerShip() {

}
void PlayerShip::checkCollision(Entity* entity){

}
void PlayerShip::update(sf::Time frameTime, sf::RenderWindow* window) {
    if(teleportTimer.getElapsedTime().asMilliseconds() > (int)BLINK_DELAY) {
        canBlink = true;
    }

    handleUserInput();
    face(sf::Vector2f(Input::mousePosition.x + window->getView().getCenter().x - window->getSize().x / 2, Input::mousePosition.y + window->getView().getCenter().y - window->getSize().y / 2)); // face the mouse cursor
    // slow down ship
    if(!up && !down && !left && !right) {
        velocity *= FRICTION;
    }
    applyMovement(frameTime);
    gun.update(frameTime, window); 
    specialGun.update(frameTime, window);
    collisionBox.update(position.x, position.y);
}

void PlayerShip::handleUserInput() {
    
    if(up = Input::checkKey(sf::Keyboard::W)) {
        addVelocity(sf::Vector2f(0, -(float)ACCELERATION));
    }
    if(left = Input::checkKey(sf::Keyboard::A)) {
        addVelocity(sf::Vector2f(-(float)ACCELERATION, 0));
    }
    if(down = Input::checkKey(sf::Keyboard::S)) {
        addVelocity(sf::Vector2f(0, (float)ACCELERATION));
    }
    if(right = Input::checkKey(sf::Keyboard::D)) {
        addVelocity(sf::Vector2f((float)ACCELERATION,0));
    }
    if(Input::checkKey(sf::Keyboard::Space)) {
        teleport(angle);
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
        float blinkDistance = sqrtf(pow((Input::mousePosition.x + Resources::window->getView().getCenter().x - Resources::window->getSize().x / 2) - position.x, 2) + powf((Input::mousePosition.y + Resources::window->getView().getCenter().y - Resources::window->getSize().y / 2) - position.y, 2));
        if(blinkDistance < BLINK_DISTANCE){
            // uses mouse position
            nextPosition.x += blinkDistance * cosf(degreesToRadians(angle - 90));
            nextPosition.y += blinkDistance * sinf(degreesToRadians(angle - 90));
        } else {
            // max distance 
            nextPosition.x += BLINK_DISTANCE * cosf(degreesToRadians(angle - 90));
            nextPosition.y += BLINK_DISTANCE * sinf(degreesToRadians(angle - 90));
        }
        canBlink = false;
        teleportTimer.restart();
    }
    
}

void PlayerShip::firePrimary() {
    if(shootTimer.getElapsedTime().asMilliseconds() > (int)SHOOT_DELAY){
        gun.shoot();
        shootTimer.restart();
    }
}

void PlayerShip::fireSpecial() {
    if(specialShootTimer.getElapsedTime().asMilliseconds() > (int)SPECIAL_SHOOT_DELAY) {
        specialGun.shoot();
        specialShootTimer.restart();
    }
}

void PlayerShip::damage(unsigned int amount) {

}

void PlayerShip::repair(unsigned int amount) {

}

void PlayerShip::giveSpecialAmmo(unsigned int amount) {

}

void PlayerShip::giveSpecialWeapon() {

}

void PlayerShip::draw(sf::RenderWindow* window){
    Entity::draw(window);
    gun.draw(window);
    specialGun.draw(window);
}


Gun* PlayerShip::getPrimaryWeapon(){
    return &this->gun;
}

Gun* PlayerShip::getSecondaryWeapon(){
    return &this->specialGun;
}