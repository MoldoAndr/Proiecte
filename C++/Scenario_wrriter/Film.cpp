#include "Film.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>

void	Film::adaugaComponentaText(std::string_view comp)
{
	m_componenteText.emplace_back(comp);
}
		
void	Film::adaugaActorPersonaj(std::string_view numeActor, std::string_view numePersonaj)
{
	m_actoriPersonaje.emplace_back(numeActor, numePersonaj);
}
		
void	Film::seteazaFirNarativ(std::vector<int>& firNarativ)
{
	m_firNarativ = firNarativ;
}
		
void	Film::afiseazaComponenteText()
{
	std::cout << std::endl;
	for (const auto &s : m_componenteText)
		std::cout << s << std::endl << std::endl;
}
		
void	Film::afiseazaActori()
{
	std::cout << std::endl;
	std::cout.width(27);
	std::cout << "Au jucat:\n";
	for (const auto& ap : m_actoriPersonaje)
	{
		std::cout.width(20);
		std::cout << ap.first << " : ";
		std::cout << ap.second << '\n';
	}
}
		
void	Film::afiseazaFirNarativ()
{
	std::cout << std::endl;
	std::cout.width(27);
	std::cout << "Firul narativ:\n";
	std::cout.width(10);
	for (auto i : m_firNarativ)
		std::cout << i << ' ';
	std::cout << std::endl;
}
