#pragma once
#include "Personaj.h"
#include <string>
#include <functional>
#include <iostream>
#include <fstream>

class Replica
{
public:
	Replica(Personaj&, std::string);

	void								afiseazaReplica(std::ofstream&) const;
	void								adaugaAdnotari();
	std::string_view					mesaj() const { return m_mesaj; }
	Personaj&							personaj() { return m_personaj.get(); }

private:
	std::string							m_mesaj{};
	std::reference_wrapper<Personaj>	m_personaj;
};
