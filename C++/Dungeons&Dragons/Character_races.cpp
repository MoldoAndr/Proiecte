#include "Character_races.h"
#include "File_Manager.h"

Character_races* Character_races::get_instance_pointer()
{
	if (Character_races::instance == nullptr)
		Character_races::instance = new Character_races;
	return Character_races::instance;
}

void Character_races::destroy_instance()
{
	if (Character_races::instance)
		delete Character_races::instance;
	Character_races::instance = nullptr;
}

Character_races& Character_races::get_instance()
{
	return *get_instance_pointer();
}

void Character_races::add_class(const char* filename)
{
	//adaug pe baza filename, o pereche de nume clasa si abilitati asociate
	m_classes.emplace_back(std::make_pair
		<std::string, std::vector<Abilitate*>>
		(std::string(filename).substr(std::string(filename).
			find_last_of('/') + 1).substr(0, std::string(filename).
				find_last_of('.') - std::string(filename).find_last_of('/') - 1),
			File_Manager::get_instance().citire_abilitati(filename)));
}

std::vector<Abilitate*> Character_races::get_abilitati(std::string name)
{
	for (auto& iterator : m_classes)
		if (iterator.first == name)
			return iterator.second;
	std::vector<Abilitate*> exiter;
	return exiter;
}

Character_races::Character_races()
{
	add_class("character_race/GOBLIN.txt");
	add_class("character_race/ELF.txt");
	add_class("character_race/HUMAN.txt");
}

Character_races::~Character_races()
{
	for (auto& iterator : m_classes)
		for (auto& ability_iterator : iterator.second)
			delete ability_iterator;
}

std::ostream& operator<<(std::ostream& out, const Character_races& chr)
{
	for (auto& iterator : chr.m_classes)
	{
		std::cout << iterator.first << '\n';
		for (auto& ability_iterator : iterator.second)
			std::cout << *ability_iterator;
		std::cout << '\n';
	}
	return out;
}