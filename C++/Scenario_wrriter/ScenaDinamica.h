#pragma once
#include "Scena.h"
#include "Replica.h"
#include <string>

class ScenaDinamica : public Scena
{
public:
	virtual void							afiseazaScena(std::ofstream&) const override final;
	void									proceseazaReplica(std::string&);
	virtual void							modificaScena() override {}
	virtual void							adaugareAdnotari() override final;
	bool									adaugaCadru(std::tuple<std::string, std::string, std::string>&) override final { return false; }
	void									definesteReplicilePersonajelor() override final;
	virtual void							adaugaEfectSpecial(std::string_view) override final {}
	virtual std::pair<std::string, double>	determinaVremeSiCompatibilitate() override final;
	virtual std::string						extrageText() override final;

private:
	std::vector<Replica>					m_replici{};
};