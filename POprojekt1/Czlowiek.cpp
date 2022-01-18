#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include "Czlowiek.h"
#include "Organizm.h"
#include "Zwierze.h"
#define CZLOWIEK_SILA 5
#define CZLOWIEK_INICJATYWA 4
#define NAZWA_GATUNKU "czlowiek"
#define GORA 0
#define DOL 1
#define LEWO 2
#define PRAWO 3
#define ORGANIZM_BRONIACY 4
#define ORGANIZM_ATAKUJACY 5
#define NIC 7
using namespace std;


Czlowiek::Czlowiek(Swiat* swiat, int x, int y, int tura_aktualna)
{
	this->swiat = swiat;
	this->nazwa_gatunku = NAZWA_GATUNKU;
	this->tura_urodzenia = tura_aktualna;
	this->koordynaty.pozycja_x = x;
	this->koordynaty.pozycja_y = y;
	this->poprzednie_koordynaty.poprzedni_x = x;
	this->poprzednie_koordynaty.poprzedni_y = y;
	this->inicjatywa = CZLOWIEK_INICJATYWA;
	this->sila = CZLOWIEK_SILA;
}
void Czlowiek::rysowanie()
{
	HANDLE kolor;
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(kolor, 11);
	cout << "@";
	SetConsoleTextAttribute(kolor, 15);
}
int Czlowiek::akcja(std::list <Organizm*> &lista_organizmow, int numer_tury)
{
	this->poprzednie_koordynaty.poprzedni_y = this->koordynaty.pozycja_y;
	this->poprzednie_koordynaty.poprzedni_x = this->koordynaty.pozycja_x;
	cout << "wykonaj ruch" << endl;
	if (this->specjalna_umiejetnosc_wlaczona &&  numer_tury -specjalna_umiejetnosc_start_tura >= 5)
	{
		cout << "Nie jestes juz niesmiertelny" << endl;
		this->specjalna_umiejetnosc_wlaczona = false;
	}
	while (true)
	{
		int  zadanie = _getch();
		if (zadanie == 'w' || zadanie == 'W' ||  zadanie== 72)
		{
			if (this->getY() != 0)
			{
				this->koordynaty.pozycja_y--;
				break;
			}
			else cout << "nie mozesz wykonac tego ruchu" << endl;
		}
		if (zadanie == 's' || zadanie == 'S' || zadanie == 80)
		{
			if (this->getY() != 19)
			{
				this->koordynaty.pozycja_y++;
				break;
			}
			else cout << "nie mozesz wykonac tego ruchu" << endl;
		}
		if (zadanie == 'A' || zadanie == 'a' || zadanie == 75)
		{
			if (this->getX() != 0)
			{
				this->koordynaty.pozycja_x--;
				break;
			}
			else cout << "nie mozesz wykonac tego ruchu" << endl;
		}
		if (zadanie == 'd' || zadanie == 'D' || zadanie == 77)
		{
			if (this->getX() != 19)
			{
				this->koordynaty.pozycja_x++;
				break;
			}
			else cout << "nie mozesz wykonac tego ruchu" << endl;
		}
		if (zadanie == 'Q' || zadanie == 'q' )
		{
			if (this->specjalna_umiejetnosc_wlaczona==false  && numer_tury-this->specjalna_umiejetnosc_start_tura>10)
			{
				cout << "Czujesz przyplyw mocy, jestes niesmiertelny"<<endl;
				this->specjalna_umiejetnosc_wlaczona = true;
				this->specjalna_umiejetnosc_start_tura = numer_tury;
			}
			else cout << "nie mozesz wykonac tego ruchu" << endl;
		}
	}
	return NIC;
}
bool Czlowiek::czy_obil_atak()
{
	if (this->specjalna_umiejetnosc_wlaczona) return true;
	else return false;
}
int Czlowiek::kolizja(Organizm* organizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmow)
{
	if (this->sila > organizm_z_ktorym_kolizja->get_sila())
	{
		return ORGANIZM_ATAKUJACY;
	}
	else if (this->sila <= organizm_z_ktorym_kolizja->get_sila() && this->czy_obil_atak()==false)
	{
		return ORGANIZM_BRONIACY;
	}
	else if(this->czy_obil_atak())
	{

		cout << "Czlowiek zostal zaatakowany przez silniejszy organizm, lecz dzieki umiejtnosci niesmiertelnosc udalo mu sie przezyc";
		int nowe_pole = sprawdz_czy_wolne_pola(this->getX(), this->getY(), lista_organizmow);
		if (nowe_pole == GORA) this->koordynaty.pozycja_y--;
		if (nowe_pole == DOL) this->koordynaty.pozycja_y++;
		if (nowe_pole == LEWO) this->koordynaty.pozycja_x--;
		if (nowe_pole == PRAWO) this->koordynaty.pozycja_x++;
		Sleep(4000);
		return NIC;
	}
	return NIC;
}
int Czlowiek::sprawdz_czy_wolne_pola(int x, int y, std::list <Organizm*> lista_organizmow)
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
		for (Organizm* organizm : lista_organizmow)
		{
			if (organizm->getX() == szukane_x && organizm->getY() == szukane_y || szukane_x > 19 || szukane_x < 0 || szukane_y >19 || szukane_y < 0)
			{
				czy_wolne = false;
				break;
			}
		}
		if (czy_wolne == true)
		{
			return i;
		}
	}
	return NIC;

}
Organizm* Czlowiek::stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura)
{
	return 0;
}