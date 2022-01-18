
#include <iostream>
#include <Windows.h>
#include "Mlecz.h"
#include "Organizm.h"
#include "Roslina.h"
#define MLECZ_SILA 0
#define MLECZ_INICJATYWA 0
#define NAZWA_GATUNKU "mlecz"
#define LEWO 0
#define PRAWO 1
#define GORA 2
#define DOL 3
#define ROZMNAZANIE 6
#define BRAK_WOLNEGO_POLA 4
#define NIC 7
Mlecz::Mlecz(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->inicjatywa = MLECZ_INICJATYWA;
	this->sila = MLECZ_SILA;
}
void Mlecz::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 14);
	cout << "M";
	SetConsoleTextAttribute(kolor, 15);
}
int Mlecz::akcja(std::list <Organizm*> &lista_organizmów, int numer_tury)
{
	int wolne_pole = sprawdz_czy_wolne_pola(this->getX(), this->getY(), lista_organizmów);
//	cout << "siema"<<wolne_pole << endl;
//	Sleep(1000);
	if (wolne_pole == BRAK_WOLNEGO_POLA) return NIC;

	bool nowe_pole_mlecz[4]{}; // pola obok aktualnego mlecza, czy tam ma siê pojawiæ potomek.
	int ile_prob_rozprzestrzeniania = 0;
	nowe_pole_mlecz[LEWO] = czy_wolne_pole(this->getX()-1, this->getY(), lista_organizmów);
	nowe_pole_mlecz[PRAWO] = czy_wolne_pole(this->getX()+1, this->getY(), lista_organizmów);
	nowe_pole_mlecz[GORA] = czy_wolne_pole(this->getX(), this->getY()-1, lista_organizmów);
	nowe_pole_mlecz[DOL] = czy_wolne_pole(this->getX(), this->getY()+1, lista_organizmów);
	int random = 0;
	
	while (ile_prob_rozprzestrzeniania<4)
	{
		int losowe_pole = rand() % 4;
		if (nowe_pole_mlecz[losowe_pole] == true)
		{
			//cout << "wolne pole" << endl;
			Organizm* nowy_mlecz;
			if (rand() % 100 > 75)
			{
				
				//cout << "udalo sie" << endl;
				if (losowe_pole == LEWO)
				{
					nowy_mlecz = this->stworz_potomka(this->swiat,this->getX() - 1, this->getY(), numer_tury);
					this->swiat->dodaj_organizm(nowy_mlecz);
				}
				else if (losowe_pole == PRAWO)
				{
					nowy_mlecz = this->stworz_potomka(this->swiat, this->getX() + 1, this->getY(), numer_tury);
					this->swiat->dodaj_organizm(nowy_mlecz);
				}
				else if (losowe_pole == GORA)
				{
					nowy_mlecz = this->stworz_potomka(this->swiat, this->getX(), this->getY() - 1, numer_tury);
					this->swiat->dodaj_organizm(nowy_mlecz);
				}
				else if (losowe_pole == DOL)
				{
					nowy_mlecz = this->stworz_potomka(this->swiat, this->getX(), this->getY() + 1, numer_tury);
					this->swiat->dodaj_organizm(nowy_mlecz);
				}
				nowe_pole_mlecz[losowe_pole] = false;
				if (sprawdz_czy_wolne_pola(this->getX(), this->getY(), lista_organizmów) == false) return NIC;
			}
			ile_prob_rozprzestrzeniania++;
		}
		if(nowe_pole_mlecz[0]==false && nowe_pole_mlecz[1] == false && nowe_pole_mlecz[2] == false && nowe_pole_mlecz[3] == false ) break;
	}
	return ROZMNAZANIE;
}
Organizm* Mlecz::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Mlecz(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}
bool Mlecz::czy_wolne_pole(int x, int y, std::list <Organizm*> lista_organizmów)
{
	if (x > 19 || x < 0 || y >19 || y < 0) return false;
	for (Organizm* organizm : lista_organizmów)
	{
		if (organizm->getX() == x && organizm->getY() == y) return false;
	}
	return true;
}