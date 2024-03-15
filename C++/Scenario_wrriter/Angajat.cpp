#include "Angajat.h"

Angajat::Angajat(std::string_view nume)
	:m_id{ Angajat::s_idGenerator++ }, m_nume{ nume }
{
}

void	Angajat::inregistreazaModificari(Scenariu& s, std::ofstream& fout)
{
	s.afiseazaScenariu(fout);
}
