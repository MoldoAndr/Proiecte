#pragma once
#include "Angajat.h"
#include "Scenariu.h"
#include "Regizor.h"
#include "EfectSpecial.h"
class Producator : public Angajat
{
public:
	static Producator*			producator(std::string_view nume = "???");
	virtual void				distruge() override;

	virtual void				modificaScenariul(Scenariu&) override;

private:
	static inline Producator*	s_instance{ nullptr };

	Producator(std::string_view nume)
		: Angajat{ nume }
	{
	}
	Producator(const Producator&) = delete;
	~Producator()
	{
	}
	
	std::vector<EfectSpecial*>	m_efecteSpeciale{};

	void						genereazaEfecte(Scenariu&, std::vector<bool>);
	std::string					genereazaTextulEfectului(const EfectSpecial*);

	friend void Regizor::modificaScenariul(Scenariu&);
};

