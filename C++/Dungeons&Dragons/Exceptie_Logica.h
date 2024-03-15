#ifndef EXCEPTIE_LOGICA_H
#define EXCEPTIE_LOGICA_H
#include "Exceptie.h"

class Exceptie_Logica : public Exceptie
{
public :
	Exceptie_Logica(int cod) :
		Exceptie(cod) {}

	std::string what() override final
	{
		std::string result;
		if (m_error_code == 1) 
			result = "INDEX OUT OF BOUNDS";
		if (m_error_code == 2)
			result = "NAME CAN'T BE AN EMPTY STRING";
		if (m_error_code == 3)
			result = "INTELIGENTA/DEXTERITATE/PUTERE NU POT FI NEGATIVE";
		if (m_error_code == 4)
			result = "COULDN'T FIND ROOM";
		if (m_error_code == 5)
			result += "NUME GRESIT";
		result += " ERROR CODE : " + std::to_string(m_error_code);

		return result;
	}
};

#endif