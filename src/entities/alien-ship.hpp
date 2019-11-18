#ifndef ALIEN_SHIP_HPP
#define ALIEN_SHIP_HPP

#include "sfmlpch.hpp"
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
#include "entity.hpp"

class AlienShip : public Entity
{
	public:
		AlienShip(sf::Vector2f position, sf::Vector2u size, Level* level);
		AlienShip(float x, float y, unsigned int w, unsigned int h, Level* level);
		~AlienShip();

		void update(sf::Time frameTime);
		void fire();

	private:

		void init();
		void updateAI();
		void movingState();
		void firingState();
		sf::Sprite sprite;
		sf::Clock changeMovementTimer;
		sf::Clock firingTimer;
		enum State
		{
			FIRING,
			MOVING
		};
		State state = MOVING;
		const sf::Time CHANGE_MOVEMENT_DELAY = sf::seconds(1);
		const sf::Time FIRING_DELAY = sf::seconds(1);
		const unsigned int MAX_SPEED = 100; // pixels per second

};

#endif
