#pragma once
#include "Angajat.h"
class Regizor : public Angajat
{
public:
	static Regizor*										regizor(std::string_view nume = "???");
	virtual void										distruge() override;

	virtual void										modificaScenariul(Scenariu&) override;

private:
	static inline Regizor*								s_instance{ nullptr };

	Regizor(std::string_view nume)
		: Angajat{ nume }
	{
	}
	Regizor(const Regizor&) = delete;
	~Regizor()
	{
	}

	std::tuple<std::string, std::string, std::string>	genereazaCadru();
	std::vector<bool>									decideAsupraEfectelor(Scenariu&);
};

