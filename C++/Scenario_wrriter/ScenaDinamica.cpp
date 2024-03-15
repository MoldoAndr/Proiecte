#include "ScenaDinamica.h"
#include "FileManager.h"
#include "Scenariu.h"
#include <sstream>
#include <algorithm>
#include <cassert>
#include <iostream>

void							ScenaDinamica::adaugareAdnotari()
{
	for (auto& replica : m_replici)
		replica.adaugaAdnotari();
}

void							ScenaDinamica::definesteReplicilePersonajelor()
{
	for (auto& r : m_replici)
		r.personaj().adaugaReplica(r.mesaj());
}

std::pair<std::string, double>	ScenaDinamica::determinaVremeSiCompatibilitate()
{
	return std::pair<std::string, double>{ "", 0 };
}

std::string						ScenaDinamica::extrageText()
{
	std::string text{};
	for (const auto& r : m_replici)
	{
		text += r.mesaj();
		text += '\n';
	}
	text.pop_back();
	return text;
}

void							ScenaDinamica::afiseazaScena(std::ofstream& fout) const
{
	fout << std::endl;
	for (auto& scene : m_replici)
		scene.afiseazaReplica(fout);
	fout << std::endl;
}

void							ScenaDinamica::proceseazaReplica(std::string& text)
{
	std::string numePersonaj;
	FileManager& manager{ FileManager::fileManager() };
	std::istringstream word(text);
	std::string aux;
	bool eVerb = false;
	while (word >> aux)
	{
		if (manager.esteVerb(aux))
		{
			eVerb = true;
			word >> numePersonaj;
			numePersonaj.pop_back();
			break;

		}
	}

	bool personajGasitInScenariu{ false };

	for (auto& personaj : Scenariu::scenariu().m_personaje)
		if (personaj->nume() == numePersonaj)
		{
			personaj->cresteAparitii();
			m_replici.push_back(Replica{ *personaj,text });
			personajGasitInScenariu = true;
			if (!personajulApareInScena(numePersonaj))
				adaugaPersonaj(personaj);
		}
	if (personajGasitInScenariu == false && eVerb == true)
	{
		Personaj* personaj{ new Personaj{numePersonaj} };
		Scenariu::scenariu().adaugaPersonaj(personaj);
		adaugaPersonaj(personaj);
		m_replici.push_back(Replica{ *personaj ,text});
	}
}