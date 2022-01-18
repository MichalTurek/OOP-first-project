#include <iostream>
#include <Windows.h>
#include "Wilcze_jagody.h"
#include "Organizm.h"
#include "Roslina.h"
#define JAGODY_SILA 99
#define JAGODY_INICJATYWA 0
#define NAZWA_GATUNKU "wilcze jagody"
#define LEWO 0
#define PRAWO 1
#define GORA 2
#define DOL 3
#define BRAK_WOLNEGO_POLA 4
#define ORGANIZM_BRONIACY 4
#define ORGANIZM_ATAKUJACY 5
#define NIC 7
#define WIELE_GINIE 8
Wilcze_jagody::Wilcze_jagody(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->inicjatywa = JAGODY_INICJATYWA;
	this->sila = JAGODY_SILA;
}
void Wilcze_jagody::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 13);
	cout << "J";
	SetConsoleTextAttribute(kolor, 15);
}
int Wilcze_jagody::kolizja(Organizm* organizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów)
{
	if (organizm_z_ktorym_kolizja->get_sila() < this->get_sila())
	{
		cout << "zwierze weszlo na pole wilczych jagod, ginie";
		Sleep(3000);
		return ORGANIZM_ATAKUJACY;
	}
	else
	{
		cout << "roslina zjadla wilcze jagody, ale przeplacila to zyciem" << endl;
		Sleep(3000);
		return WIELE_GINIE;
	}
}
Organizm* Wilcze_jagody::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Wilcze_jagody(swiat,x, y, aktualna_tura);
	return nowy_ogranizm;
}