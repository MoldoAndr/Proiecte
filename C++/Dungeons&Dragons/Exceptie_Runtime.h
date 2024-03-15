#ifndef EXCEPTIE_RUNTIME_H
#define EXCEPTIE_RUNTIME_H
#include "Exceptie.h"

class Exceptie_Runtime : public Exceptie
{
public :
	Exceptie_Runtime(int cod) :
		Exceptie(cod) {}
	std::string what() override final
	{
		std::string result;
		if (m_error_code == 1)
			result = "RUNTIME ERROR WITH ERROR CODE " + std::to_string(m_error_code);
		return result;
	}
};

#endif