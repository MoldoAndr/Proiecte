#ifndef ICHARACTER_H
#define ICHARACTER_H
#include "character_info.h"
#include <string>
using namespace character_info;
class Abilitate;

class ICharacter
{
	virtual void				set_caracter(tip_caracter)		= 0;
	virtual void				set_caracter(rasa_caracter)		= 0;
	virtual void				set_caracter(caracter_trecut)	= 0;
	virtual void				set_caracter(std::string)		= 0;
	virtual void				set_caracter(short int)			= 0;
	virtual void				decrease_hp(short)				= 0;
	virtual Abilitate*			choose_ability()				= 0;
	virtual short int			get_intellect() const			= 0;
	virtual short int			get_dexterity() const			= 0;
	virtual short int			get_power()		const			= 0;
	virtual short int			get_hp()		const			= 0;
	virtual std::string			get_name()		const			= 0;
};

#endif