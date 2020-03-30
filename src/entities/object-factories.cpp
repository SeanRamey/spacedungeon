#include "object-factories.hpp"
#include "resources.hpp"

///////////////////////////
Animation AnimationFactory::createAnimation(AnimationType type) {

	Animation animation;
	switch(type) {
		case AnimationType::PLAYER_IDLE:
		animation.setTexture(Resources::getTexture(Resources::TextureID::PLAYER_SHIP));
		animation.setCellSize(32,32);
		animation.setCellsPerSecond(1);
		animation.setRepeat(true);
		break;

		case AnimationType::ALIEN_SHIP_IDLE:
		animation.setTexture(Resources::getTexture(Resources::TextureID::ALIEN_SHIP));
		animation.setCellSize(32,32);
		animation.setCellsPerSecond(1);
		animation.setRepeat(true);
		break;

		case AnimationType::BASIC_BULLET:
		animation.setTexture(Resources::getTexture(Resources::TextureID::BULLET));
		animation.setCellSize(12,16);
		animation.setCellsPerSecond(10);
		animation.setRepeat(true);
		break;

		case AnimationType::SPECIAL_BULLET:
		animation.setTexture(Resources::getTexture(Resources::TextureID::SPECIALBULLET));
		animation.setCellSize(32,32);
		animation.setCellsPerSecond(15);
		animation.setRepeat(true);
		break;

		case AnimationType::NONE:
		default:
		break;
	}

	return animation;
}
