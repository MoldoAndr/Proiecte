#include "Abilitate.h"
#include "Exceptie_Logica.h"
#include <iomanip>
#pragma region implementare_abilitate

std::ostream& operator<<(std::ostream& out, const Abilitate& abilitate)
{
	out << std::left << std::setw(15) 
		<< abilitate.m_nume << " - " << std::setw(15) 
		<< abilitate.m_damage << ' '
		<< abilitate.m_diff_quant << ' ';

	if (abilitate.m_dificultate == Difficulty_Class::intellect)
		out << std::left << std::setw(20) << " intellect" << std::endl;

	if (abilitate.m_dificultate == Difficulty_Class::strengh)
		out << std::left << std::setw(20) << " strengh" << std::endl;

	if (abilitate.m_dificultate == Difficulty_Class::dexterity)
		out << std::left << std::setw(20) << " dexterity" << std::endl;

	return out;
}

Abilitate::Abilitate(std::string nume_2,short int damage,short int diff_q, Difficulty_Class dificultate)
{
	if (nume_2.empty())
		throw Exceptie_Logica(2);
	m_nume			= nume_2;
	m_damage		= damage;
	m_dificultate	= dificultate;
	m_diff_quant	= diff_q;
}

#pragma endregion