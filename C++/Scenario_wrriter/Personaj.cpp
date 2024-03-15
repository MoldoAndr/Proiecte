#include "Personaj.h"
#include "Actor.h"

void	Personaj::adaugaReplica(std::string_view mesaj)
{
	m_replici.push_back(mesaj);
}

void	Personaj::seteazaActor(Actor& actor)
{
	m_actorDeCareEsteJucat = &actor;
}
