#include "Zwierze.h"
#include "Swiat.h"
#include <iostream>
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

int Zwierze::akcja(std::list <Organizm*> &lista_organizmów, int numer_tury)
{	

	this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
	this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
	while (true)
	{
		int random = rand() % 4;
		if (random == GORA && this->getY()!=0 )
		{
			this->koordynaty.pozycja_y--;	
			break;
			
		}
		else if (random == DOL && this->getY() != 19)
		{
			this->koordynaty.pozycja_y++;
			break;
		}
		else if (random == LEWO && this->getX() !=0)
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
int Zwierze::zwroc_wolne_pole_dla_potomka(int x, int y, std::list <Organizm*> lista_organizmów)
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
int Zwierze::get_poprzedni_x()
{
	return this->poprzednie_koordynaty.poprzedni_x;
}
int Zwierze::get_poprzedni_y()
{
	return this->poprzednie_koordynaty.poprzedni_y;
}
void Zwierze::cofnij_na_poprzednia_pozycje()
{
	this->koordynaty.pozycja_x = this->poprzednie_koordynaty.poprzedni_x;
	this->koordynaty.pozycja_y = this->poprzednie_koordynaty.poprzedni_y;
}
bool Zwierze::czy_zwierze()
{
	return true;
}