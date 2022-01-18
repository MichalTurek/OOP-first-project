
#include <iostream>
#include "Owca.h"
#include "Organizm.h"
#include "Zwierze.h"
#define OWCA_SILA 4
#define OWCA_INICJATYWA 4
#define NAZWA_GATUNKU "owca"
using namespace std;

Owca::Owca(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->poprzednie_koordynaty.poprzedni_x = x;
	this->poprzednie_koordynaty.poprzedni_y = y;
	this->inicjatywa = OWCA_INICJATYWA;
	this->sila = OWCA_SILA;
}
void  Owca::rysowanie()
{
	cout << "O";
}

Organizm* Owca::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Owca(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}