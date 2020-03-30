#include "stdpch.hpp"
#include "basic-bullet.hpp"
//#include <iostream>
#include "input.hpp"
#include "math-util.hpp"
//#include <cmath>
#include "player-ship.hpp"
#include "random-numbers.hpp"
#include "resources.hpp"
#include "object-factories.hpp"

BasicBullet::BasicBullet(sf::Vector2f position, sf::Vector2f targetPosition, Entity* owner, Level* level):
Bullet(position, targetPosition, owner, sf::Vector2u(12,16), 200, 1, level){
	setAnimation(AnimationFactory::createAnimation(AnimationFactory::AnimationType::BASIC_BULLET));
	offset = Util::GetRandomNumber(0, 8) - 4;
	accelerate(sf::Vector2f(initialSpeed * cosf(degreesToRadians(getRotation() - 90 + offset)), initialSpeed * sinf(degreesToRadians(getRotation() - 90 + offset))));
}

BasicBullet::~BasicBullet(){

}

void BasicBullet::update(sf::Time frameTime) {
	Bullet::update(frameTime);
}
