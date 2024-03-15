#include "ScenaStatica.h"
#include "FileManager.h"
#include <cctype>
#include <fstream>
#include <cassert>
	
void							ScenaStatica::modificaScena()
{

}

void							ScenaStatica::afiseazaScena(std::ofstream& fout) const
{
	fout << m_text << std::endl;
}

void							ScenaStatica::proceseazaScena(std::string& text)
{
	std::string numePersonaj;
	FileManager& manager{ FileManager::fileManager() };
	std::istringstream word(text);
	std::string aux;
	bool gasitInScenariu{ false };
	m_text = text;

	while (word >> aux)
	{
		if (!std::isalpha(aux.back()))
			aux.pop_back();
		if (manager.esteNume(aux))
		{
			gasitInScenariu = false;
			for (auto& personaj : Scenariu::scenariu().m_personaje)
				if (personaj->nume() == aux)
				{
					personaj->cresteAparitii();
					gasitInScenariu = true;
					if (!personajulApareInScena(aux))
						adaugaPersonaj(personaj);
				}
			if (!gasitInScenariu)
			{
				Personaj* personaj{ new Personaj{aux} };
				Scenariu::scenariu().adaugaPersonaj(personaj);
				adaugaPersonaj(personaj);
			}
		}
	}
}

bool							ScenaStatica::adaugaCadru(std::tuple<std::string, std::string, std::string>& cadru)
{
	m_momentZi = std::get<0>(cadru);
	m_elementNatural = std::get<1>(cadru);
	m_stareVreme = std::get<2>(cadru);
	m_text = m_momentZi + ". Afara este " + m_stareVreme + " si se vad " + m_elementNatural + ". " + m_text;
	return true;
}

void							ScenaStatica::adaugaEfectSpecial(std::string_view efect)
{
	m_text.insert(m_text.find_first_of(".", m_text.find_first_of(".") + 1) + 1, efect);
}

std::pair<std::string, double>	ScenaStatica::determinaVremeSiCompatibilitate()
{
	return std::pair<std::string, double>{m_stareVreme, m_gradCompatibilitate};
}

std::string						ScenaStatica::extrageText()
{
	return m_text;
}
