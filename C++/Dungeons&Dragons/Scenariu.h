#ifndef SCENARIU_H
#define SCENARIU_H

#include "Player.h"
#include "Room.h"

class Scenariu
{
public:
	static Scenariu&	get_instance();
	static Scenariu*	get_instance_pointer();
	static void			destroy_instance();
	void				load_rooms();
	void				load_player();
	inline Room*		get_room(std::string);
	inline Room*		get_current_room() { return m_current_room; }
	inline Player*		get_player() { return m_player; }
	void				set_current_room(std::string);
	bool				interactioneaza_obiect(std::string);
	bool				lupta_inamic(std::string);
	friend std::ostream& operator<<(std::ostream&, const Scenariu&);
	size_t				get_enemies_number() const;
private:
	static inline Scenariu*
		instance{ nullptr };

	Scenariu();
	Scenariu(const Scenariu&) = delete;
	Scenariu(Scenariu&&) = delete;
	~Scenariu();

	Player*				m_player{};
	Room*				m_current_room{};
	std::vector<Room*>	m_rooms;
};

#endif