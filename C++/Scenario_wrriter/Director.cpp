#include "Director.h"

Director*	Director::director(std::string_view nume)
{
	if (!Director::s_instance)
		Director::s_instance = new Director{nume};
	return (Director::s_instance);
}

void		Director::distruge()
{
	if (Director::s_instance)
	{
		delete Director::s_instance;
		Director::s_instance = nullptr;
	}

}

void		Director::modificaScenariul(Scenariu& s)
{
	s.copiazaFirNarativInFilm(m_film);
	s.reareanjeazaScene();
	s.copiazaTextInFilm(m_film);
	s.copiazaActoriInFilm(m_film);
	redaFilmul();
}

void		Director::redaFilmul()
{
	m_film.afiseazaComponenteText();
	m_film.afiseazaActori();
	m_film.afiseazaFirNarativ();
}