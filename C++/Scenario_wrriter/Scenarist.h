#pragma once
#include "Angajat.h"
class Scenarist : public Angajat
{
public:
	static Scenarist*			scenarist(std::string_view nume = "???");
	virtual void				distruge() override;
	virtual void				modificaScenariul(Scenariu&) override;

private:
	static inline Scenarist*	s_instance{ nullptr };

	Scenarist(std::string_view nume)
		: Angajat{ nume }
	{
	}
	Scenarist(const Scenarist&) = delete;
	~Scenarist()
	{
	}
};

