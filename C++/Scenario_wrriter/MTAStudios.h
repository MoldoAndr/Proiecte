#pragma once
#include "Angajat.h"
#include <vector>

class MTAStudios
{
public:
	static MTAStudios&			studio();
	static void					distrugeStudio();
	
	void						modificaScenariul();

private:
	static inline MTAStudios*	s_instance{nullptr};

	MTAStudios();
	MTAStudios(const MTAStudios&) = delete;
	~MTAStudios();

	Scenariu&					m_scenariu{ Scenariu::scenariu() };
	std::vector<Angajat*>		m_angajati{};
};