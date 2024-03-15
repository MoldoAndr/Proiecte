#include "Replica.h"
#include <sstream>
#include <string>

Replica::Replica(Personaj& pers, std::string mesaj)
	: m_mesaj{ mesaj }, m_personaj{ pers } {}

void	stergeUltimele2(std::string& text)
{
	std::istringstream fin(text);
	std::string aux{ text };
	int nWords{};
	while (fin >> text)
		nWords++;
	std::istringstream fin2(aux);
	text = "";
	std::string aux2;
	for (int i = 0; i < nWords - 2; ++i)
	{
		fin2 >> aux2;
		text += aux2 + " ";
	}
}
		
void Replica::afiseazaReplica(std::ofstream& fout) const
{
	fout << m_mesaj << '\n';
}

void	Replica::adaugaAdnotari()
{
	stergeUltimele2(m_mesaj);
	m_mesaj.erase(m_mesaj.begin());
	m_mesaj = "(" + m_personaj.get().nume() + "): " + m_mesaj;
	m_mesaj.pop_back();
	m_mesaj.pop_back();
	m_mesaj += ".";
}
