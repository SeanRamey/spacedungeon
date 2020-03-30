#include "damageable.hpp"


///////////////////////////
Damageable::Damageable(unsigned int maxHitpoints, unsigned int initialHitpoints)
: hitpoints(maxHitpoints, initialHitpoints) {

}

///////////////////////////
Damageable::~Damageable() {

}

///////////////////////////
void Damageable::damage(unsigned int amount) {
	hitpoints.deplete(amount);
}

///////////////////////////
void Damageable::heal(unsigned int amount) {
	hitpoints.replenish(amount);
}

///////////////////////////
void Damageable::destroy() {
	hitpoints.deplete(hitpoints.getAmount()); // deplete all hitpoints
}

///////////////////////////
void Damageable::restore() {
	hitpoints.replenish(hitpoints.getMaxAmount()); // replenish the max amount
}

///////////////////////////
bool Damageable::isDestroyed() {
	return (hitpoints.getAmount() == 0) ? true : false;
}

///////////////////////////
Hitpoints Damageable::getHitpoints() {
	return hitpoints;
}
