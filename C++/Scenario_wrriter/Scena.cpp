#include "Scena.h"
#include "Actor.h"
#include <iostream>

void	Scena::afiseazaPersonajeScena() const
{
	for (auto personaj : m_personaje)
		std::cout << personaj->nume();
	std::cout << std::endl;
}
		
bool	Scena::personajulApareInScena(std::string_view numePersonaj) const
{
	for (const auto& personaj : m_personaje)
		if (personaj->nume() == numePersonaj)
			return true;
	return false;
}
		
void	Scena::adaugaPersonaj(Personaj* personaj)
{
	m_personaje.push_back(personaj);
}
		
void	Scena::stabilesteGradeCompatibilitate()
{
	if (std::size(m_personaje) == 0)
	{
		m_gradCompatibilitate = 0;
		return;
	}
	for (auto& p : m_personaje)
		m_gradCompatibilitate += p->actor().stareDeSpirit() * 0.5;
	m_gradCompatibilitate /= std::size(m_personaje);
}
