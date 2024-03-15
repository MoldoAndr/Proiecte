#include "Interractive_Objects.h"
#include <iomanip>
#include <Windows.h>
#include "Player.h"
#include "Scenariu.h"

#pragma region obiect_interactiv

std::ostream&	operator<<(std::ostream& out, const Interractive_Objects& obj)
{
	out << std::left
		<< std::setw(15) << obj.m_name
		<< std::setw(15) << obj.m_action_name
		<< std::setw(15) << obj.m_difficulty
		<< std::setw(15) << obj.m_difficulty_type ;

	return out;
}

void			Interractive_Objects::set_name(std::string nume)
{
	m_name = nume;
}

void			Interractive_Objects::set_action(std::string actiune)
{
	m_action_name = actiune;
}

void			Interractive_Objects::set_difficulty(short int diff)
{
	m_difficulty = diff;
}

void			Interractive_Objects::set_difficulty_type(std::string diff_tip)
{
	m_difficulty_type = diff_tip;
}

void			Interractive_Objects::print() const
{
	std::cout << *this;
}

void			Interractive_Objects::interract()
{
	Sleep(1000);
	std::cout << std::left << std::setw(10)
		<< "IN URMA INTERACTIUNII CU "
		<< m_name
		<< " AI CASTIGAT: " << m_difficulty / 2
		<< " " << m_difficulty_type << std::endl;
	Sleep(1000);

	if (m_difficulty_type == "intellect")
		Player::get_instance().set_inteligenta
		(Player::get_instance().get_intellect() + m_difficulty / 2);

	if (m_difficulty_type == "dexterity")
		Player::get_instance().set_dexteritate
		(Player::get_instance().get_dexterity() + m_difficulty / 2);

	if (m_difficulty_type == "power")
		Player::get_instance().set_putere
		(Player::get_instance().get_power() + m_difficulty / 2);

	std::cout << std::endl << std::left << std::setw(30)
		<< "NOILE CARACTERISTICI ALE CARACTERULUI:";

	Sleep(2000);
	std::cout << Player::get_instance();
	Sleep(1000);
}

#pragma endregion