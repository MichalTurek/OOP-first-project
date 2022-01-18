
#include <iostream>
#include  <Windows.h>
#include "Zolw.h"
#define ZOLW_SILA 2
#define ZOLW_INICJATYWA 1
#define LEWO 0
#define PRAWO 1
#define GORA 2
#define DOL 3
#define BRAK_WOLNEGO_POLA 4
#define ORGANIZM_BRONIACY 4
#define ORGANIZM_ATAKUJACY 5
#define ROZMNAZANIE 6
#define NIC 7 
#define NAZWA_GATUNKU "zolw"

Zolw::Zolw(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->poprzednie_koordynaty.poprzedni_x = x;
	this->poprzednie_koordynaty.poprzedni_y = y;
	this->inicjatywa = ZOLW_INICJATYWA;
	this->sila = ZOLW_SILA;
}
void Zolw::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 6);
	cout << "Z";
	SetConsoleTextAttribute(kolor, 15);
}
int Zolw::akcja(std::list <Organizm*> &lista_organizmów, int numer_tury)
{
	this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
	this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
	int random = rand() % 4;
	if (random != 0) return NIC;
	while (true)
	{
		int random = rand() % 4;
		if (random == GORA && this->getY() != 0 )
		{
			this->koordynaty.pozycja_y--;
			break;
		}
		else if (random == DOL && this->getY() != 19 )
		{
			this->koordynaty.pozycja_y++;
			break;
		}
		else if (random == LEWO && this->getX() != 0 )
		{
			this->koordynaty.pozycja_x--;
			break;
		}
		else if (random == PRAWO && this->getX() != 19)
		{
			this->koordynaty.pozycja_x++;
			break;
		}
	}
	return NIC;
}

int Zolw::kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów)
{
	if (this->get_nazwa_gatunku() == ogranizm_z_ktorym_kolizja->get_nazwa_gatunku())
	{
		ogranizm_z_ktorym_kolizja->cofnij_na_poprzednia_pozycje();
		int wynik_rozmnazania = this->rozmnazanie(ogranizm_z_ktorym_kolizja, lista_organizmów);
		return wynik_rozmnazania;
	}
	else if (this->sila > ogranizm_z_ktorym_kolizja->get_sila())
	{
		return ORGANIZM_ATAKUJACY;
	}
	else if (this->sila <= ogranizm_z_ktorym_kolizja->get_sila() && ogranizm_z_ktorym_kolizja->get_sila()>=5)
	{
		return ORGANIZM_BRONIACY;
	}
	else if (this->sila < ogranizm_z_ktorym_kolizja->get_sila() && ogranizm_z_ktorym_kolizja->get_sila()<5)
	{
		
		cout << "kolizja z zolwikiem, atakujacy wraca na poprzednie pole, kolizja w: ("<<this->getX()<<","<<this->getY()<<endl;
		ogranizm_z_ktorym_kolizja->cofnij_na_poprzednia_pozycje();
		Sleep(7000);
		return NIC;
	}
	return NIC;
} 
Organizm* Zolw::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Zolw(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}