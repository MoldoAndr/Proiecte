#pragma region info
/*
    STANDARD DE C++ FOLOSIT - 20
    
    NO KEY SENSITIVE LA CREAREA CARACTERULUI PROPRIU
    
    SISTEM DE LOGGING CARE SCRIE ERORILE ARUNCATE IN FISIER
    
    FOLDERE:
        character_class - descrie clasele caracterelor cu abilitatile aferente
        character_race  - descrie rasele  caracterelor cu abilitatile aferente
        ROOMS           - contine toate folderele ROOM_X, unde X este numarul camerei
                                                         - fiecare camera contine obiecte si inamici

    de asemenea, am creat 2 clase doar de management a datelor, 
    Character_classes, Character_races,
    care contin perechi denumire-vector de abilitati
    pentru un mai bun management al memoriei, fiecare caracter avand astfel un pointer
    la adresa de memorie la care este alocat acesta,
    de curatarea datelor ocupandu-se clasele singleton Character_classes si Character_races.

    Pentru evitarea padding-ului facut de catre compiler cat mai mult posibil, 
    am declarat proprietatile fiecarei clase in ordinea crescatoare a dimensiunii.

    Flux de functionare:
       - Dungeon_Master-ul da nastere scenariului, care are un player, mai multe camere cu obiecte si inamici.
       - Dupa crearea personajului, se poate relua procesul sau se incepe aventura, personajul fiind spawnat intr-o camera.
       - Ajuns in camera, poate alege actiunea : lupta cu inamic/ interactioneaza cu obiect,
                identificand apoi cu ce interacioneaza in functie de nume
       - Fiecare interactiune este conditionata de o aruncare cu zarurile asupra careia se pun diversi modificatori.
       - Jocul este - pierdut daca personajul ramane fara hitpoints
                    - castigat daca omoara toti inamicii din fiecare camera, adica din scenariu.

    Eventualele dependente circulare au fost rezolvate prin folosirea de Forward Declarations, utiliazarea pointerilor
        si prin includerea headerului de care am nevoie doar in .cpp, nu si in header.

    Inputurile de tipul int au fost tratate cu ajutorul unei functii care verifica validitatea acestuia
    Astfel a fost necesara #define NOMINMAX pentru a da bypass definitiilor pt min si max
*/
#pragma endregion

void play_game();

int main()
{
    play_game();
    return 0xB1A;
}