
#include <iostream>
#include <list>
#include <Windows.h>
#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Owca.h"

using namespace std;

int main()
{
    Swiat nowy_swiat;
    nowy_swiat.rysuj_swiat();
    while (true)
    {
        nowy_swiat.wykonaj_ture();
    }
    nowy_swiat.wyczysc_liste();

}
