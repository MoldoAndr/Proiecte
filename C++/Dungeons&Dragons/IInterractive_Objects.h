#ifndef IINTERRACTIVE_OBJECT_H
#define IINTERRACTIVE_OBJECT_H

#include <iostream>

class Room;

class IInterractive_Objects
{
public:
	virtual void		set_name(std::string) = 0;
	virtual void		set_action(std::string) = 0;
	virtual bool		get_next_room() = 0;
	virtual void		set_difficulty(short int) = 0;
	virtual void		set_difficulty_type(std::string) = 0;
	virtual void		set_next_room(Room*) = 0;
	virtual int			get_mastery() = 0;
	virtual	std::string get_name() = 0;
	virtual std::string get_mastery_type() = 0;
	virtual void		interract() = 0;
	virtual void		print() const = 0;
};

#endif