#include "Actor.h"
#include <fstream>
#include <cassert>

std::ostream&	operator<<(std::ostream& out, Actor::TipActor tip)
{
	switch (tip)
	{
	case Actor::TipActor::principal:
		out << "principal";
		break;
	case Actor::TipActor::figurant:
		out << "figurant";
		break;
	default:
		out << "??";
	}

	return out;
}

void			Actor::afiseazaActor(std::ofstream& fout) const 
{
	fout << m_nume << ' ' << m_stareDeSpirit << ' ' << m_tipActor << std::endl;
}

void			Actor::actualizeazaStareDeSpirit()
{
	if (!joacaPersonaj())
		return;
	if (m_tipActor == Actor::TipActor::figurant && m_personajJucat->tip() == Personaj::TipPersonaj::principal)
		m_stareDeSpirit *= static_cast<double>(5) / 4;
	if (m_tipActor == Actor::TipActor::principal && m_personajJucat->tip() == Personaj::TipPersonaj::figurant)
		m_stareDeSpirit *= static_cast<double>(3) / 4;
}

void			Actor::seteazaPersonaj(Personaj* personaj)
{
	m_personajJucat = personaj;
}

bool			Actor::joacaPersonaj()
{
	if (m_personajJucat == nullptr)
		return false;
	return true;
} 
