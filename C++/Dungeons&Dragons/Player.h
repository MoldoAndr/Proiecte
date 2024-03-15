#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character
{
public:
	static			Player& get_instance();
	static			Player* get_instance_pointer();
	static			void	destroy_instance();
	void			set_inteligenta(short int);
	void			set_dexteritate(short int);
	void			set_putere(short int);
	void			set_hitpoints(short int);
	Abilitate*		choose_ability() override;
	Player*			operator-=(short int&);
private:
	inline static Player*	
					instance{ nullptr };
	Player()		= default;
	Player(const Player&) 
					= delete;
	Player(Player&&)
					= delete;
};

#endif