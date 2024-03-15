#include "Enemy.h"
#include "Rand_Gen.h"
#include <Windows.h>

#define ATRIBUTES_SUM 30

void		Enemy::randomize_atributes()
{
	Rand_Gen& engine{ Rand_Gen::getInstance() };
	engine.setSum(ATRIBUTES_SUM);
	auto valori{ engine.generateValues() };
	m_rasa = static_cast<character_info::rasa_caracter>(engine.getRandomValue(3) - 1);
	m_tip = static_cast<character_info::tip_caracter>(engine.getRandomValue(3) - 1);
	m_caracter_trecut = static_cast<character_info::caracter_trecut>(engine.getRandomValue(3) - 1);
	m_inteligenta	= std::get<0>(valori);
	m_dexteritate	= std::get<1>(valori);
	m_putere		= std::get<2>(valori);
	m_hitpoints		= engine.getRandomValue(150);
	Rand_Gen::destroy_instance();
	define_arguments();
}

Abilitate*	Enemy::choose_ability()
{
	Sleep(500);
	short int rand{ Rand_Gen::getInstance().getRandomValue(static_cast<short>(m_abilitati.size() - 1)) };
	std::cout << '\n' << m_nume << " A ALES ABILITATEA " << m_abilitati[rand]->nume()
		<< " CARE DA " << m_abilitati[rand]->damage() << " DAMAGE \n";
	Sleep(500);
	return m_abilitati[rand];
}

Enemy* Enemy::operator-=(const short int& AB)
{
	Character::operator-=(AB);
	return this;
}
