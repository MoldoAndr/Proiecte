#include "Scenarist.h"
#include "FileManager.h"
#include "Scenariu.h"

Scenarist*	Scenarist::scenarist(std::string_view nume)
{
	if (!Scenarist::s_instance)
		Scenarist::s_instance = new Scenarist(nume);
	return (Scenarist::s_instance);
}

void		Scenarist::distruge()
{
	if (Scenarist::s_instance)
	{
		delete Scenarist::s_instance;
		Scenarist::s_instance = nullptr;
	}
}

void		Scenarist::modificaScenariul(Scenariu& s)
{
	FileManager::fileManager().organizareScene(s, "Text Files/Poveste.txt");
	FileManager::fileManager().citireFirNarativ(s, "Text Files/FirNarativ.txt");

	s.adaugaAdnotari();
	s.stabilestePersonajePrincipale();
}