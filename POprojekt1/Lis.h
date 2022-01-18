#pragma once
#include "Zwierze.h"
#include "Swiat.h"
class Lis : public Zwierze
{
public:
	Lis(Swiat* swiat, int x, int y, int born_time);
	void rysowanie() override;
	int akcja(std::list <Organizm*> &lista_organizmów, int numer_tury) override;
	bool sprawdz_czy_bezpiecznie(int x, int y, std::list <Organizm*> lista_organizmów);
	Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) override;
};

