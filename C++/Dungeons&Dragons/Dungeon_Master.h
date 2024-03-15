#ifndef DUNGEON_MASTER_H
#define DUNGEON_MASTER_H

#include "Scenariu.h"

class Dungeon_Master
{

public:
	static Dungeon_Master&	get_instance();
	static Dungeon_Master*	get_instance_pointer();
	static void				destroy_instance();
	void					creare_scenariu();
	void					incepe_aventura();
	void					game_over();
private:
	void					interactioneaza(char);
	void					alegere_optiune();
	void					spawn_in_room();
	void					lupta_cu_inamic();
	void					interactioneaza_cu_obiect();
	Dungeon_Master();
	~Dungeon_Master();
	Dungeon_Master(Dungeon_Master&&)
							= delete;
	Dungeon_Master(const Dungeon_Master&) 
							= delete;
	inline static Dungeon_Master*
							instance{ nullptr };
	inline static Scenariu* scenariu{ nullptr };
	inline static bool		m_game_over{ false };
};

#endif