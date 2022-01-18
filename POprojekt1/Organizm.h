#pragma once
#include "Swiat.h"
#include <iostream>
#include "Organizm.h"
#include <list>

using namespace std;
class Swiat;
class Organizm
{
protected:
	 Swiat* swiat;
	 int sila, inicjatywa,tura_urodzenia;
	 bool czy_zyje = true;
	 string nazwa_gatunku;
	 struct Pozycja_t
	 {
		 int pozycja_x, pozycja_y;
	 } koordynaty;
public:
	 bool sprawdz_czy_zyje();
	 void zabij();
	 virtual int akcja(std::list <Organizm*> &lista_organizmów, int numer_tury)=0;
	 virtual int kolizja(Organizm * ogranizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów);
	 virtual void rysowanie() = 0;
	 virtual int getX();
	 virtual int  getY();
	 virtual int get_tura_startowa();
	 virtual int get_sila();
	 virtual int get_inicjatywa();
	 virtual string get_nazwa_gatunku();
	 virtual void cofnij_na_poprzednia_pozycje() = 0;
	 virtual void zwieksz_sile();
	 virtual bool czy_zwierze() = 0;
	 virtual bool czy_obil_atak();
	 int sprawdz_czy_wolne_pola(int x, int y, std::list <Organizm*> lista_organizmów);
	 virtual int zwroc_wolne_pole_dla_potomka(int x, int y, std::list <Organizm*> lista_organizmów) = 0;
	 int rozmnazanie(Organizm* organizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów);
	 virtual Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) = 0;
};

