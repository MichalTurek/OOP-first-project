#pragma once
#include "Organizm.h"
class Zwierze : public Organizm
{
protected:
	struct Pozycja_poprzednia_t
	{
		int poprzedni_x;
		int poprzedni_y;
	}poprzednie_koordynaty;

public:
	int akcja(std::list <Organizm*> &lista_organizmów, int numer_tury) override;
	virtual void rysowanie()=0;
	virtual Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) = 0;
	int get_poprzedni_x();
	int get_poprzedni_y();
	void cofnij_na_poprzednia_pozycje() override;
	int zwroc_wolne_pole_dla_potomka(int x, int y, std::list <Organizm*> lista_organizmów) override;
	bool czy_zwierze() override;
};

