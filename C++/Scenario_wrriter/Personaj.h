#pragma once
#include <vector>
#include <string>

class Actor;

class Personaj
{
public:
	enum class TipPersonaj
	{
		principal,
		figurant
	};
	
	Personaj(std::string s)
		: m_nume{ s }, m_nrAparitii{ 1 }, m_actorDeCareEsteJucat{ nullptr } {}

	TipPersonaj						tip() const { return m_tip; }
	void							seteazaPrincipal() { m_tip = Personaj::TipPersonaj::principal; }
	void							cresteAparitii() { m_nrAparitii++; }
	std::string						nume() const { return m_nume; }
	int								nrAparitii() const { return m_nrAparitii; }
	void							adaugaReplica(std::string_view);
	std::vector<std::string_view>	replici() const { return m_replici; }
	void							seteazaActor(Actor&);
	const Actor&					actor() { return *m_actorDeCareEsteJucat; }

private:
	std::string						m_nume{};
	int								m_nrAparitii{};
	TipPersonaj						m_tip{Personaj::TipPersonaj::figurant};
	std::vector<std::string_view>	m_replici{};
	Actor*							m_actorDeCareEsteJucat{};
};

