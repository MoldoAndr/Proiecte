#include "File_Manager.h"
#include <fstream>
#include "Exceptie_Fisier.h"
#include "Object_builder.h"
#include "Scenariu.h"
#include "Room.h"

File_Manager& File_Manager::get_instance()
{
	if (File_Manager::instance == nullptr)
		File_Manager::instance = new File_Manager;
	return *File_Manager::instance;
}

void File_Manager::delete_instance()
{
	if (File_Manager::instance)
		delete File_Manager::instance;
	File_Manager::instance = nullptr;
}

std::vector<Abilitate*> File_Manager::citire_abilitati(const char* filename)
{
	std::vector<Abilitate*> 
						return_vector;
	Abilitate*			aux_ability{ nullptr };
	std::ifstream		fin(filename, std::ios::in);
	if (!fin.is_open())
		throw Exceptie_Fisier(1);
	std::string			aux_string{};
	short int			aux_int{};
	short int			aux_diff_quant{};
	char				aux_diff{};
	Difficulty_Class	aux_diff2{};
	while (fin >> aux_string >> aux_int >> aux_diff_quant >> aux_diff)
	{
		if (aux_diff == '0')
			aux_diff2 = Difficulty_Class::intellect;
		else if (aux_diff == '1')
			aux_diff2 = Difficulty_Class::dexterity;
		else 
			aux_diff2 = Difficulty_Class::strengh;
		
		aux_ability = new Abilitate(aux_string, aux_int,aux_diff_quant, aux_diff2);
		return_vector.push_back(aux_ability);
	}
	return return_vector;
}

Enemy* File_Manager::read_enemy(std::string filename, bool& exists)
{
	std::ifstream reader(filename, std::ios::in);
	if (!reader.is_open())
	{
		exists = false;
		return nullptr;
	}
	Enemy* auxiliar = new Enemy();

	std::string nume{};
	short int varsta{};
	std::string rasa,tip,trecut;

	reader >> nume >> varsta >> rasa >> tip >> trecut;
	reader.close();
	auxiliar->set_caracter(nume);
	auxiliar->set_caracter(varsta);
	if (rasa == "HUMAN")	auxiliar->set_caracter(rasa_caracter::human);
	if (rasa == "GOBLIN")	auxiliar->set_caracter(rasa_caracter::goblin);
	if (rasa == "ELF")		auxiliar->set_caracter(rasa_caracter::elf);
	if (tip == "WIZARD")	auxiliar->set_caracter(tip_caracter::Wizard);
	if (tip == "SORCERER")	auxiliar->set_caracter(tip_caracter::Sorcerer);
	if (tip == "FIGHTER")	auxiliar->set_caracter(tip_caracter::Fighter);
	if (trecut == "HOT")	auxiliar->set_caracter(caracter_trecut::hot);
	if (trecut == "ACOLIT") auxiliar->set_caracter(caracter_trecut::acolit);
	if (trecut == "SOLDAT")	auxiliar->set_caracter(caracter_trecut::soldat);

	auxiliar->randomize_atributes();
	return auxiliar;
}

IInterractive_Objects* File_Manager::read_object(std::string filename,bool& exists )
{
	IInterractive_Objects* obiect{ nullptr };
	std::ifstream reader(filename, std::ios::in);
	if (!reader.is_open())
	{
		exists = false;
		return nullptr;
	}
	std::string	object_name,
		action_name,
		diff_name,
		room;
	short int	diff;
	reader >> object_name >> action_name >> diff >> diff_name;
	if (object_name == "door" || object_name == "portal")
	{
		reader >> room;
		Object_builder<Portals>* builder = new Object_builder<Portals>;
			obiect = builder
			->set_name(object_name)
			.set_action_name(action_name)
			.set_diff(diff)
			.set_diff_type(diff_name)
			.set_next_room(Scenariu::get_instance().get_room(room))
			.build();
		delete builder;
	}
	else
	{
		Object_builder<Interractive_Objects>* builder = new Object_builder<Interractive_Objects>;
		obiect = builder
			->set_name(object_name)
			.set_action_name(action_name)
			.set_diff(diff)
			.set_diff_type(diff_name)
			.build();
	}
	return obiect;
}

Room* File_Manager::create_room(bool& room_exists, size_t room_number)
{
	std::string file_name;
	file_name = "ROOMS/ROOM_" + std::to_string(room_number);
	std::ifstream reader(file_name + "/object_1.txt", std::ios::in);
	if (!reader.is_open())
	{
		room_exists = 0;
		return nullptr;
	}
	Room* new_room = new Room(static_cast<unsigned short int>(room_number));	
	return new_room;
}