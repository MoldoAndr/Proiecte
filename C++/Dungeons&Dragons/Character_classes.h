#ifndef CHARACTER_CLASSES_H
#define CHARACTER_CLASSES_H

#include "Abilitate.h"
#include <vector>
#include <utility>

class Character_classes
{
public:
	static Character_classes*	get_instance_pointer();
	static void					destroy_instance();
	static Character_classes&	get_instance();
	void						add_class(const char*);
	std::vector<Abilitate*>		get_abilitati(std::string);
	friend std::ostream&		operator<<(std::ostream&, const Character_classes&);
private:
	inline static Character_classes*
								instance{ nullptr };
	std::vector < std::pair <std::string, std::vector<Abilitate*>>>
								m_classes;
	Character_classes();
	Character_classes(Character_classes&&) = delete;
	Character_classes(const Character_classes&) = delete;
	virtual ~Character_classes();
};

#endif