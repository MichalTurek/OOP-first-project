#include "Trawa.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "Organizm.h"
#include "Roslina.h"
#define TRAWA_SILA 0
#define TRAWA_INICJATYWA 0
#define NAZWA_GATUNKU "trawa"

Trawa::Trawa(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->inicjatywa = TRAWA_INICJATYWA;
	this->sila = TRAWA_SILA;
}
void Trawa::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor,2);
	cout << "T";
	SetConsoleTextAttribute(kolor, 15);
}
Organizm* Trawa::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Trawa(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}