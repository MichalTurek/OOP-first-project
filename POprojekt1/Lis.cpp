#include "Lis.h"
#include <iostream>
#include <Windows.h>
#define LIS_SILA 3
#define LIS_INICJATYWA 7
#define GORA 0
#define DOL 1
#define LEWO 2
#define PRAWO 3
#define NAZWA_GATUNKU "lis"
#define NIC 7
Lis::Lis(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->poprzednie_koordynaty.poprzedni_x = x;
	this->poprzednie_koordynaty.poprzedni_y = y;
	this->inicjatywa = LIS_INICJATYWA;
	this->sila = LIS_SILA;
}
void Lis::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 7);
	cout << "L";
	SetConsoleTextAttribute(kolor, 15);
}
int Lis::akcja(std::list <Organizm*> &lista_organizmów, int numer_tury)
{
	int how_many_attempts =0;
	this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
	this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
	while (true)
	{
		how_many_attempts++;
		if (how_many_attempts > 48) break;
		int random = rand() % 4;

		if (random == GORA && this->getY() != 0 && this->sprawdz_czy_bezpiecznie(this->getX(),this->getY() - 1,lista_organizmów))
		{
			this->koordynaty.pozycja_y--;
			break;

		}
		else if (random == DOL && this->getY() != 19 && this->sprawdz_czy_bezpiecznie(this->getX(), this->getY() + 1, lista_organizmów))
		{
			this->koordynaty.pozycja_y++;
			break;
		}
		else if (random == LEWO && this->getX() != 0 && this->sprawdz_czy_bezpiecznie(this->getX() - 1, this->getY(), lista_organizmów))
		{
			this->koordynaty.pozycja_x--;
			break;
		}
		else if (random == PRAWO && this->getX() != 19 && this->sprawdz_czy_bezpiecznie(this->getX() + 1, this->getY(), lista_organizmów))
		{
			this->koordynaty.pozycja_x++;
			break;
		}
	}
	return NIC;
}
bool Lis::sprawdz_czy_bezpiecznie(int x, int y, std::list <Organizm*> lista_organizmów)
{
	for (Organizm* organizm : lista_organizmów)
	{
		if (organizm->getX() == x && organizm->getY() == y && organizm->get_sila() > LIS_SILA) return false;
	}
	return true;
}
Organizm* Lis::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Lis(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}