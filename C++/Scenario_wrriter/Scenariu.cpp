#include "Scenariu.h"
#include "Random.h"
#include <cassert>
#include <algorithm>
#include <numeric>

Scenariu::~Scenariu()
{
	for (auto a : m_actori)
	{
		delete a;
		a = nullptr;
	}
	for (auto s : m_scene)
	{
		delete s;
		s = nullptr;
	}
	for (auto p : m_personaje)
	{
		delete p;
		p = nullptr;
	}
}

void		zip(
			const std::vector<Scena*>&,
			const std::vector<int>&,
			std::vector<std::pair<Scena*, int>>&);

void		unzip(
			const std::vector<std::pair<Scena*, int>>&,
			std::vector<Scena*>&,
			std::vector<int>&);

Scenariu&	Scenariu::scenariu()
{
	if (!Scenariu::s_instance)
		Scenariu::s_instance = new Scenariu;
	return (*Scenariu::s_instance);
}

void		Scenariu::distruge()
{
	if (Scenariu::s_instance)
	{
		delete Scenariu::s_instance;
	}
	Scenariu::s_instance = nullptr;
}

void		Scenariu::adaugaScena(Scena* s)
{
	m_scene.emplace_back(s);
}

void		Scenariu::adaugaPersonaj(Personaj* p)
{
	m_personaje.push_back(p);
}

void		Scenariu::afiseazaPersonaje(std::ofstream& fout) const
{
	for (const auto& p : m_personaje)
	{
		fout << p->nume() << ' ' << p->nrAparitii() << '\n';
		for (auto r : p->replici())
			fout << r << '\n';
	}
	fout << std::endl;
}

void		Scenariu::afiseazaScenariu(std::ofstream& fout)
{
	afiseazaPersonaje(fout);

	for (auto& actor : m_actori)
		actor->afiseazaActor(fout);

	for (auto& scena : m_scene)
		scena->afiseazaScena(fout);
}

void		Scenariu::adaugaAdnotari()
{
	for (auto& scena : m_scene)
		scena->adaugareAdnotari();
}

void		Scenariu::stabilestePersonajePrincipale()
{
	std::sort(m_personaje.begin(), m_personaje.end(), [](Personaj* a, Personaj* b)
														{
															return a->nrAparitii() > b->nrAparitii();
														});
	for (std::size_t i{ 0 }; i < 3; i++)
		m_personaje[i]->seteazaPrincipal();
}

void		Scenariu::adaugaActor(Actor* act)
{
	m_actori.push_back(act);
}

void		Scenariu::amestecaActori()
{
	std::shuffle(m_actori.begin(), m_actori.end(), Random::mt);
}

void		Scenariu::distribuiePersonajeActorilor()
{
	amestecaActori();
	for (std::size_t i{ 0 }; i < nrPersonaje(); i++)
	{
		m_actori[i]->seteazaPersonaj(m_personaje[i]);
		m_personaje[i]->seteazaActor(*m_actori[i]);
	}
}

void		Scenariu::actualizeazaStareDeSpiritActori()
{
	for (auto& a : m_actori)
		a->actualizeazaStareDeSpirit();
}

bool		Scenariu::maiAdaugaCadru(std::tuple<std::string, std::string, std::string>& cadru)
{
	bool maiAdauga{ true };
	static std::size_t i = 0;
	for (; i < std::size(m_scene); i++)
	{
		if (m_scene[i]->adaugaCadru(cadru) == true)
		{
			i++;
			return true;
		}
	}
	return false;
}

void		Scenariu::definesteReplicilePersonajelor()
{
	for (auto& scena : m_scene)
		scena->definesteReplicilePersonajelor();
}

void		Scenariu::stabilesteGradeCompatibilitate()
{
	for (auto& scena : m_scene)
		scena->stabilesteGradeCompatibilitate();
}

size_t		Scenariu::numaraScene()
{
	return std::size(m_scene);
}

std::vector<std::pair<std::string, double>>
			Scenariu::genereazaComponenteleEfectelorSpeciale(std::vector<bool>efecte)
{
	std::vector<std::pair<std::string, double>> efecteSpeciale{};
	size_t counter{};
	for (auto& scena : m_scene)
	{
		if(efecte[counter++] == true)
			efecteSpeciale.push_back(scena->determinaVremeSiCompatibilitate());
		else
			efecteSpeciale.emplace_back("", 0);
	}
	return efecteSpeciale;
}

void		Scenariu::seteazaFirNarativ(std::vector<int> firNarativ)
{
	m_firNarativ = firNarativ;
}

void		Scenariu::adaugaEfectSpecial(std::string_view efect, std::size_t numarScena)
{
	m_scene[numarScena]->adaugaEfectSpecial(efect);
}

void		Scenariu::reareanjeazaScene()
{
	std::vector<std::pair<Scena*, int>> zipped;
	zip(m_scene, m_firNarativ, zipped);
	std::sort(std::begin(zipped), std::end(zipped),
		[&](const auto& a, const auto& b)
		{
			return a.second > b.second;
		});
	unzip(zipped, m_scene, m_firNarativ);
}

void		Scenariu::copiazaTextInFilm(Film& film)
{
	for (const auto& scena : m_scene)
	{
		film.adaugaComponentaText(scena->extrageText());
	}
}

void		Scenariu::copiazaActoriInFilm(Film& film)
{
	for (const auto& a : m_actori)
	{
		film.adaugaActorPersonaj(a->nume(), a->personaj().nume());
	}
}

void		Scenariu::copiazaFirNarativInFilm(Film& film)
{
	film.seteazaFirNarativ(m_firNarativ);
}

void		zip(
			const std::vector<Scena*>& a,
			const std::vector<int>& b,
			std::vector<std::pair<Scena*, int>>& zipped)
{
	for (size_t i = 0; i < a.size(); ++i)
	{
		zipped.push_back(std::make_pair(a[i], b[i]));
	}
}

void		unzip(
			const std::vector<std::pair<Scena*, int>>& zipped,
			std::vector<Scena*>& a,
			std::vector<int>& b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = zipped[i].first;
		b[i] = zipped[i].second;
	}
}