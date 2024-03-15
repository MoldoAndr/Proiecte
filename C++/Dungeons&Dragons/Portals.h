#ifndef PORTALS_H
#define PORTALS_H

#include "Interractive_Objects.h"

class Room;

class Portals : public Interractive_Objects
{
public:
	Portals(Room* next_room = nullptr) :
		m_next_room{ next_room } {}
	bool	get_next_room() override { return true; }
	void	set_next_room(Room*) override final;
	void	interract() override final;
	void	print() const override final;
	friend	std::ostream& operator<<(std::ostream&, const Portals&);
private:
	Room*	m_next_room{};
};

#endif