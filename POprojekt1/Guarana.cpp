#include <iostream>
#include <Windows.h>
#include "Guarana.h"
#include "Organizm.h"
#include "Roslina.h"
#define GUARANA_SILA 0
#define GUARANA_INICJATYWA 0
#define NAZWA_GATUNKU "guarana"
#define LEWO 0
#define PRAWO 1
#define GORA 2
#define DOL 3
#define BRAK_WOLNEGO_POLA 4
#define ORGANIZM_BRONIACY 4
#define ORGANIZM_ATAKUJACY 5
#define NIC 7
Guarana::Guarana(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->inicjatywa = GUARANA_INICJATYWA;
	this->sila = GUARANA_SILA;
}
void Guarana::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 4);
	cout << "G";
	SetConsoleTextAttribute(kolor, 15);
}
int Guarana::kolizja(Organizm* organizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów)
{
	cout << "Zwierze sila" << organizm_z_ktorym_kolizja->get_sila() << endl;
	organizm_z_ktorym_kolizja->zwieksz_sile();
	cout << "Zjadl guarane, aktualna sila" << organizm_z_ktorym_kolizja->get_sila() << endl;
	Sleep(5000);
	return ORGANIZM_BRONIACY;
}
Organizm* Guarana::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Guarana(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}