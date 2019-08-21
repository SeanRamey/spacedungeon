#ifndef ENTITY_DATA_HPP
#define ENTITY_DATA_HPP

namespace EntityData {
	namespace DefaultEntity {
		constexpr unsigned int hitpoints = 100;
	}

	namespace PlayerShip {
		constexpr unsigned int hitpoints = 50;
	}

	namespace AlienShip {
		constexpr unsigned int hitpoints = 10;
	}

	namespace Bullet {
		constexpr unsigned int hitpoints = 1;
	}
}

#endif
