// am folisit acest fisier .cpp ca extensie a header-ului 
// a fost exclus din procesul de compilare 
// a fost inclus la finalul header-ului
// pentru o mai buna modularizare a codului

#include "Object_builder.h"
#include "Portals.h"

template<typename T>Object_builder<T>& Object_builder<T>::set_name(std::string nume)
{
    obj->set_name(nume);
    return *this;
}

template<typename T>Object_builder<T>& Object_builder<T>::set_action_name(std::string action)
{
    obj->set_action(action);
    return *this;
}

template<typename T>Object_builder<T>& Object_builder<T>::set_diff(short int diff)
{
    obj->set_difficulty(diff);
    return *this;
}

template<typename T>Object_builder<T>& Object_builder<T>::set_diff_type(std::string type)
{
    obj->set_difficulty_type(type);
    return *this;
}

template<>Object_builder<Portals>& Object_builder<Portals>::set_next_room(Room* next_room)
{
    obj->set_next_room(next_room);
    return *this;
}

template<>Object_builder<Interractive_Objects>& Object_builder<Interractive_Objects>::set_next_room(Room* next_room)
{
    return *this;
}

template<typename T>T* Object_builder<T>::build()   
{
    return obj;
}
