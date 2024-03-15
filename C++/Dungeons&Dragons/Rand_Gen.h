#ifndef RAND_GEN_H
#define RAND_GEN_H

#include <iostream>
#include <random>
#include <tuple>

class Rand_Gen {

public:
    static Rand_Gen& getInstance();
    static void destroy_instance();
    
    void setSum(short s);
    short getRandomValue(short max);
    std::tuple<short, short, short> generateValues();

private:
    std::random_device rd{};
    std::mt19937 gen{};
    std::uniform_int_distribution<short> distribution{};
    short int sum{};

    inline static Rand_Gen* instance{ nullptr };

    Rand_Gen() : gen(rd()) {}
    Rand_Gen(const Rand_Gen&) = delete;
    Rand_Gen(Rand_Gen&&) = delete;

};
#endif  