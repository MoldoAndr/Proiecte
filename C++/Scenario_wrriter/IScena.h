#pragma once
#include "Personaj.h"
#include <string_view>
#include <string>
#include <utility>
class IScena
{
public:
	virtual void							modificaScena() = 0;
	virtual void							afiseazaScena(std::ofstream&) const = 0;
	virtual void							adaugareAdnotari() = 0;
	virtual void							afiseazaPersonajeScena() const = 0;
	virtual bool							personajulApareInScena(std::string_view) const = 0;
	virtual void							adaugaPersonaj(Personaj*) = 0;
	virtual bool							adaugaCadru(std::tuple<std::string, std::string, std::string>&) = 0;
	virtual void							definesteReplicilePersonajelor() = 0;
	virtual void							stabilesteGradeCompatibilitate() = 0;
	virtual void							adaugaEfectSpecial(std::string_view) = 0;
	virtual std::pair<std::string, double>	determinaVremeSiCompatibilitate() = 0;
	virtual std::string						extrageText() = 0;
};

