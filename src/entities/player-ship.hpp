#ifndef PLAYER_SHIP_HPP
#define PLAYER_SHIP_HPP

#include "allpch.hpp"
#include "input.hpp"
#include "math-util.hpp"
#include "gun.hpp"
#include "entity.hpp"
#include "entity-data.hpp"
#include "controllable.hpp"

class PlayerShip : public Entity, public Controllable {
	public:
		PlayerShip(float x, float y, unsigned int w, unsigned int h, Level* level);
		PlayerShip(sf::Vector2f position, sf::Vector2u size, Level* level);
		~PlayerShip();
		void init();

		void update(sf::Time frameTime);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void teleport();
		void firePrimary();
		void fireSpecial();
		void giveSpecialAmmo(unsigned int amount);
		void giveSpecialWeapon();

		Gun* getPrimaryWeapon();
		Gun* getSecondaryWeapon();

	private:
		enum State {
			STILL,
			MOVING
		};
		State state = STILL;
		enum Action {
			MOVE_UP,
			MOVE_DOWN,
			MOVE_LEFT,
			MOVE_RIGHT,
			TELEPORT,
			FIRE_PRIMARY,
			FIRE_SPECIAL
		};
		unsigned int shieldLevel = 0;
		unsigned int powerLevel = 0;
		bool canBlink = true;
		Gun gun;
		Gun specialGun;
		sf::Clock teleportTimer;
		sf::Clock shootTimer;
		sf::Clock specialShootTimer;
};

#endif
