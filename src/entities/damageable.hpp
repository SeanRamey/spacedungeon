#ifndef DAMAGEABLE_HPP
#define DAMAGEABLE_HPP

#include "hitpoints.hpp"

class Damageable {
	public:
	Damageable(unsigned int maxHitpoints, unsigned int initialHitpoints);
	~Damageable();

	virtual void damage(unsigned int amount);
	virtual void heal(unsigned int amount);
	virtual void destroy();
	virtual void restore();
	virtual bool isDestroyed();
	Hitpoints getHitpoints();

	private:
	Hitpoints hitpoints;
};

#endif
