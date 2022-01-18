#pragma once
#include "Zwierze.h"
class Wilk : public Zwierze
{
public:
	Wilk(Swiat* swiat, int x, int y, int born_time);
	void rysowanie() override;
	Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) override;
};
