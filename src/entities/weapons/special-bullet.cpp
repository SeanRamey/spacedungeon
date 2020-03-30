#include "stdpch.hpp"

#include "special-bullet.hpp"
#include "resources.hpp"
#include "player-ship.hpp"
#include "math-util.hpp"
//#include <iostream>
#include "level.hpp"
#include "random-numbers.hpp"
#include "object-factories.hpp"

///////////////////////////
SpecialBullet::SpecialBullet(sf::Vector2f position, sf::Vector2f targetPosition, Entity* owner, Level* level) :
Bullet(position, targetPosition, owner, sf::Vector2u(32,32), 200, 2, level, sf::seconds(1)){
	numSplits = 16;
	setAnimation(AnimationFactory::createAnimation(AnimationFactory::AnimationType::SPECIAL_BULLET));
}

///////////////////////////
SpecialBullet::~SpecialBullet(){
}

///////////////////////////
void SpecialBullet::destroy(){
	Entity::destroy();
	double degreeSplit = 360 / numSplits;
	for(size_t i = 0; i < numSplits; i++){
		sf::Vector2f finalPosition;
		finalPosition.x = getPosition().x + cosf(degreesToRadians(i * (degreeSplit + Util::GetRandomNumber(-5, 5))));
		finalPosition.y = getPosition().y + sinf(degreesToRadians(i * (degreeSplit + Util::GetRandomNumber(-5, 5))));
		SpecialBulletSplit* shrapnel = new SpecialBulletSplit(getPosition(), finalPosition, owner, level);
		shrapnel->setTexture(Resources::getTexture(Resources::TextureID::SHRAPNEL));
		level->addEntity(shrapnel);
	}
}

///////////////////////////
void SpecialBullet::update(sf::Time frameTime){
	if(timeAlive.getElapsedTime().asMilliseconds() > maxTimeAlive.asMilliseconds() || getPosition() == targetPosition){
		destroy();
	}
	Entity::update(frameTime);
}
