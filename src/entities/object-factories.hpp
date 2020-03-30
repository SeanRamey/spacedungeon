#ifndef OBJECT_FACTORIES_HPP
#define OBJECT_FACTORIES_HPP

#include "animation.hpp"

namespace AnimationFactory {

	enum AnimationType {
		NONE,
		PLAYER_IDLE,
		ALIEN_SHIP_IDLE,
		BASIC_BULLET,
		SPECIAL_BULLET,
		NUM_ANIMATION_TYPES
	};

	Animation createAnimation(AnimationType type);
}

#endif
