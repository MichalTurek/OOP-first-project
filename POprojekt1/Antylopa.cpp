#include "Antylopa.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#define ANTYLOPA_SILA 4
#define ANTYLOPA_INICJATYWA 4
#define LEWO 0
#define PRAWO 1
#define GORA 2
#define DOL 3
#define BRAK_WOLNEGO_POLA 4
#define ORGANIZM_BRONIACY 4
#define ORGANIZM_ATAKUJACY 5
#define ROZMNAZANIE 6
#define NIC 7 
#define NAZWA_GATUNKU "antylopa"
using namespace std;
Antylopa::Antylopa(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->poprzednie_koordynaty.poprzedni_x = x;
	this->poprzednie_koordynaty.poprzedni_y = y;
	this->inicjatywa = ANTYLOPA_INICJATYWA;
	this->sila = ANTYLOPA_SILA;
}
void Antylopa::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 1);
	cout << "A";
	SetConsoleTextAttribute(kolor, 15);
	
}
int Antylopa::akcja(std::list <Organizm*> &lista_organizmów, int numer_tury)
{
	int ile_ruchow_wykonal = 0;
	cout << this->getX() << " " << this->getY()<<endl;
	while (true)
	{
		this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
		this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
		int random = rand() % 4;
		if (random == GORA && this->getY() != 0)
		{
			this->koordynaty.pozycja_y--;
		}
		else if (random == DOL && this->getY() != 19 )
		{
			this->koordynaty.pozycja_y++;
		}
		else if (random == LEWO && this->getX() != 0 )
		{
			this->koordynaty.pozycja_x--;
		}
		else if (random == PRAWO && this->getX() != 19)
		{
			this->koordynaty.pozycja_x++;
		}
		ile_ruchow_wykonal++;
		if (sprawdz_czy_kolizja(this->getX(), this->getY(), lista_organizmów) == true || ile_ruchow_wykonal>=2)break; 
	}
	return NIC;
}
int Antylopa::kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów)
{
	cout << "kolizja " << this->getX() << "," << this->getY() << endl;
	cout << "kolizja" << ogranizm_z_ktorym_kolizja->getX() << "," << ogranizm_z_ktorym_kolizja->getY() << endl;
	if (this->get_nazwa_gatunku() == ogranizm_z_ktorym_kolizja->get_nazwa_gatunku())
	{
		ogranizm_z_ktorym_kolizja->cofnij_na_poprzednia_pozycje();
		int wynik_rozmnazania = this->rozmnazanie(ogranizm_z_ktorym_kolizja, lista_organizmów);
		return wynik_rozmnazania;
	}
	int random = rand() % 2;
	int wolna_pozycja = znajdz_wolne_pole(this->getX(), this->getY(), lista_organizmów);
	if (random == 0 || wolna_pozycja==NIC)
	{
		if (this->sila > ogranizm_z_ktorym_kolizja->get_sila())
		{
			return ORGANIZM_ATAKUJACY;
		}
		else if (this->sila <= ogranizm_z_ktorym_kolizja->get_sila() )
		{
			return ORGANIZM_BRONIACY;
		}
	}
	else if (wolna_pozycja == PRAWO)this->koordynaty.pozycja_x++;
	else if (wolna_pozycja == LEWO)this->koordynaty.pozycja_x--;
	else if (wolna_pozycja == GORA)this->koordynaty.pozycja_y--;
	else if (wolna_pozycja == DOL)this->koordynaty.pozycja_y++;
	cout << this->nazwa_gatunku << " uciekla przed walka z " << ogranizm_z_ktorym_kolizja->get_nazwa_gatunku() << endl;
	cout << this->getX() << "," << this->getY() << endl;
	return NIC;
}
int Antylopa::znajdz_wolne_pole(int x, int y, std::list <Organizm*> lista_organizmów)
{
	if (sprawdz_czy_kolizja(this->getX() + 1, this->getY(), lista_organizmów)) return PRAWO;
	if (sprawdz_czy_kolizja(this->getX() - 1, this->getY(), lista_organizmów)) return LEWO;
	if (sprawdz_czy_kolizja(this->getX() , this->getY()-1, lista_organizmów)) return GORA;
	if (sprawdz_czy_kolizja(this->getX() , this->getY()+1, lista_organizmów)) return DOL;
	return NIC;
}
bool Antylopa::sprawdz_czy_kolizja(int x, int y, std::list <Organizm*> lista_organizmów)
{
	for (Organizm* organizm : lista_organizmów)
	{
		if (organizm->getX() == x && organizm->getY() == y && uintptr_t(organizm) != uintptr_t(this)) return true;
	}
	return false;
}
Organizm* Antylopa::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	Organizm* nowy_ogranizm = new Antylopa(swiat, x, y, aktualna_tura);
	return nowy_ogranizm;
}