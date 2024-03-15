#ifndef CHARACTER_H
#define CHARACTER_H

#include "ICharacter.h"
#include "character_info.h"
#include "Character_classes.h"
#include "Character_races.h"

using namespace character_info;
class Room;

class Character : public ICharacter
{
public :
	void				set_caracter(tip_caracter);
	void				set_caracter(rasa_caracter);
	void				set_caracter(caracter_trecut);
	void				set_caracter(std::string);
	void				set_caracter(short int);
	Abilitate*			get_ability(std::string);
	inline short int	get_intellect() const override { return m_inteligenta; }
	inline short int	get_dexterity() const override { return m_dexteritate; }
	inline short int	get_power() const override { return m_putere; }
	inline std::string	get_name() const override { return m_nume; }
	inline short int	get_hp() const override { return m_hitpoints; }
	inline void			decrease_hp(short damage) override { m_hitpoints -= damage; };
	Abilitate*			choose_ability() override = 0;
	Character*			operator-=(const short int&);
	friend std::ostream&
						operator<<(std::ostream&, const Character&);

protected :

	void				define_arguments();

	short int			m_varsta{};
	short int			m_inteligenta{};
	short int			m_dexteritate{};
	short int			m_putere{};
	short int			m_hitpoints{};
	
	tip_caracter		m_tip{};
	rasa_caracter		m_rasa{};
	caracter_trecut		m_caracter_trecut{};
	std::string			m_nume{};

	std::vector
		<Abilitate*>	m_abilitati{};
	
};

#endif