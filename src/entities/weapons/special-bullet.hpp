#ifndef SPECIAL_BULLET_HPP
#define SPECIAL_BULLET_HPP
#include "bullet.hpp"
#include "entity.hpp"
#include "tile.hpp"
#include "special-bullet-split.hpp"

class SpecialBullet : public Bullet {
	public:
		SpecialBullet(sf::Vector2f position, sf::Vector2f targetPosition, Entity* owner, Level* level);
		~SpecialBullet();
		void update(sf::Time frameTime);
		void destroy();

	private:
		const unsigned int SPEED = 500;
		const sf::Vector2u SIZE = sf::Vector2u(32,32);
		const unsigned int DAMAGE = 2;

		unsigned int numSplits;
		std::vector<SpecialBulletSplit> splitoffs;
};

#endif
