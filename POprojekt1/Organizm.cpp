#include <list>
#include <iostream>
#include <Windows.h>
#include "Organizm.h"
#include "Organizm.h"
#include "Swiat.h"
#include <Windows.h>
#define LEWO 0
#define PRAWO 1
#define GORA 2
#define DOL 3
#define BRAK_WOLNEGO_POLA 4
#define ORGANIZM_BRONIACY 4
#define ORGANIZM_ATAKUJACY 5
#define ROZMNAZANIE 6
#define NIC 7
using namespace std;
int Organizm::get_sila()
{
	return this->sila;
}
string Organizm::get_nazwa_gatunku()
{
	return this->nazwa_gatunku;
}
int Organizm::get_tura_startowa()
{
	return this->tura_urodzenia;
}
int Organizm::getX()
{
	return this->koordynaty.pozycja_x;
}
int Organizm::getY()
{
	return this->koordynaty.pozycja_y;
}
int Organizm::get_inicjatywa()
{
	return this->inicjatywa;
}
int Organizm::kolizja(Organizm* organizm_atakujacy, std::list <Organizm*> lista_organizmów)
{
	
	if (this->get_nazwa_gatunku() == organizm_atakujacy->get_nazwa_gatunku())
	{
		organizm_atakujacy->cofnij_na_poprzednia_pozycje();
		return this->rozmnazanie(organizm_atakujacy, lista_organizmów);
	}
	else if (this->sila > organizm_atakujacy->get_sila())
	{
		return ORGANIZM_ATAKUJACY;
	}
	else if (this->sila <= organizm_atakujacy->get_sila())
	{
		return ORGANIZM_BRONIACY;
	}
	return NIC;
}
void Organizm::zwieksz_sile()
{
	this->sila += 3;
}
void Organizm::zabij()
{
	this->czy_zyje = false;
}
bool Organizm::sprawdz_czy_zyje()
{
	return this->czy_zyje;
}
bool Organizm::czy_obil_atak()
{
	return false;
}
int Organizm::sprawdz_czy_wolne_pola(int x, int y, std::list <Organizm*> lista_organizmów)
{
	int szukane_x, szukane_y;

	for (int i = 0; i < 4; i++)
	{
		bool czy_wolne = true;
		if (i == LEWO)
		{
			szukane_x = x - 1;
			szukane_y = y;
		}
		if (i == PRAWO)
		{
			szukane_x = x + 1;
			szukane_y = y;
		}
		if (i == GORA)
		{
			szukane_x = x;
			szukane_y = y - 1;
		}
		if (i == DOL)
		{
			szukane_x = x;
			szukane_y = y + 1;
		}
		for (Organizm* organizm : lista_organizmów)
		{
			if (organizm->getX() == szukane_x && organizm->getY() == szukane_y || szukane_x > 19 || szukane_x < 0 || szukane_y >19 || szukane_y < 0)
			{
				czy_wolne = false;
				break;
			}
		}
		if (czy_wolne == true) return i;
	}
	return BRAK_WOLNEGO_POLA;
}
int Organizm::rozmnazanie(Organizm* organizm_atakujacy, std::list <Organizm*> lista_organizmów)
{
	int wolne_pole_obok_atakujacego = organizm_atakujacy->sprawdz_czy_wolne_pola(this->getX(), this->getY(), lista_organizmów);
	int wolne_pole = this->sprawdz_czy_wolne_pola(this->getX(), this->getY(), lista_organizmów);
	if (wolne_pole == BRAK_WOLNEGO_POLA && wolne_pole_obok_atakujacego == BRAK_WOLNEGO_POLA) return NIC;
	wolne_pole = this->zwroc_wolne_pole_dla_potomka(this->getX(), this->getY(), lista_organizmów);
	wolne_pole_obok_atakujacego = organizm_atakujacy->zwroc_wolne_pole_dla_potomka(this->getX(), this->getY(), lista_organizmów);
	if (wolne_pole == BRAK_WOLNEGO_POLA && wolne_pole_obok_atakujacego == BRAK_WOLNEGO_POLA) return NIC;
	if (wolne_pole == LEWO)
	{
		Organizm* organizm = this->stworz_potomka(this->swiat, this->getX() - 1, this->getY(), swiat->get_tura());
		swiat->dodaj_organizm(organizm);
	}
	else if (wolne_pole == PRAWO)
	{
		Organizm* organizm = this->stworz_potomka(this->swiat, this->getX() + 1, this->getY(), swiat->get_tura());
		swiat->dodaj_organizm(organizm);
	}
	else if (wolne_pole == GORA)
	{
		Organizm* organizm = this->stworz_potomka(this->swiat, this->getX(), this->getY() - 1, swiat->get_tura());
		swiat->dodaj_organizm(organizm);
	}
	else if (wolne_pole == DOL)
	{
		Organizm* organizm = this->stworz_potomka(this->swiat, this->getX(), this->getY() + 1, swiat->get_tura());
		swiat->dodaj_organizm(organizm);
	}
	if (wolne_pole != BRAK_WOLNEGO_POLA) return ROZMNAZANIE;
	else wolne_pole = wolne_pole_obok_atakujacego;
	// jesli nie bylo wolnych pol obok broniacego organizmu
	if (wolne_pole == LEWO)
	{
		Organizm* organizm = organizm_atakujacy->stworz_potomka(organizm_atakujacy->swiat, organizm_atakujacy->getX() - 1, organizm_atakujacy->getY(), swiat->get_tura());
		swiat->dodaj_organizm(organizm);
	}
	else if (wolne_pole == PRAWO)
	{
		Organizm* organizm = organizm_atakujacy->stworz_potomka(organizm_atakujacy->swiat, organizm_atakujacy->getX() + 1, organizm_atakujacy->getY(), swiat->get_tura());
		swiat->dodaj_organizm(organizm);
	}
	else if (wolne_pole == GORA)
	{
		Organizm* organizm = organizm_atakujacy->stworz_potomka(organizm_atakujacy->swiat, organizm_atakujacy->getX(), organizm_atakujacy->getY() - 1, swiat->get_tura());
		swiat->dodaj_organizm(organizm);
	}
	else if (wolne_pole == DOL)
	{
		Organizm* organizm = organizm_atakujacy->stworz_potomka(organizm_atakujacy->swiat, organizm_atakujacy->getX(), organizm_atakujacy->getY() + 1, swiat->get_tura());
		swiat->dodaj_organizm(organizm);
	}
	cout << "rozmnazanie (" << this->getX() << "," << this->getY() << ")" << endl;
	return  ROZMNAZANIE;
}