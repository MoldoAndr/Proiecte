#pragma once
#include "Angajat.h"
#include "Film.h"

class Director : public Angajat
{
public:
	static Director*			director(std::string_view nume = "???");
	virtual void				distruge() override;
								
	virtual void				modificaScenariul(Scenariu&) override;
								
private:						
	static inline Director*		s_instance{ nullptr };

	Director(std::string_view nume)
		: Angajat{ nume }
	{
	}
	Director(const Director&) = delete;
	~Director()
	{
	}

	void						redaFilmul();

	Film						m_film{};
};

