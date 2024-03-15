#pragma once
#include "Scenariu.h"
class IAngajat
{
public:
	virtual void	distruge() = 0;
	virtual void	modificaScenariul(Scenariu&) = 0;
	virtual void	inregistreazaModificari(Scenariu&, std::ofstream&) = 0;
};

