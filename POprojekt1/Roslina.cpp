#include <iostream>
#include <Windows.h>
#include <ctime>
#include "Roslina.h"
#include "Organizm.h"
#define LEWO 0
#define PRAWO 1
#define GORA 2
#define DOL 3
#define ROZMNAZANIE 6
#define BRAK_WOLNEGO_POLA 4
#define NIC 7

using namespace std;
void Roslina::cofnij_na_poprzednia_pozycje()
{
	return;
}
int Roslina::akcja(std::list <Organizm*> &lista_organizmów, int numer_tury)
{
	int wolne_pole = sprawdz_czy_wolne_pola(this->getX(), this->getY(), lista_organizmów);
	if (wolne_pole == BRAK_WOLNEGO_POLA) return BRAK_WOLNEGO_POLA;
	int random = rand() % 100;
	wolne_pole = this->zwroc_wolne_pole_dla_potomka(this->getX(), this->getY(), lista_organizmów);
	if (wolne_pole == BRAK_WOLNEGO_POLA || random < 75) return NIC;
	if(wolne_pole == LEWO)
	{
		Organizm* organizm = this->stworz_potomka(this->swiat, this->getX() - 1, this->getY(), this->swiat->get_tura());
		this->swiat->dodaj_organizm(organizm);
	}
	if (wolne_pole == PRAWO)
	{
		Organizm* organizm = this->stworz_potomka(this->swiat, this->getX() + 1, this->getY(), this->swiat->get_tura());
		this->swiat->dodaj_organizm(organizm);
	}
	if (wolne_pole == GORA)
	{
		Organizm* organizm = this->stworz_potomka(this->swiat, this->getX(), this->getY() - 1, this->swiat->get_tura());
		this->swiat->dodaj_organizm(organizm);
	}
	if (wolne_pole == DOL)
	{
		Organizm* organizm = this->stworz_potomka(this->swiat, this->getX(), this->getY() + 1, this->swiat->get_tura());
		this->swiat->dodaj_organizm(organizm);
	}
	return ROZMNAZANIE;
}

bool Roslina::czy_zwierze()
{
	return false;
}
int Roslina::zwroc_wolne_pole_dla_potomka(int x, int y, std::list <Organizm*> lista_organizmów)
{
	int ilosc_prob = 0;
	while (true)
	{
		ilosc_prob++;
		if (ilosc_prob > 16) break;
		int random = rand() % 4;
		int szukane_x=0, szukane_y=0;
		bool czy_wolne = true;
		if (random == LEWO)
		{
			szukane_x = x - 1;
			szukane_y = y;
		}
		else if (random == PRAWO)
		{
			szukane_x = x + 1;
			szukane_y = y;
		}
		else if (random == GORA)
		{
			szukane_x = x;
			szukane_y = y - 1;
		}
		else if (random == DOL)
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
		if (czy_wolne == true)
		{
			return random;
		}

	}
	return BRAK_WOLNEGO_POLA;
}