
#include <iostream>
#include <windows.h>
#include "Wilk.h"
#include "Organizm.h"
#include "Zwierze.h"
#define WILK_SILA 9
#define WILK_INICJATYWA 5
#define NAZWA_GATUNKU "wilk"
using namespace std;

Wilk::Wilk(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->poprzednie_koordynaty.poprzedni_x = x;
	this->poprzednie_koordynaty.poprzedni_y = y;
	this->inicjatywa = WILK_INICJATYWA;
	this->sila = WILK_SILA;
}
void  Wilk::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 8);
	cout << "W";
	SetConsoleTextAttribute(kolor, 15);
}
Organizm* Wilk::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Wilk(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}
