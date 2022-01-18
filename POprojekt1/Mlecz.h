#pragma once
#include "Roslina.h"
class Mlecz : public Roslina
{
public:
	int akcja(std::list <Organizm*> &lista_organizm�w, int numer_tury) override;
	bool czy_wolne_pole(int x, int y, std::list <Organizm*> lista_organizm�w);
	Mlecz(Swiat* swiat, int x, int y, int born_time);
	void rysowanie() override;
	Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) override;
};