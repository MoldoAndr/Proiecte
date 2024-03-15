#include "Character.h"
#include <Windows.h>
#include "File_Manager.h"
#include "D20.h"


#pragma region implementare_caracter

void		Character::set_caracter(tip_caracter tip)
{
	m_tip = tip;
}

void		Character::set_caracter(rasa_caracter rasa)
{
	m_rasa = rasa;
}

void		Character::set_caracter(caracter_trecut trecut)
{
	m_caracter_trecut = trecut;
	define_arguments();	
}

void		Character::set_caracter(std::string nume)
{
	m_nume = nume;
}

void		Character::set_caracter(short int varsta)
{
	m_varsta = varsta;
}

Abilitate*	Character::get_ability(std::string nume_abilitate)
{
	for (auto& abilitate : m_abilitati)
		if (abilitate->nume() == nume_abilitate)
			return abilitate;
	return nullptr;
}

Character*	Character::operator-=(const short int& abilitate)
{
	decrease_hp(abilitate);
	return this;
}
	
void		Character::define_arguments()
{
	
	Character_classes*	clase	{ Character_classes::get_instance_pointer() };
	Character_races*	rase	{ Character_races::get_instance_pointer() };
		
	if (m_rasa == rasa_caracter::elf)
		m_abilitati = rase->get_abilitati("ELF");
	if (m_rasa == rasa_caracter::goblin)
		m_abilitati = rase->get_abilitati("GOBLIN");
	if (m_rasa == rasa_caracter::human)
		m_abilitati = rase->get_abilitati("HUMAN");

	std::vector<Abilitate*> aux_vector;

	if (m_tip == tip_caracter::Fighter)
		aux_vector = clase->get_abilitati("FIGHTER");
	if (m_tip == tip_caracter::Sorcerer)
		aux_vector = clase->get_abilitati("SORCERER");
	if (m_tip == tip_caracter::Wizard)
		aux_vector = clase->get_abilitati("WIZARD");

	m_abilitati.insert(m_abilitati.end(), aux_vector.begin(), aux_vector.end());
}

std::ostream& 
			operator<<(std::ostream& out, const Character& ch)
{
	out << "\n\tNUME:            " << ch.m_nume
		<< "\n\tVARSTA:          " << ch.m_varsta
		<< "\n\tINTELIGENTA:     " << ch.m_inteligenta
		<< "\n\tDEXTERITATE:     " << ch.m_dexteritate
		<< "\n\tPUTERE:          " << ch.m_putere
		<< "\n\tHITPOINTS:       " << ch.m_hitpoints
		<< "\n\tCARACTER TRECUT: ";
	
	switch (ch.m_caracter_trecut)
	{
	case caracter_trecut::acolit:
		out << "ACOLIT";
		break;
	case caracter_trecut::hot:
		out << "HOT";
		break;
	case caracter_trecut::soldat:
		out << "SOLDAT";
		break;
	}
	out << "\n\tTIP CARACTER:    ";
	switch (ch.m_tip)
	{
	case tip_caracter::Fighter:
		out << "FIGHTER";
		break;
	case tip_caracter::Sorcerer:
		out << "SORCERER";
		break;
	case tip_caracter::Wizard:
		out << "WIZARD";
		break;
	}
	out << "\n\tRASA CARACTER:   ";
	switch (ch.m_rasa)
	{
	case rasa_caracter::elf:
		out << "ELF";
		break;
	case rasa_caracter::goblin:
		out << "GOBLIN";
		break;
	case rasa_caracter::human:
		out << "HUMAN";
		break;
	}
	
	out << "\n\tABILITATI:\n\tname  \t\tdamage\t\tdiff difficulty class\n";

	for (auto& abilitate : ch.m_abilitati)
		out << "\t" << *abilitate;
	out << "\n\n";
	return out;
}

#pragma endregion