#ifndef ROOM_H
#define ROOM_H

#include "Enemy.h"
#include "Interractive_Objects.h"
#include <vector>

class Room
{
public:
	Room(unsigned short int room_number) :
		m_room_number{ room_number },
		m_name{"ROOM_" + 
		std::to_string(room_number)} {}
	~Room();
	inline size_t							get_object_number() const { return m_objects.size(); }
	inline size_t							get_enemy_number() const{ return m_enemies.size(); }
	void									add_enemies();
	void									add_objects();
	void									delete_enemy(Enemy*);
	void									delete_object(IInterractive_Objects*);
	IInterractive_Objects*					get_object(std::string);
	Enemy*									get_enemy(std::string);
	inline std::string						name() const { return m_name; }
	friend std::ostream&					operator<<(std::ostream&, const Room&);
private:
	bool									add_enemy();
	bool									add_object();
	unsigned short int						m_room_number{};
	std::string								m_name;
	std::vector<IInterractive_Objects*>		m_objects;
	std::vector<Enemy*>						m_enemies;
};

#endif