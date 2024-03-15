#ifndef D20_H
#define D20_H

#include <iostream>
#include <random>
#include <ctime>

class D20 {

public:    
    static D20* get_instance_pointer()
    {
        if (D20::instance == nullptr)
            D20::instance = new D20;
        return D20::instance;
    }

    static D20& get_instance() 
    {
        return *get_instance_pointer();
    }

    static void destroy_instance()
    {
        if (D20::instance)
            delete D20::instance;
        D20::instance = nullptr;
    }

    int         roll() const {
        return (rand() % 20) + 1;
    }

private:

    inline static D20*  instance{ nullptr };
    D20(const D20&)     = delete;
    D20(D20&&)          = delete;
    D20() 
    {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

};
#endif