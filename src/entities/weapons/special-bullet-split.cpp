#include "stdpch.hpp"

#include "special-bullet-split.hpp"
#include "math-util.hpp"
#include "entity.hpp"
#include "player-ship.hpp"
//#include <cmath>

SpecialBulletSplit::SpecialBulletSplit(sf::Vector2f position, sf::Vector2f targetPosition, Entity* owner, Level* level) :
Bullet(position, targetPosition, owner, sf::Vector2u(10,10), 500, 1, level, sf::milliseconds(100)){

}

SpecialBulletSplit::~SpecialBulletSplit(){

}

void SpecialBulletSplit::update(sf::Time frameTime){
	if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds() || getPosition() == targetPosition){
		destroy();
	}
	Entity::update(frameTime);
}
