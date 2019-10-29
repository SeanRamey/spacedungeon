#ifndef ENTITY_DATA_HPP
#define ENTITY_DATA_HPP

#include "allpch.hpp"
#include "resources.hpp"

namespace EntityData {

	struct AnimationData {
		Resources::TextureID textureID;
		unsigned int cellsPerSecond;
		sf::Vector2u cellSize;
		bool repeating = false;
	};

	namespace DefaultEntity {
		constexpr unsigned int HITPOINTS = 100;
	}

	namespace PlayerShip {
		constexpr unsigned int HITPOINTS = 50;
		constexpr unsigned int MAX_HITPOINTS = 50;
		constexpr unsigned int MAX_SPEED = 1000; // MAX_SPEED MUST BE LARGER THAN ACCELERATION
		constexpr unsigned int ACCELERATION = 100;
		constexpr unsigned int BLINK_DISTANCE = 200;
		constexpr unsigned int MAX_SHIELD_LEVEL = 5;
		constexpr unsigned int MAX_POWER_LEVEL = 10;
		constexpr float FRICTION = 0.95;
		// times are in milliseconds
		constexpr unsigned int BLINK_DELAY = 750;
		constexpr unsigned int SHOOT_DELAY = 200;
		constexpr unsigned int SPECIAL_SHOOT_DELAY = 1000;
	}

	namespace AlienShip {
		constexpr unsigned int HITPOINTS = 10;
		constexpr unsigned int MAX_SPEED = 100;
		// times are in milliseconds
		constexpr unsigned int CHANGE_MOVEMENT_DELAY = 1000;
		constexpr unsigned int FIRING_DELAY = 1000;
	}

	namespace Bullet {
		constexpr unsigned int HITPOINTS = 1;
	}
}

#endif
