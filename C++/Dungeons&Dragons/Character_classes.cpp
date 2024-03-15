#include "Character_classes.h"
#include "File_Manager.h"

Character_classes* Character_classes::get_instance_pointer()
{
	if (Character_classes::instance == nullptr)
		Character_classes::instance = new Character_classes;
	return Character_classes::instance;
}

void Character_classes::destroy_instance()
{
	if (Character_classes::instance)
		delete Character_classes::instance;
	Character_classes::instance = nullptr;
}

Character_classes& Character_classes::get_instance()
{
	return *get_instance_pointer();
}

void Character_classes::add_class(const char* filename)
{
	//adaug pe baza filename, o pereche de nume clasa si abilitati asociate
	m_classes.emplace_back(std::make_pair
		<std::string, std::vector<Abilitate*>>
		(std::string(filename).substr(std::string(filename).
			find_last_of('/') + 1).substr(0, std::string(filename).
				find_last_of('.') - std::string(filename).find_last_of('/') - 1),
			File_Manager::get_instance().citire_abilitati(filename)));
}

std::vector<Abilitate*> Character_classes::get_abilitati(std::string name)
{
	for (auto& iterator : m_classes)
		if (iterator.first == name)
			return iterator.second;
	std::vector<Abilitate*> exiter;
	return exiter;
}

Character_classes::Character_classes()
{
	add_class("character_class/FIGHTER.txt");
	add_class("character_class/SORCERER.txt");
	add_class("character_class/WIZARD.txt");
}

Character_classes::~Character_classes()
{
	for (auto& iterator : m_classes)
		for (auto& ability_iterator : iterator.second)
			delete ability_iterator;
}

std::ostream& operator<<(std::ostream& out, const Character_classes& chr)
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