#pragma once
#include "Roslina.h"
class Barszcz_sosnowskiego : public Roslina
{
public:
	int kolizja(Organizm* organizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów) override;
	int akcja(std::list <Organizm*> &lista_organizmów, int numer_tury) override;
	Barszcz_sosnowskiego(Swiat* swiat, int x, int y, int born_time);
	void rysowanie() override;
	Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) override;
};

