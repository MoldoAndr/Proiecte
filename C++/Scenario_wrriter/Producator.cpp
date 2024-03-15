#include "Producator.h"
#include "FileManager.h"

Producator*	Producator::producator(std::string_view nume)
{
	if (!Producator::s_instance)
		Producator::s_instance = new Producator{ nume };
	return (Producator::s_instance);
}

void		Producator::distruge()
{
	if (Producator::s_instance)
	{
		delete Producator::s_instance;
		Producator::s_instance = nullptr;
	}
}

void		Producator::modificaScenariul(Scenariu& s)
{

}

void		Producator::genereazaEfecte(Scenariu& s, std::vector<bool> efecte)
{
	std::vector<std::pair<std::string, double>> componenteEfecteSpeciale{ s.genereazaComponenteleEfectelorSpeciale(efecte) };
	for (auto& c : componenteEfecteSpeciale)
		m_efecteSpeciale.push_back(FileManager::fileManager().extrageEfectSpecial(c));
	for (size_t counter{}; counter < std::size(m_efecteSpeciale); counter++)
		if(componenteEfecteSpeciale[counter].first != "" && componenteEfecteSpeciale[counter].second != 0)
			s.adaugaEfectSpecial(genereazaTextulEfectului(m_efecteSpeciale[counter]), counter);
}

std::string	Producator::genereazaTextulEfectului(const EfectSpecial* e)
{
	std::string textEfect{ " " };
	textEfect = textEfect + static_cast<std::string>(e->efectVizual());
	textEfect[1] = toupper(textEfect[1]);
	textEfect += " si ";
	textEfect += e->efectSonor();
	textEfect += '.';
	return textEfect;
}