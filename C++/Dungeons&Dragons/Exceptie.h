#ifndef EXCEPTIE_H
#define EXCEPTIE_H
#include "IExceptie.h"
#include <string>

class Exceptie : public IExceptie
{
protected:
	Exceptie(int cod_eroare) :
		m_error_code{ cod_eroare } {}
	int m_error_code {};
};
#endif