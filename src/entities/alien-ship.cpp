#include "stdpch.hpp"

#include "alien-ship.hpp"
#include "random-numbers.hpp"
#include "object-factories.hpp"
#include "entity-data.hpp"
//#include <iostream>
//#include <algorithm>

AlienShip::AlienShip(sf::Vector2f position, sf::Vector2u size, Level* level)
: Entity(position, size, level) {
	init();
}

AlienShip::AlienShip(float x, float y, unsigned int w, unsigned int h, Level* level)
: Entity(x, y, w, h, level) {
	init();
}

AlienShip::~AlienShip() {

}

void AlienShip::init() {
	type = Entity::Type::ALIEN_SHIP;
	setAnimation(AnimationFactory::createAnimation(AnimationFactory::AnimationType::ALIEN_SHIP_IDLE));
}

void AlienShip::update(sf::Time frameTime) {
	updateAI();
	Entity::update(frameTime);
}

void AlienShip::updateAI() {

	switch(state) {
		case MOVING:
		movingState();
		break;

		case FIRING:
		firingState();
		break;

		default:
		movingState();
	}
}

void AlienShip::movingState() {
	if(changeMovementTimer.getElapsedTime().asMilliseconds() >= EntityData::AlienShip::CHANGE_MOVEMENT_DELAY) {
		switch(Util::GetRandomNumber(0,3)) {
			case 0:
			// up
			setVelocity(sf::Vector2f(0,-30));
			break;

			case 1:
			// right
			setVelocity(sf::Vector2f(30,0));
			break;

			case 2:
			// down
			setVelocity(sf::Vector2f(0,30));
			break;

			case 3:
			// left
			setVelocity(sf::Vector2f(-30,0));
			break;

			default:
			break;
		}

		changeMovementTimer.restart();
		state = FIRING;
	}
}

void AlienShip::firingState() {
	fire();
	state = MOVING;
}

void AlienShip::fire() {

}
