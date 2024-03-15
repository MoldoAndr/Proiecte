#ifndef ABILITATE_H
#define ABILITATE_H
#include <iostream>

enum Difficulty_Class
{
	intellect,
	dexterity,
	strengh,
};

class Abilitate
{
public:
	Abilitate(std::string,short int,short int, Difficulty_Class);

	inline short int&			damage() { return m_damage; }
	inline std::string&			nume() { return m_nume; }
	inline  Difficulty_Class&	dificultate() { return m_dificultate; }
	inline short int			valoare_dif() { return m_diff_quant; }
	friend std::ostream&
								operator<<(std::ostream&, const Abilitate&);
private:
	std::string					m_nume;
	short int					m_damage{};
	short int					m_diff_quant{};
	Difficulty_Class			m_dificultate{};
};

#endif