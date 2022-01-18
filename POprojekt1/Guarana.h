#pragma once
#include "Roslina.h"
class Guarana : public Roslina
{
public:
	int kolizja(Organizm* organizm_z_ktorym_kolizja, std::list <Organizm*> lista_organizmów) override;
	Guarana(Swiat* swiat, int x, int y, int born_time);
	void rysowanie() override;
	Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) override;
};

