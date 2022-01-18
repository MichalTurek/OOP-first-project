#include <iostream>
#include <Windows.h>
#include "Barszcz_sosnowskiego.h"
#include "Organizm.h"
#include "Roslina.h"
#define JAGODY_SILA 10
#define JAGODY_INICJATYWA 0
#define NAZWA_GATUNKU "barszcz sosnowskiego"
#define LEWO 0
#define PRAWO 1
#define GORA 2
#define DOL 3
#define ROZMNAZANIE 6
#define BRAK_WOLNEGO_POLA 4
#define ORGANIZM_BRONIACY 4
#define ORGANIZM_ATAKUJACY 5
#define NIC 7
#define WIELE_GINIE 8
Barszcz_sosnowskiego::Barszcz_sosnowskiego(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->inicjatywa = JAGODY_INICJATYWA;
	this->sila = JAGODY_SILA;
}
void Barszcz_sosnowskiego::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 13);
	cout << "B";
	SetConsoleTextAttribute(kolor, 15);
}
int Barszcz_sosnowskiego::kolizja(Organizm* organizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmow)
{
	if (organizm_z_ktorym_kolizja->get_sila() < this->get_sila())
	{
		cout << "zwierze weszlo na pole barszczu sosnowkiego, ginie";
		//Sleep(3000);
		while (true)
		{
			bool czy_usnieto_martwe = true;
			for (Organizm* organizm : lista_organizmow)
			{
				if (organizm->sprawdz_czy_zyje() == false)
				{
					cout << organizm->get_nazwa_gatunku() << " " << organizm->getX() << " " << organizm->getY() << endl;
					swiat->delete_organism(organizm);
					czy_usnieto_martwe = false;
					break;
				}
			}
			if (czy_usnieto_martwe) break;
		}
		return ORGANIZM_ATAKUJACY;
	}
	else
	{
		cout << "roslina zjadla barszcz sosnowskiego, ale przeplacila to zyciem" << endl;
		//Sleep(3000);
		return WIELE_GINIE;
	}
}
int Barszcz_sosnowskiego::akcja(std::list <Organizm*> &lista_organizmow, int numer_tury)
{
	int szukane_x, szukane_y;
	bool czy_ktos_zginol = false;
	for (int i = 0; i < 4; i++)
	{
		if (i == LEWO)
		{
			szukane_x = this->getX() - 1;
			szukane_y = this->getY();
		}
		if (i == PRAWO)
		{
			szukane_x = this->getX() + 1;
			szukane_y = this->getY();
		}
		if (i == GORA)
		{
			szukane_x = this->getX();
			szukane_y = this->getY() - 1;
		}
		if (i == DOL)
		{
			szukane_x = this->getX();
			szukane_y = this->getY() + 1;
		}
		for (Organizm* organizm : lista_organizmow)
		{
			if (organizm->getX() == szukane_x && organizm->getY() == szukane_y && organizm->czy_zwierze()&& organizm->czy_obil_atak()==false)
			{
				czy_ktos_zginol = true;
				organizm->zabij();
			}
		}
	}
	while (true)
	{
		bool czy_usnieto_martwe = true;
		for (Organizm* organizm : lista_organizmow)
		{
			if (organizm->sprawdz_czy_zyje() == false)
			{
				cout << organizm->get_nazwa_gatunku() << " " << organizm->getX() << " " << organizm->getY() << endl;
				swiat->delete_organism(organizm);
				czy_usnieto_martwe = false;
				break;
			}
		}
		if (czy_usnieto_martwe) break;
	}
	if (czy_ktos_zginol)return WIELE_GINIE;
	int wolne_pole = sprawdz_czy_wolne_pola(this->getX(), this->getY(), lista_organizmow);
	if (wolne_pole == BRAK_WOLNEGO_POLA) return BRAK_WOLNEGO_POLA;
	int random = rand() % 100;
	wolne_pole = this->zwroc_wolne_pole_dla_potomka(this->getX(), this->getY(), lista_organizmow);
	if (wolne_pole == BRAK_WOLNEGO_POLA || random < 80) return NIC;
	if (wolne_pole == LEWO)
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
Organizm* Barszcz_sosnowskiego::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Barszcz_sosnowskiego(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}