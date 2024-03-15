#pragma once
#include "Scena.h"
#include "ScenaDinamica.h"
#include "Actor.h"
#include "Personaj.h"
#include "ScenaStatica.h"
#include "EfectSpecial.h"
#include "Film.h"
#include <fstream>

class Scenariu
{
public:
	static Scenariu&		scenariu();
	static void				distruge();

	std::size_t				nrActori() const { return std::size(m_actori); };
	std::size_t				nrPersonaje() const { return std::size(m_personaje); }
	void					afiseazaScenariu(std::ofstream&);
	void					adaugaScena(Scena*);
	void					adaugaPersonaj(Personaj*);
	void					afiseazaPersonaje(std::ofstream&) const;
	void					adaugaAdnotari();
	void					stabilestePersonajePrincipale();
	void					adaugaActor(Actor*);
	void					distribuiePersonajeActorilor();
	void					actualizeazaStareDeSpiritActori();
	bool					maiAdaugaCadru(std::tuple<std::string, std::string, std::string>&);
	void					definesteReplicilePersonajelor();
	void					stabilesteGradeCompatibilitate();
	std::size_t				numaraScene();
	std::vector<std::pair<std::string, double>>
							genereazaComponenteleEfectelorSpeciale(std::vector<bool>);
	void					seteazaFirNarativ(std::vector<int>);
	void					adaugaEfectSpecial(std::string_view, std::size_t);
	void					reareanjeazaScene();
	void					copiazaTextInFilm(Film&);
	void					copiazaActoriInFilm(Film&);
	void					copiazaFirNarativInFilm(Film&);

private:
	static inline Scenariu*	s_instance{nullptr};

	Scenariu()
	{
	}
	Scenariu(const Scenariu&) = delete;
	~Scenariu();

	std::vector<Scena*>		m_scene{};
	std::vector<int>		m_firNarativ{};
	std::vector<Actor*>		m_actori{};
	std::vector<Personaj*>	m_personaje{};
	
	void					amestecaActori();

	friend void ScenaStatica::proceseazaScena(std::string&);
	friend void ScenaDinamica::proceseazaReplica(std::string&);
};

