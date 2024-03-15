#ifndef EXCEPTIE_FISIER_H
#define EXCEPTIE_FISIER_H
#include "Exceptie.h"

class Exceptie_Fisier : public Exceptie
{
public:
	Exceptie_Fisier(int cod) :
		Exceptie(cod) {}
	std::string what() override final
	{
		std::string result;
		if (m_error_code == 1)
			result = "EROARE LA DESCHIDEREA FISIERULUI CU CODUL " + std::to_string(m_error_code);
		if (m_error_code == 2)
			result = "EROARE LA INCHIDEREA FISIERULUI CU CODUL " + std::to_string(m_error_code);
		return result;
	}
};

#endif