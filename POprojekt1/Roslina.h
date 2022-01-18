#pragma once
#include "Organizm.h"
class Roslina : public Organizm
{
public:
	int akcja(std::list <Organizm*> &lista_organizmów,int numer_tury) override;
	virtual void rysowanie() = 0;
	void cofnij_na_poprzednia_pozycje() override;
	
	bool czy_zwierze() override;
	virtual Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) = 0;
	int zwroc_wolne_pole_dla_potomka(int x, int y, std::list <Organizm*> lista_organizmów) override;
};



