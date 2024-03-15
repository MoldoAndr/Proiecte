#include "Rand_Gen.h"

Rand_Gen&       Rand_Gen::getInstance() {
    if (Rand_Gen::instance == nullptr)
        Rand_Gen::instance = new Rand_Gen;
    return *Rand_Gen::instance;
}

void            Rand_Gen::destroy_instance()
{
    if (Rand_Gen::instance)
        delete Rand_Gen::instance;
    Rand_Gen::instance = nullptr;
}

void            Rand_Gen::setSum(short s) 
{
    sum = s;
    distribution = std::uniform_int_distribution<short>(1, sum);
}

short           Rand_Gen::getRandomValue(short max) {
    std::uniform_int_distribution<short> newDistribution(1, max);
    return newDistribution(gen);
}

std::tuple<short int, short int, short int> 
                Rand_Gen::generateValues() 
{
    short value1 = getRandomValue(sum / 2);
    short value2 = getRandomValue(sum - value1);
    short value3 = sum - value1 - value2;
    return std::make_tuple(value1, value2, value3);
}