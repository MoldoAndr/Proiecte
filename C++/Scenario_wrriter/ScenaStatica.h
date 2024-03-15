#pragma once
#include "Scena.h"

class ScenaStatica : public Scena
{
public:
	virtual void							modificaScena() override;
	virtual void							afiseazaScena(std::ofstream&) const override final;
	void									proceseazaScena (std::string&);
	virtual void							adaugareAdnotari() override final {}
	bool									adaugaCadru(std::tuple<std::string, std::string, std::string>&) override final;
	void									definesteReplicilePersonajelor() override final {}
	virtual void							adaugaEfectSpecial(std::string_view);
	virtual std::pair<std::string, double>	determinaVremeSiCompatibilitate() override final;
	virtual std::string						extrageText() override final;

private:
	std::string								m_momentZi{};
	std::string								m_elementNatural{};
	std::string								m_stareVreme{};
	std::vector<EfectSpecial>				efecteSpeciale{};
	std::string								m_text{};
};