#pragma once
#include "IAngajat.h"
#include <string>
#include <string_view>

class Angajat : public IAngajat
{
public:
	int					id() const { return m_id; }
	std::string_view	nume() const { return m_nume; }
	void				inregistreazaModificari(Scenariu&, std::ofstream&) override final;

private:
	static inline int	s_idGenerator{ 1 };
	std::string			m_nume{};
	int					m_id{};
	
protected:
	Angajat(std::string_view);
};

