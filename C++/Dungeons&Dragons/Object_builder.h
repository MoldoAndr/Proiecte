#ifndef OBJECT_BUILDER_H
#define OBJECT_BUILDER_H
#include "Interractive_Objects.h"

class Room;
template<class T> 
	class Object_builder
{

public:
	Object_builder() : obj{ new T } {}
	Object_builder& set_name(std::string);
	Object_builder& set_action_name(std::string);
	Object_builder& set_diff(short int);
	Object_builder& set_diff_type(std::string);
	Object_builder& set_next_room(Room*);
	T* build();
private:
	T* obj{ nullptr };
};

#include "Object_builder.cpp"

#endif