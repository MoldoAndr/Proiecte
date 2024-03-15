#include "Player.h"
#include <Windows.h>
#include "D20.h"

Player&		Player::get_instance()
{
    if (Player::instance == nullptr)
        Player::instance = new Player;
    return *Player::instance;
}

Player*		Player::get_instance_pointer()
{
    if (Player::instance == nullptr)
        Player::instance = new Player;
    return Player::instance;
}

void		Player::destroy_instance()
{
    if (Player::instance)
        delete Player::instance;
    Player::instance = nullptr;
}

void		Player::set_inteligenta(short int inteligenta)
{
    m_inteligenta = inteligenta;
}

void		Player::set_dexteritate(short int dexteritate)
{
    m_dexteritate = dexteritate;
}

void		Player::set_putere(short int putere)
{
    m_putere = putere;
}

void		Player::set_hitpoints(short int hp)
{

	if (m_caracter_trecut == caracter_trecut::acolit)
	{
		m_inteligenta += 2;
		m_dexteritate += 6;
		m_putere += 2;
	}
	if (m_caracter_trecut == caracter_trecut::hot)
	{
		m_inteligenta += 6;
		m_dexteritate += 4;
		m_putere += 2;
	}
	if (m_caracter_trecut == caracter_trecut::soldat)
	{
		m_inteligenta += 2;
		m_dexteritate += 4;
		m_putere += 6;
	}
    m_hitpoints = hp;
}

Abilitate*	Player::choose_ability()
{
choose_ability:
	std::string abilitate{""};
	std::cout << "\nALEGE ABILITATE IN FUNCTIE DE NUME: ";
	std::cin >> abilitate;
	std::cout << std::endl;
	if (!get_ability(abilitate))
		goto choose_ability;
	Sleep(1000);
	std::cout << "AI ALES ABILITATEA "
		<< get_ability(abilitate)->nume()
		<< " CARE DA "
		<< get_ability(abilitate)->damage()
		<< " DAMAGE \n";
	Sleep(700);
	std::cout << "\nSE REALIZEAZA O ARUNCARE CU ZARUL\n";
	Sleep(900);
	int roll{ D20::get_instance().roll() };
	std::cout << "\nS-A ARUNCAT VALOAREA: " << roll << ' ';
	Sleep(900);

	using namespace character_info;

	if (get_ability(abilitate)->dificultate() == Difficulty_Class::intellect)
	{
		roll += static_cast<int>(floor(m_inteligenta / 2) - 5);
		std::cout << "\nS-A APLICAT MODIFICATORUL: " << std::showpos << floor(m_inteligenta / 2) - 5;
	}

	if (get_ability(abilitate)->dificultate() == Difficulty_Class::dexterity)
	{
		roll += static_cast<int>(floor(m_dexteritate / 2) - 5);
		std::cout << "\nS-A APLICAT MODIFICATORUL: " << std::showpos << floor(m_dexteritate / 2) - 5;
	}

	if (get_ability(abilitate)->dificultate() == Difficulty_Class::strengh)
	{
		roll += static_cast<int>(floor(m_putere / 2) - 5);
		std::cout << "\nS-A APLICAT MODIFICATORUL: " << std::showpos << floor(m_putere / 2) - 5;
	}
	Sleep(700);
	std::cout << '\n';
	if (roll >= get_ability(abilitate)->valoare_dif())
	{
		std::cout << "ARUNCAREA A AVUT SUCCES\n\n";
		Sleep(1000);
		return get_ability(abilitate);
	}
	std::cout << "ARUNCAREA A FOST UN ESEC\n" << "AI DAT 0 DAMAGE INAMICULUI\n\n";
	Sleep(1000);
	return new Abilitate("fake_ability", 0, 0, Difficulty_Class::intellect);
}

Player*		Player::operator-=(short int& AB)
{
	Character::operator-=(AB);
	return this;
}
