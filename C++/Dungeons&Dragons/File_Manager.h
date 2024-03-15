#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include "Abilitate.h"
#include "IInterractive_Objects.h"
#include "Enemy.h"

class File_Manager
{
public:
	static File_Manager&				get_instance();
	static void							delete_instance();
	std::vector<Abilitate*>				citire_abilitati(const char*);
	Enemy*								read_enemy(std::string,bool&);
	IInterractive_Objects*				read_object(std::string,bool&);
	Room*								create_room(bool&,size_t);
private:
	inline static File_Manager*			instance{ nullptr };
	File_Manager()						= default;
	File_Manager(const File_Manager&)	= delete;
	File_Manager(File_Manager&&)		= delete;
};

#endif