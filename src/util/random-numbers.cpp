
#include "random-numbers.hpp"

#include <time.h>
#include <stdlib.h>

    void Util::SeedRandomNumbers()
    {
        srand(time(0));
    }

    unsigned int Util::GetRandomNumber(unsigned int min, unsigned int max)
    {
        return (rand() % max) + min;
    }