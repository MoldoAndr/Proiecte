#include "Portals.h"
#include "Room.h"
#include <Windows.h>
#include <iomanip>
#include "Scenariu.h"

void Portals::set_next_room(Room* next_room)
{
	m_next_room = next_room;
}

void Portals::interract()
{
	Sleep(1000);
	std::cout << std::left << std::setw(10)
		<< "IN URMA INTERACTIUNII CU "
		<< m_name
		<< " AI FOST MUTAT IN " << m_next_room->name();
	Sleep(2000);
	system("cls");
	Scenariu::get_instance().set_current_room(m_next_room->name());
}

void Portals::print() const
{
	std::cout << *this;
}

std::ostream& operator<<(std::ostream& out, const Portals& portal)
{
	portal.Interractive_Objects::print();
	out << ' ' << portal.m_next_room->name();
	return out;
}