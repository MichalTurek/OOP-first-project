#pragma once
#include "Zwierze.h"
#include "Swiat.h"
class Zolw : public Zwierze
{

public:
	Zolw(Swiat* swiat, int x, int y, int born_time);
	int akcja(std::list <Organizm*>& lista_organizmów, int numer_tury) override;
	int kolizja(Organizm* ogranizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów) override;
	Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) override;
	void rysowanie() override;
};



