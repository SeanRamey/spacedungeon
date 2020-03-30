
#include "random-numbers.hpp"

#include <ctime>
#include <cstdlib>

	void Util::SeedRandomNumbers()
	{
		std::srand(std::time(0));
	}

	unsigned int Util::GetRandomNumber(unsigned int min, unsigned int max)
	{
		return (std::rand() % max) + min;
	}
