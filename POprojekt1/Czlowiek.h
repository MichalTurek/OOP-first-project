#pragma once
#include "Zwierze.h"
class Czlowiek : public Zwierze
{
protected:
	bool specjalna_umiejetnosc_wlaczona = false;
	int specjalna_umiejetnosc_start_tura = -10;
public:
	Czlowiek(Swiat* swiat, int x, int y, int aktualna_tura);
	int akcja(std::list <Organizm*> &lista_organizm�w, int numer_tury) override;
	int kolizja(Organizm* organizm_z_ktorym_kolizja,std::list <Organizm*> lista_organizm�w) override;
	bool czy_obil_atak() override;
	void rysowanie() override;
	int sprawdz_czy_wolne_pola(int x, int y, std::list <Organizm*> lista_organizm�w);
	Organizm* stworz_potomka(Swiat* swiat, int x, int y, int aktualna_tura) override;
};

