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
	if(hp != hpMax && amount + hp <= hpMax) {
		hp += amount;
	}
}

///////////////////////////
void Hitpoints::deplete(unsigned int amount) {
	if(hp != 0 && hp - amount >= 0) {
		hp -= amount;
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
unsigned int Hitpoints::getAmount() {
	return hp;
}

///////////////////////////
float Hitpoints::getAsPercent() {
	return hp / hpMax;
}

///////////////////////////
unsigned int Hitpoints::getMaxAmount() {
	return hpMax;
}
