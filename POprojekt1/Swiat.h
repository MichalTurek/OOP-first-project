#pragma once
#define WORLD_HEIGHT 20
#define WORLD_WIDHT 20 
#include "Organizm.h"
#include <list>
class Organizm;
class Swiat
{
protected:
	int world_widht = 20;
	int world_height = 20;
	int world_time = 0;
	std::list <Organizm*> lista_organizmow;
public:
	Swiat();
	void dodaj_poczatkowe_organizmy();
	int get_tura();
	void wykonaj_ture();
	void rysuj_swiat();
	std::list<Organizm*>::iterator delete_organism(Organizm* do_usuniecia);
	//std::list<Organizm*>::iterator obsluga_kolizji(Organizm* do_usuniecia, Organizm* organizm_atakujacy, std::list<Organizm*>::iterator &iterator, bool &czy_koniec_listy, bool &czy_zabito_zwierze);
	void dodaj_organizm(Organizm* do_dodania);
	void wyczysc_liste();
};

