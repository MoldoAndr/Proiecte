#include "Player_Builder.h"
#include "Rand_Gen.h"
#include <string>
#include <Windows.h>

#define ATRIBUTES_SUM 50

#pragma region creare_personaj

void to_upper(std::string& text);

Player_Builder& Player_Builder::get_instance()
{
    if (Player_Builder::instance == nullptr)
        Player_Builder::instance = new Player_Builder();
    return *Player_Builder::instance;
}

void            Player_Builder::destroy_instance()
{
    if (Player_Builder::instance)
        delete Player_Builder::instance;
    Player_Builder::instance = nullptr;
    Player_Builder::_Player   = nullptr;
}

Player_Builder& Player_Builder::set_name()
{
    std::string nume;
    std::cout << "\nNUMELE CARACTERULUI:                         ";
    read_name:
    std::getline(std::cin, nume);
    if (nume != "")
        _Player->set_caracter(nume);
    else goto read_name;
    std::cin.clear();
    std::cin.sync();
    return *this;
}

unsigned int read_integer(std::string text);

Player_Builder& Player_Builder::set_varsta()
{
    unsigned int varsta{};
    std::string text{ "\nVARSTA CARACTERULUI(1->100):                 " };
    while (varsta <= 0 || varsta >= 101)
    {
        varsta = read_integer(text);
    }
    _Player->set_caracter(varsta);
    std::cin.clear();
    std::cin.sync();
    return *this;
}

Player_Builder& Player_Builder::set_rasa_caracter()
{

alegere_rasa:
    std::string rasa_aux;
    rasa_caracter rasa;
    std::cout << "\nRASA CARACTERULUI(HUMAN/ELF/GOBLIN):         ";
    std::cin >> rasa_aux;
    to_upper(rasa_aux);
    if (rasa_aux == "HUMAN")
        rasa = rasa_caracter::human;
    else if (rasa_aux == "GOBLIN")
        rasa = rasa_caracter::goblin;
    else if (rasa_aux == "ELF")
        rasa = rasa_caracter::elf;
    else goto alegere_rasa;
    _Player->set_caracter(rasa);
    return *this;
}

Player_Builder& Player_Builder::set_tip_caracter()
{

alegere_tip:
    tip_caracter tip;
    std::string tip_aux;
    std::cout << "\nTIPUL CARACTERULUI(FIGHTER/SORCERER/WIZARD): ";
    std::cin >> tip_aux;
    to_upper(tip_aux);
    if (tip_aux == "FIGHTER")
        tip = tip_caracter::Fighter;
    else if (tip_aux == "SORCERER")
        tip = tip_caracter::Sorcerer;
    else if (tip_aux == "WIZARD")
        tip = tip_caracter::Wizard;
    else goto alegere_tip;
    _Player->set_caracter(tip);
    return *this;
}

Player_Builder& Player_Builder::set_tip_caracter_trecut()
{

alegere_caracter_trecut:
    caracter_trecut trecut;
    std::string trecut_aux;
    std::cout << "\nCARACTERUL TRECUT(SOLDAT/ACOLIT/HOT):        ";
    std::cin >> trecut_aux;
    to_upper(trecut_aux);
    if (trecut_aux == "SOLDAT")
        trecut = caracter_trecut::soldat;
    else if (trecut_aux == "ACOLIT")
        trecut = caracter_trecut::acolit;
    else if (trecut_aux == "HOT")
        trecut = caracter_trecut::hot;
    else goto alegere_caracter_trecut;
    _Player->set_caracter(trecut);
    return *this;
}

Player_Builder& Player_Builder::set_atribute()
{
    Sleep(1000);
    
    std::cout << "\nATRIBUTELE (INTELIGENTA/DEXTERITATE/PUTERE)\nAU FOST ALESE RANDOM A.I. SUMA LOR SA FIE " << ATRIBUTES_SUM << '\n';
    
    Rand_Gen& generator{ Rand_Gen::getInstance() };
    generator.setSum(ATRIBUTES_SUM);
    
    std::tuple<short int,short int,short int> 
            valori{ generator.generateValues() };
    
    _Player->set_inteligenta(std::get<0>(valori));
    _Player->set_dexteritate(std::get<1>(valori));
    _Player->set_putere(std::get<2>(valori));

    Sleep(1000);

    std::cout << "\nPENTRU VALOAREA HITPOINTS \nA FOST ALES UN NUMAR RANDOM INTRE 0 - > 200\n";
    _Player->set_hitpoints(generator.getRandomValue(200));
    
    Sleep(1000);

    std::cout << "\nIN FUNCTIE DE CARACTERUL TRECUT AU FOST APLICATI ASUPRA\nCARACTERISTICILOR MODIFICATORII CORESPUNZATORI\n\n";
    
    Sleep(1000);

    return *this;
}
    
Player*         Player_Builder::build()
{
    return _Player;
}

void            to_upper(std::string& text)
{
    for (size_t i{}; i < text.size(); ++i)
        text[i] = static_cast<char>(toupper(text[i]));
}

#pragma endregion