#define  NOMINMAX
#include "Dungeon_Master.h"
#include <iostream>
#include <Windows.h>
#include "Exceptie_Logica.h"
#include <iomanip>
#include <limits>
#include <string>

#pragma region      Implementare_Dungeon_Master
        
unsigned int        read_integer(std::string text);

void                you_won();

Dungeon_Master&     Dungeon_Master::get_instance()
{
    if (Dungeon_Master::instance == nullptr)
        Dungeon_Master::instance = new Dungeon_Master;
    return *Dungeon_Master::instance;
}
    
Dungeon_Master*     Dungeon_Master::get_instance_pointer()
{
    if (Dungeon_Master::instance == nullptr)
        Dungeon_Master::instance = new Dungeon_Master;
    return Dungeon_Master::instance;
}

void                Dungeon_Master::destroy_instance()
{
    if (Dungeon_Master::instance)
        delete Dungeon_Master::instance;
    Dungeon_Master::instance = nullptr;
}

void                Dungeon_Master::creare_scenariu()
{
    scenariu->load_player();
    scenariu->load_rooms();
    scenariu->set_current_room("ROOM_1");
}

void                Dungeon_Master::interactioneaza(char optiune)
{
    if (optiune == '1')
        lupta_cu_inamic();

    if (optiune == '2')
        interactioneaza_cu_obiect();

    if (optiune == '3')
    {
        Sleep(1000);
        std::cout << std::endl << *scenariu->get_player();
        Sleep(2000);
        std::cout << *scenariu->get_current_room();
        Sleep(1000);
        alegere_optiune();
    }
}

void                Dungeon_Master::spawn_in_room()
{

    if (scenariu->get_current_room()) {
        std::cout
            << "\n\tESTI SPAWNAT IN CAMERA: "
            << *scenariu->get_current_room();
        Sleep(1000);
    }
    else throw Exceptie_Logica(4);

    alegere_optiune();
}

void                Dungeon_Master::incepe_aventura()
{
    Sleep(2000);
    system("cls");

    std::cout 
        << "\n\t\t\tINCEPE AVENTURA\n";
    
    spawn_in_room();
}

void                Dungeon_Master::alegere_optiune()
{    
    if (scenariu->get_enemies_number() == 0)
    {
        m_game_over = true;
        you_won();
        return;
    }
 
    std::cout << "ALEGE ACTIUNE(1/2/3):\n";

    if (scenariu->get_current_room()->get_enemy_number())
        std::cout << "\t1- LUPTA CU INAMIC\n";

    if (scenariu->get_current_room()->get_object_number())
        std::cout << "\t2- INTERACTIONEAZA CU OBIECT\n";

    std::cout << "\t3- AFISEAZA CARACTERISTICI CARACTER PROPRIU: \n"
        << "\t\t\t";

    char optiune{};

    while (optiune < '1' || optiune > '3')
    {
        if (scenariu->get_current_room()->get_enemy_number() == 0)
            while (optiune < '2' || optiune > '3')
                optiune = static_cast<char>(read_integer("\nALEGE OPTIUNE:") + '0');
        else
            optiune = static_cast<char>(read_integer("\nALEGE OPTIUNE:") + '0');
    }
    interactioneaza(optiune);
}

void                Dungeon_Master::interactioneaza_cu_obiect()
{
    std::string obiect;
interactioneaza:
    std::cout << "\nALEGE OBIECTUL CU CARE VREI SA INTERACTIONEZI:\n\t\t\t";
    std::cin >> obiect;
    if (scenariu->interactioneaza_obiect(obiect) == false)
        goto interactioneaza;
    std::cout << *scenariu->get_current_room();
    Sleep(1000);
    alegere_optiune();
}

void                Dungeon_Master::lupta_cu_inamic()
{
    std::string inamic;
lupta:
    std::cout << "\nALEGE INAMICUL CU CARE VREI SA TE LUPTI:";
    std::cin >> inamic;
    if (scenariu->lupta_inamic(inamic) == false)
        goto lupta;

    if (!m_game_over)
    {
        Sleep(1000);
        std::cout << *scenariu->get_current_room();
        Sleep(1000);
        alegere_optiune();
    }
}

void                Dungeon_Master::game_over()
{
    Sleep(1000);
    m_game_over = true;
    std::cout << "\n\nGAME OVER!\n\n";
    Sleep(1000);
    system("cls");
}

Dungeon_Master::Dungeon_Master()
{
    scenariu = Scenariu::get_instance_pointer();
}

Dungeon_Master::~Dungeon_Master()
{
    scenariu->destroy_instance();
}

void                you_won()
{
    Sleep(1000);
    system("cls");
    std::cout << "\n\n\n\n\n\n\t\t\t\t"
        << "YOU WON";
    Sleep(1000);
    system("cls");
}

unsigned int        read_integer(std::string text){
    
    int value{};
    while (0xB1A)
    {
        std::cout << text;
        if (std::cin >> value)
        {
            if (value >= 0)
                break;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return value;
}

#pragma endregion