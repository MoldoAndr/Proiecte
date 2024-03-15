#pragma once
#include <vector>
#include <string_view>
#include <utility>
class Film
{
public:
	void					   	adaugaComponentaText(std::string_view);
	void						adaugaActorPersonaj(std::string_view, std::string_view);
	void						seteazaFirNarativ(std::vector<int>&);
	void						afiseazaComponenteText();
	void						afiseazaActori();
	void						afiseazaFirNarativ();

private:
	std::vector<std::string>	m_componenteText{};
	std::vector<int>			m_firNarativ{};
	std::vector<std::pair<std::string, std::string>>
								m_actoriPersonaje{};
};

