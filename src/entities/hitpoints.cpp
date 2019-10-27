#include "stdpch.hpp"
#include "hitpoints.hpp"

///////////////////////////
Hitpoints::Hitpoints(unsigned int maxAmount, unsigned int startingAmount)
: hpMax(maxAmount)
, hp(startingAmount) {

}

///////////////////////////
Hitpoints::Hitpoints() {

}

///////////////////////////
Hitpoints::~Hitpoints() {

}

///////////////////////////
void Hitpoints::replenish(unsigned int amount) {
	if(amount + hp <= hpMax) {
		hp += amount;
	} else {
		hp = hpMax;
	}
}

///////////////////////////
void Hitpoints::deplete(unsigned int amount) {
	if(amount - hp >= 0) {
		hp -= amount;
	} else {
		hp = 0;
	}
}

///////////////////////////
void Hitpoints::set(unsigned int amount) {
	if(amount <= hpMax) {
		hp = amount;
	}
}

///////////////////////////
void Hitpoints::setMax(unsigned int amount) {
	hpMax = amount;
}

///////////////////////////
unsigned int Hitpoints::get() {
	return hp;
}

///////////////////////////
unsigned int Hitpoints::max() {
	return hpMax;
}
