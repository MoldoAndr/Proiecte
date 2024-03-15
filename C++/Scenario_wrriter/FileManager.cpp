#include "FileManager.h"
#include "ScenaDinamica.h"
#include "ScenaStatica.h"
#include "Actor.h"
#include <cassert>

FileManager&				FileManager::fileManager()
{
	if (!FileManager::s_instance)
		FileManager::s_instance = new FileManager;
	return *FileManager::s_instance;
}

void						FileManager::distruge()
{
	if (FileManager::s_instance)
	{
		delete FileManager::s_instance;
		FileManager::s_instance = nullptr;
	}
}

void						FileManager::organizareScene(Scenariu& scenariu, std::string FisierPoveste)
{
	std::ifstream fin;
	fin.open(FisierPoveste, std::ios::in);
	std::string statice;
	std::string buffer;

	while (std::getline(fin, buffer))
	{
		if (buffer[0] == '-')
		{
			ScenaDinamica* scena{ new ScenaDinamica{} };
			std::vector<std::string> personaje{};
			scena->proceseazaReplica(buffer += "\n");
			while (std::getline(fin, buffer))
			{
				if (buffer[0] != '-')
					break;
				scena->proceseazaReplica(buffer += "\n");
			}
			scenariu.adaugaScena(scena);
		}
		else
		{
			ScenaStatica* scena{ new ScenaStatica{} };
			statice += buffer;
			while (buffer.size() != 0 && std::getline(fin, buffer))
			{
				statice += buffer;
				if (buffer.size() == 0) break;
			}
			scena->proceseazaScena(statice);
			statice = "";
			scenariu.adaugaScena(scena);
		}
	}
	fin.close();
}

void						FileManager::citireActori(Scenariu& s, std::string FisierActori, size_t nrPersonaje)
{
	//exceptie pentru cazul in care nu mai sunt actori, dar mai sunt personaje
	std::ifstream fin;
	std::string buffer, b2, b3, b4;
	double _b3{};
	Actor::TipActor _b4{};
	fin.open(FisierActori, std::ios::in);
	while (std::getline(fin, buffer))
	{
		std::istringstream word(buffer);
		while (word >> b2 >> b3 >> b4)
		{
			Actor* act;
			if (b3 == "Fericit") _b3 = Actor::stariDeSpirit[Actor::TipStareDeSpirit::fericit];
			if (b3 == "Binedispus") _b3 = Actor::stariDeSpirit[Actor::TipStareDeSpirit::binedispus];
			if (b3 == "Trist") _b3 = Actor::stariDeSpirit[Actor::TipStareDeSpirit::trist];
			if (b4 == "Principal")
			{
				_b4 = Actor::TipActor::principal;
				act = new Actor(_b4, b2, _b3);
			}
			else
			{
				_b4 = Actor::TipActor::figurant;
				act = new Actor(_b4, b2, _b3);
			}
			
			s.adaugaActor(act);
			nrPersonaje--;
		}
		if (nrPersonaje == 0)
			break;
	}
	fin.close();
	assert(nrPersonaje == 0 && "Nu sunt suficienti actori");
}

std::vector<std::string>	FileManager::citire(TipCadru Tip)
{
	std::vector<std::string> returner;

	std::ifstream fin;

	const char* filename{};

	switch (Tip)
	{
	case TipCadru::Nume:
		filename = "Text Files/nume.txt";
		break;
	case TipCadru::ElementeNaturale:
		filename = "Text Files/elementeNaturale.txt";
		break;
	case TipCadru::MomenteZi:
		filename = "Text Files/momenteZi.txt";
		break;
	case TipCadru::StareVreme:
		filename = "Text Files/stareaVremii.txt";
		break;
	case TipCadru::Verbe:
		filename = "Text Files/verbe.txt";
		break;
	}

	fin.open(filename, std::ios::in);
	std::string buffer;

	while (std::getline(fin, buffer))
	{
		returner.push_back(buffer);
	}


	fin.close();


	if (Tip == TipCadru::Nume)
		numePosibile = returner;
	return returner;
}

bool						FileManager::esteNume(const std::string& Nume)
{
	if (numePosibile.size() == 0)
		numePosibile = citire(TipCadru::Nume);
	return (std::count(numePosibile.begin(), numePosibile.end(), static_cast<std::string>(Nume)));
}

bool						FileManager::esteVerb(const std::string& Verb)
{
	if (verbePosibile.size() == 0)
		verbePosibile = citire(TipCadru::Verbe);
	return (std::count(verbePosibile.begin(), verbePosibile.end(), static_cast<std::string>(Verb)));
}

std::string&				FileManager::extrageElementNatural()
{
	if (elementeNaturale.size() == 0)
		elementeNaturale = citire(TipCadru::ElementeNaturale);
	return elementeNaturale[Random::get(0, static_cast<int>(std::size(elementeNaturale)) - 1)];
}

std::string&				FileManager::extrageMomentZi()
{
	if (momenteZi.size() == 0)
		momenteZi = citire(TipCadru::MomenteZi);
	return momenteZi[Random::get(0, static_cast<int>(std::size(momenteZi)) - 1)];
}

std::string&				FileManager::extrageStareVreme()
{
	if (stariVreme.size() == 0)
		stariVreme = citire(TipCadru::StareVreme);
	return stariVreme[Random::get(0, static_cast<int>(std::size(stariVreme)) - 1)];
}

EfectSpecial*				FileManager::extrageEfectSpecial(std::pair<std::string, double> efect)
{
	if(efect.first == "" || efect.second == 0)
		return nullptr;

	std::ifstream fin;
	std::string filename_vizuale{ "Text Files/" + efect.first + "/" + efect.first + "_vizuale.txt"};
	std::string filename_sonore{ "Text Files/" + efect.first + "/" + efect.first + "_sonore.txt" };
	std::vector<std::string> efecteVizuale{};
	std::vector<std::string> efecteSonore{};

	fin.open(filename_vizuale, std::ios::in);
	std::string buffer;
	while (std::getline(fin, buffer))
	{
		efecteVizuale.push_back(buffer);
	}
	fin.close();

	fin.open(filename_sonore, std::ios::in);
	while (std::getline(fin, buffer))
	{
		efecteSonore.push_back(buffer);
	}
	fin.close();

	//gradul de compatibilitate este mai mare decat unu tot timpul, asa ca putem sa scadem 1 si sa identificam ce efecte vom avea
	return new EfectSpecial{efecteVizuale[static_cast<size_t>(efect.second / 10 * std::size(efecteVizuale) - 1) ],
							efecteSonore[static_cast<size_t>(efect.second / 10 * std::size(efecteSonore) - 1)] };
}

void						FileManager::citireFirNarativ(Scenariu& s, std::string FisierFirNarativ)
{
	std::vector<int> firNarativ{};
	std::ifstream fin;
	fin.open(FisierFirNarativ, std::ios::in);
	int buffer;
	
	while (fin >> buffer)
		firNarativ.push_back(buffer);

	s.seteazaFirNarativ(firNarativ);

	fin.close();
}