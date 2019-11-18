#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP

#include "allpch.hpp"
#include "input.hpp"
#include "math-util.hpp"
#include "gun.hpp"
#include "entity.hpp"
#include "entity-data.hpp"

class PlayerShip : public Entity {
	public:
		PlayerShip(float x, float y, unsigned int w, unsigned int h, Level* level);
		PlayerShip(sf::Vector2f position, sf::Vector2u size, Level* level);
		~PlayerShip();
		void init();

		void update(sf::Time frameTime);
		void handleUserInput();
		void teleport(float angle);
		void firePrimary();
		void fireSpecial();
		void giveSpecialAmmo(unsigned int amount);
		void giveSpecialWeapon();

		Gun* getPrimaryWeapon();
		Gun* getSecondaryWeapon();

	private:
	// stats
		unsigned int shieldLevel;
		unsigned int powerLevel;

		bool up = false;
		bool down = false;
		bool right = false;
		bool left = false;

		Gun gun;
		Gun specialGun;

	// teleporting
		bool canBlink;
		sf::Clock teleportTimer;
		sf::Clock shootTimer;
		sf::Clock specialShootTimer;
};

#endif
