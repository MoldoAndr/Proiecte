#ifndef CHARACTER_RACES_H
#define CHARACTER_RACES_H

#include "Abilitate.h"
#include <vector>
#include <utility>

class Character_races
{
public:
	static Character_races*		get_instance_pointer();
	static void					destroy_instance();
	static Character_races&		get_instance();
	void						add_class(const char*);
	std::vector<Abilitate*>		get_abilitati(std::string);
	friend std::ostream& operator<<(std::ostream&, const Character_races&);
private:
	inline static Character_races*
		instance{ nullptr };
	std::vector < std::pair <std::string, std::vector<Abilitate*>>>
		m_classes;
	Character_races();
	Character_races(Character_races&&) = delete;
	Character_races(const Character_races&) = delete;
	virtual	~Character_races();
};

#endif