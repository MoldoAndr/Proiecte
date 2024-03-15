#include "Room.h"
#include "File_Manager.h"
#include <string>

#pragma region creare_camera

bool			Room::add_enemy()
{
	bool exists{ true };
	std::string file_name = "ROOMS/";
	file_name += "ROOM_" + std::to_string(m_room_number) + "/enemy_"
		+ std::to_string(m_enemies.size() + 1) + ".txt";
	if (exists)
		m_enemies.push_back(File_Manager::
			get_instance().read_enemy(file_name,exists));
	return exists;
}

bool			Room::add_object()
{
	bool exists{ true };
	std::string file_name = "ROOMS/";
	file_name += "ROOM_" + std::to_string(m_room_number) + "/object_"
		+ std::to_string(m_objects.size() + 1) + ".txt";
	if (exists)
		m_objects.push_back(File_Manager::get_instance().read_object(file_name,exists));
	return exists;
}

void			Room::add_enemies()
{
	while (add_enemy());
	m_enemies.pop_back();
}

void			Room::add_objects()
{
	while (add_object());
	m_objects.pop_back();
}

Enemy*			Room::get_enemy(std::string name)
{
	for (auto& enemy : m_enemies)
		if (enemy->get_name() == name)
			return enemy;
	return nullptr;
}

void			Room::delete_object(IInterractive_Objects* object)
{
	auto it = std::find(m_objects.begin(), m_objects.end(), object);
	if( it != m_objects.end())
	m_objects.erase(it);
}

void			Room::delete_enemy(Enemy* enemy)
{
	auto it = std::find(m_enemies.begin(), m_enemies.end(), enemy);
	m_enemies.erase(it);
}

std::ostream&	operator<<(std::ostream& out, const Room& room)
{
	out << room.m_name << '\n';
	if (room.m_objects.size())
	{
		out << "\nOBIECTE CU CARE POTI INTERACTIONA: \n\n";
		for (auto& obiect : room.m_objects)
		{
			out << '\t';
			obiect->print();
			out << '\n';
		}
	}

	if (room.m_enemies.size())
	{
		out << "\n\nINAMICI CU CARE TE POTI LUPTA: \n";
		for (auto& enemy : room.m_enemies)
			out << *enemy;
	}
	return out;
}

IInterractive_Objects* 
				Room::get_object(std::string name)
{
	for (auto& object : m_objects)
		if (object->get_name() == name)
			return object;
	return nullptr;
}
	
Room::~Room()
{
	for (auto& enemy : m_enemies)
		delete enemy;
	for (auto& object : m_objects)
		delete object;
}

#pragma endregion