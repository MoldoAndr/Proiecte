#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"

class Enemy : public Character
{
public:
	void		randomize_atributes	();
	Abilitate*	choose_ability() override final;
	Enemy*		operator-=(const short int&);
};

#endif