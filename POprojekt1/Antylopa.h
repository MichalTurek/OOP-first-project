#pragma once
#include "Zwierze.h"
#include "Swiat.h"
class Antylopa : public Zwierze
{
public:
	Antylopa(Swiat* swiat, int x, int y, int born_time);
	void rysowanie() override;
	int akcja(std::list <Organizm*> &lista_organizm�w, int numer_tury) override;
	int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizm�w) override;
	int znajdz_wolne_pole(int x, int y, std::list <Organizm*> lista_organizm�w);
	bool sprawdz_czy_kolizja(int x, int y, std::list <Organizm*> lista_organizm�w);
	Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) override;
};
