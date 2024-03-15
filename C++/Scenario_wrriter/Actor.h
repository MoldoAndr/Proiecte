#pragma once
#include "Personaj.h"
#include <string>
#include <fstream>

class Actor
{
public:

	enum class TipActor
	{
		principal,
		figurant,
	};
	enum TipStareDeSpirit
	{
		trist = 0,
		binedispus = 1,
		fericit = 2,
	};
	
	//atentie la modificarea gradului de compatibilitate si consecintele asupra generarii efectelor speciale
	inline static double stariDeSpirit[]{ 2.0, 4.0, 8.0 }; 

	Actor() = default;
	Actor(TipActor tip, std::string nume, double stare) :
		m_tipActor{ tip }, m_nume{ nume }, m_stareDeSpirit{ stare }, m_personajJucat{ nullptr }
	{
	}

	std::string_view	nume() const { return m_nume; }
	void				afiseazaActor(std::ofstream& fout) const;
	void				actualizeazaStareDeSpirit();
	const Personaj&		personaj() const { return *m_personajJucat; }
	void				seteazaPersonaj(Personaj*);
	bool				joacaPersonaj();
	double				stareDeSpirit() const { return m_stareDeSpirit; }

private:
	std::string			m_nume{};
	double				m_stareDeSpirit{};
	TipActor			m_tipActor{};
	Personaj*			m_personajJucat{};
};

