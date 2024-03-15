#ifndef PLAYER_BUILDER_H
#define PLAYER_BUILDER_H

#include "Player.h"
#include "character_info.h"
#include <iostream>
using namespace character_info;

class Player_Builder
{
	/*
			.set_name()
			.set_varsta()
			.set_rasa_caracter()
			.set_tip_caracter()
			.set_tip_caracter_trecut()
			.set_atribute
			.build()};
	*/
public:
	static Player_Builder&	get_instance();
	static void				destroy_instance();
	
	Player_Builder&			set_name();
	Player_Builder&			set_varsta();
	Player_Builder&			set_rasa_caracter();
	Player_Builder&			set_tip_caracter();
	Player_Builder&			set_tip_caracter_trecut();
	Player_Builder&			set_atribute();
	Player*					build();

private:
	inline static Player*		   _Player{ nullptr };
	inline static Player_Builder* instance{ nullptr };
	Player_Builder() { _Player = Player::get_instance_pointer(); }
	Player_Builder(const Player_Builder&) = delete;
	Player_Builder(Player_Builder&&) = delete;
};

#endif