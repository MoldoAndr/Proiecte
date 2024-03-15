#ifndef INTERRACTIVE_OBJECTS
#define INTERRACTIVE_OBJECTS
#include "IInterractive_Objects.h"

class Interractive_Objects : public IInterractive_Objects
{ 
public:
	void			set_name(std::string) override;
	void			set_action(std::string) override;
	void			set_difficulty(short int) override;
	void			set_difficulty_type(std::string) override;
	void			set_next_room(Room*) override{}
	bool			get_next_room() override { return false; }
	void			print() const override;
	inline std::string		
					get_name() override { return m_name; }
	inline int				
					get_mastery() override { return m_difficulty; }
	inline std::string		
					get_mastery_type() override { return m_difficulty_type; }
	void			interract() override;
	friend std::ostream& 
					operator<<(std::ostream&, const Interractive_Objects&);

protected:
	std::string		m_name{};
	std::string		m_action_name{};
	short int		m_difficulty{};
	std::string		m_difficulty_type{};
};

#endif