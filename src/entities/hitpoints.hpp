#ifndef HITPOINTS_HPP
#define HITPOINTS_HPP

class Hitpoints {
	public:
	Hitpoints(unsigned int maxAmount, unsigned int startingAmount);
	Hitpoints();
	~Hitpoints();
	void replenish(unsigned int amount);
	void deplete(unsigned int amount);
	void set(unsigned int amount);
	void setMax(unsigned int amount);
	unsigned int getAmount();
	float getAsPercent();
	unsigned int getMaxAmount();

	private:
	unsigned int hpMax = 0;
	unsigned int hp = 0;
};

#endif
