#include "MTAStudios.h"
#include "Scenarist.h"
#include "Regizor.h"
#include "Producator.h"
#include "Director.h"
#include <fstream>

std::string	creeazaFisierAngajat(const Angajat&);

MTAStudios::MTAStudios()
{
	m_angajati.push_back(Scenarist::scenarist("scenarist"));
	m_angajati.push_back(Regizor::regizor("regizor"));
	m_angajati.push_back(Producator::producator("producator"));
	m_angajati.push_back(Director::director("director"));
}

MTAStudios::~MTAStudios()
{
	for (auto& a : m_angajati)
		a->distruge();
	Scenariu::distruge();
}

MTAStudios&	MTAStudios::studio()
{
	if (!MTAStudios::s_instance)
		MTAStudios::s_instance = new MTAStudios();
	return (*MTAStudios::s_instance);
}

void		MTAStudios::distrugeStudio()
{
	if (MTAStudios::s_instance)
		delete MTAStudios::s_instance;
	MTAStudios::s_instance = nullptr;
}

void		MTAStudios::modificaScenariul()
{
	for (auto& a : m_angajati)
	{
		a->modificaScenariul(m_scenariu);
		std::ofstream fout{ creeazaFisierAngajat(*a).c_str() };
		a->inregistreazaModificari(m_scenariu, fout);
		fout.close();
	}
}

std::string	creeazaFisierAngajat(const Angajat& a)
{
	return std::string{ "Modificari/" + std::string{a.nume()} + ".txt"};
}