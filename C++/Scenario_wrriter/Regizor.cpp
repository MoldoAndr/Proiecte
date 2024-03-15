#include "Regizor.h"
#include "FileManager.h"
#include "Producator.h"
#include "Random.h"
#include <cassert>

Regizor*											Regizor::regizor(std::string_view nume)
{
	if (!Regizor::s_instance)
		Regizor::s_instance = new Regizor{ nume };
	return (Regizor::s_instance);
}

void												Regizor::distruge()
{
	if (Regizor::s_instance)
	{
		delete Regizor::s_instance;
		Regizor::s_instance = nullptr;
	}
}

void												Regizor::modificaScenariul(Scenariu& s)
{
	FileManager::fileManager().citireActori(s, "Text Files/Actori.txt", s.nrPersonaje());
	s.distribuiePersonajeActorilor();
	s.actualizeazaStareDeSpiritActori();
	std::tuple<std::string, std::string, std::string> cadru{ genereazaCadru() };
	while (s.maiAdaugaCadru(cadru))
		cadru = genereazaCadru();
	s.definesteReplicilePersonajelor();
	s.stabilesteGradeCompatibilitate();
	Producator::producator()->genereazaEfecte(s, Regizor::decideAsupraEfectelor(s));
}

std::tuple<std::string, std::string, std::string>	Regizor::genereazaCadru()
{
	std::string& momentZi{FileManager::fileManager().extrageMomentZi()};
	std::string& elementNatural{FileManager::fileManager().extrageElementNatural()};
	std::string& stareVreme{FileManager::fileManager().extrageStareVreme()};

	return std::tuple<std::string, std::string, std::string>{ momentZi, elementNatural, stareVreme };
}

std::vector<bool>									Regizor::decideAsupraEfectelor(Scenariu& s)
{
	std::vector<bool> efecte(s.numaraScene());
	for (auto e : efecte)
		e = static_cast<bool>(Random::get(0, 1));
	return efecte;
}
