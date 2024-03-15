#pragma once
#include "IScena.h"
#include "Personaj.h"
#include "EfectSpecial.h"
#include <string>
#include <vector>
#include <functional>

class Scena : public IScena
{
public:
	void					afiseazaPersonajeScena() const override final;
	bool					personajulApareInScena(std::string_view) const override final;
	void					adaugaPersonaj(Personaj*) override final;
	void					stabilesteGradeCompatibilitate() override final;

protected:
	std::vector<Personaj*>	m_personaje{};
	double					m_gradCompatibilitate{};
};

