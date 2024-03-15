#include "Scenariu.h"
#include "Player_Builder.h"
#include "File_Manager.h"
#include "Exceptie_Logica.h"
#include "D20.h"
#include <Windows.h>
#include <iomanip>
#include "Dungeon_Master.h"
#include "Character_classes.h"
#include "Character_races.h"

#pragma region implementare_scenariu

Scenariu*	Scenariu::get_instance_pointer()
{
	if (Scenariu::instance == nullptr)
		Scenariu::instance = new Scenariu;
	return Scenariu::instance;
}

Scenariu&	Scenariu::get_instance()
{
	return *get_instance_pointer();
}

void		Scenariu::destroy_instance()
{
	if (Scenariu::instance)
		delete Scenariu::instance;
	Scenariu::instance = nullptr;
}

void		Scenariu::load_rooms()
{
	bool room_exists{ true };
	std::string file_name;
	File_Manager& manager{ File_Manager::get_instance() };
	while (room_exists)
	{
		m_rooms.push_back(manager.create_room(room_exists, m_rooms.size() + 1));
	}
	m_rooms.pop_back();
	for (auto& room : m_rooms)
	{
		room->add_enemies();
		room->add_objects();
	}
}

void		Scenariu::load_player()
{

build_player:

	Player_Builder& builder{ Player_Builder::get_instance() };
	std::cin.clear();
	m_player =
		builder
		.set_name()
		.set_varsta()
		.set_rasa_caracter()
		.set_tip_caracter()
		.set_tip_caracter_trecut()
		.set_atribute()
		.build();

	std::cout << "PLAYER CREAT:\n"
		<< *m_player << '\n'
		<< "\nRAMAI LA ACEST CARACTER? (y/n):";

	char option{};
	std::cin >> option;

	if (option != 'y')
		goto build_player;

	Player_Builder::destroy_instance();
	Sleep(1500);
}

void		Scenariu::set_current_room(std::string room_name)
{
	m_current_room = get_room(room_name);
	if (m_current_room == nullptr)
		throw Exceptie_Logica(4);
}

bool		Scenariu::interactioneaza_obiect(std::string nume_obiect)
{
	IInterractive_Objects* obiect{ m_current_room->get_object(nume_obiect) };
	if (obiect == nullptr)
		return false;

	bool reusit{};

	int roll{ D20::get_instance().roll() };
	std::cout << "\n\t\tS-A ARUNCAT CU ZARUL VALOAREA "
		<< roll << std::endl;
	Sleep(2000);
	std::cout << "\nModificatorii aplicati asupra aruncarii sunt:  ";
	 
	if (obiect->get_mastery_type() == "intellect")
	{
		std::cout << std::showpos << floor(m_player->get_intellect() / 2) - 5
			<< " intellect" << std::endl;
		if (roll + floor(m_player->get_intellect() / 2) - 5 >= obiect->get_mastery())
			reusit = true;
	}

	if (obiect->get_mastery_type() == "dexterity")
	{
		std::cout << std::showpos << floor(m_player->get_dexterity() / 2) - 5
			<< " dexterity" << std::endl;
		if (roll + floor(m_player->get_dexterity() / 2) - 5 >= obiect->get_mastery())
			reusit = true;
	}
		if (obiect->get_mastery_type() == "power")	
	{
		std::cout << std::showpos << floor(m_player->get_power() / 2) - 5
			<< " power" << std::endl;
		if (roll + floor(m_player->get_power() / 2) - 5 >= obiect->get_mastery())
			reusit = true;
	}
	Sleep(1000);
	
	if (reusit == true)
	{
		std::cout << "\n\t\tINTERACTIUNEA A FOST UN SUCCES\n";
		obiect->interract();
		if (obiect->get_next_room() == false)
			get_current_room()->delete_object(obiect);
	}
	else 
		std::cout << "\n\t\tINTERACTIUNEA A ESUAT\n";
	
	Sleep(2000);
	return true;
}

bool		Scenariu::lupta_inamic(std::string nume_inamic)
{
	Enemy* inamic{ m_current_room->get_enemy(nume_inamic) };
	if (inamic == nullptr)
		return false;

	Sleep(1000);
	bool victorie{ true };
	std::cout << "\nCARACTERISTICILE CARACTERULUI TAU : \n"
		<< *m_player << std::endl;
	while (0xB1A)
	{
		Sleep(1000);
		m_player->decrease_hp(inamic->choose_ability()->damage());
		inamic->decrease_hp(m_player->choose_ability()->damage());
		
		if (m_player->get_hp() <= 0)
		{
			victorie = false;
			break;
		}
		if (inamic->get_hp() <= 0)
			break;
		
		std::cout << "\nVIATA CARACTERULUI TAU :"
			<< std::left << std::setw(40) << m_player->get_hp()
			<< "\nVIATA INAMICULUI :"
			<< std::left << std::setw(40) << inamic->get_hp() << std::endl;
		Sleep(500);
	}

	if (victorie == false)
	{
		Dungeon_Master::get_instance().game_over();
	}
	else
	{
		Sleep(1000);
		std::cout << "\nINAMICUL A FOST INFRANT\n";
		Sleep(1000);
		m_current_room->delete_enemy(inamic);
		system("cls");
		Sleep(1000);
	}
	
	return true;
}

size_t		Scenariu::get_enemies_number() const
{
	size_t counter{};
	for (auto& room : m_rooms)
		counter += room->get_enemy_number();
	return counter;
}

Room*		Scenariu::get_room(std::string room_name)
{
	for (auto& room : m_rooms)
		if (room->name() == room_name)
			return room;
	throw Exceptie_Logica(4);
	return nullptr;
}

std::ostream& 
			operator<<(std::ostream& out, const Scenariu& scn)
{
	Sleep(400);
	out << '\n';
	out << *scn.m_player;
	Sleep(1000);
	out << '\n';
	for (auto& room : scn.m_rooms)
	{
		out << *room << '\n';
		Sleep(2000);
	}
	return out;
}

Scenariu::Scenariu()
{
	m_player = Player::get_instance_pointer();
}

Scenariu::~Scenariu()
{
	m_player->destroy_instance();
	for (auto& room : m_rooms)
		delete room;
	m_rooms.clear();
	Character_classes::destroy_instance();
	Character_races::destroy_instance();
}

#pragma endregion