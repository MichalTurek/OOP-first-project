#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Roslina.h"
#include "Trawa.h"
#include "Owca.h"
#include "Wilk.h"
#include "Zolw.h"
#include "Lis.h"
#include "Antylopa.h"
#include "Guarana.h"
#include "Mlecz.h"
#include "Wilcze_jagody.h"
#include "Barszcz_sosnowskiego.h"
#include "Czlowiek.h"
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <Windows.h>
#define NOWY_LEWO 0
#define NOWY_PRAWO 1
#define NOWY_GORA 2
#define NOWY_DOL 3
#define ORGANIZM_BRONIACY 4
#define ORGANIZM_ATAKUJACY 5
#define ROZMNAZANIE 6
#define NIC 7 
#define WIELE_GINIE 8
using namespace std;

Swiat::Swiat()
{
	srand(time(NULL));
	cout << "poczatek rozgrywki"<<endl;
	dodaj_poczatkowe_organizmy();
	Sleep(1000);
}
void Swiat::wykonaj_ture()
{
	//petla iterujaca po inicjatywie 
	for (int szukana_inicjatywa = 7; szukana_inicjatywa >= 0; szukana_inicjatywa--)
	{
		if (szukana_inicjatywa == 6 || szukana_inicjatywa == 3 || szukana_inicjatywa == 2) szukana_inicjatywa--; //przyspieszenie dzialania listy po inicjatywie, nie  sprawdza dla inicjatyw ktore nie istnieja dla zadnych organizmow
		std::list<Organizm*>::iterator it = this->lista_organizmow.begin();
		int iterator = 0;
		int efekt_akcji,efekt_kolizji;
		bool czy_koniec_listy=false;
		while(it != this->lista_organizmow.end()) // iteracja po liscie ogranizmow
		{	
			iterator++;
			bool is_element_being_killed = false;
			Organizm * organizm_aktualny = *it;
			if (organizm_aktualny->get_inicjatywa() == szukana_inicjatywa && organizm_aktualny->get_tura_startowa() != this->world_time)
			{	// sprawdzenie czy organizm posiada szukana inicjatywe oraz czy urodzil sie wczesniej niz w aktualnej turze																											
				efekt_akcji=organizm_aktualny->akcja(this->lista_organizmow, this->world_time);
				if (efekt_akcji == WIELE_GINIE) // wowolanie informacji odnosnie akcji
				{
					cout << "Zwierzeta wokol barszczu zginely" << endl;
					Sleep(2000);
					efekt_akcji = organizm_aktualny->akcja(this->lista_organizmow, this->world_time);
				}
				if (efekt_akcji == ROZMNAZANIE)
				{
					cout << "roslina " << organizm_aktualny->get_nazwa_gatunku() << " (" << organizm_aktualny->getX()<<"," << organizm_aktualny->getY() << ") rozprzestrzenila sie na sasiednie pola, " << endl;
					Sleep(2000);
				}
				for (Organizm* organizm_broniacy : this->lista_organizmow) //sprawdzenie kolizji
				{
					if (organizm_aktualny->getX() == organizm_broniacy->getX() && organizm_aktualny->getY() == organizm_broniacy->getY() && organizm_aktualny != organizm_broniacy)
					{
						efekt_kolizji = organizm_broniacy->kolizja(organizm_aktualny,this->lista_organizmow); // wywolanie metody kolizja
						cout << "Kolizja: (" << organizm_aktualny->getX() <<", "<< organizm_aktualny->getY()<<")" << endl;
						if (efekt_kolizji==ROZMNAZANIE)
						{
							cout << "Tu rozmnazanie " << organizm_aktualny->get_nazwa_gatunku() << endl;
							Sleep(3000);
							if (it != this->lista_organizmow.end())++it;
							else czy_koniec_listy = true;
							break;
						}
						if (efekt_kolizji == ORGANIZM_ATAKUJACY) //kolizja w ktorej atakujacy ginie
						{
							if (organizm_aktualny->czy_obil_atak()) //sprawdzenie czy organizm odbil atak
							{
								cout << "mimo iz atakujacy byl slabszy, zdolal przetrwac starcie" << endl;
								Sleep(2000);
								organizm_aktualny->cofnij_na_poprzednia_pozycje();
								break;
							}
							else // usuniecie ogranizmu i przesuniecie iteratora
							{
								cout << "atakujacy " << organizm_aktualny->get_nazwa_gatunku() << " sila: " << organizm_aktualny->get_sila();
								cout << " przegral z " << organizm_broniacy->get_nazwa_gatunku() << " sila: " << organizm_broniacy->get_sila() << endl;
								if (it != this->lista_organizmow.end())++it;
								else czy_koniec_listy = true;
								delete_organism(organizm_aktualny);
								Sleep(3000);
								is_element_being_killed = true;
								break;
							}
						}
						if (efekt_kolizji == ORGANIZM_BRONIACY) // kolizja w ktorej broniacy ginie 
						{
							cout << "atakujacy " << organizm_aktualny->get_nazwa_gatunku() << " sila: " << organizm_aktualny->get_sila();
							cout << " wygral z " << organizm_broniacy->get_nazwa_gatunku() << " sila: " << organizm_broniacy->get_sila() << endl;
							delete_organism(organizm_broniacy);
							if (it != this->lista_organizmow.end())++it;
							else czy_koniec_listy = true;
							Sleep(3000);
							is_element_being_killed = true;
							break;
						}
						if (efekt_kolizji == WIELE_GINIE) // sytuacja w ktorej oba organizmy gina
						{
							cout << "(" << organizm_aktualny->getX() << ", " << organizm_aktualny->getY() << ")" << endl;
							delete_organism(organizm_broniacy);
							if (it != this->lista_organizmow.end())++it;
							else czy_koniec_listy = true;
							if (organizm_aktualny->czy_obil_atak()) cout << "organizm atakujacy jest niesmiertelny, przezyl walke" << endl;
							else delete_organism(organizm_aktualny);
							Sleep(2000);
							break;
						}
					}
				}
				this->rysuj_swiat();
			}
			if (czy_koniec_listy == true) break;
			if (is_element_being_killed == false) ++it;
			if (iterator > lista_organizmow.size()) break;
		}

	}
	cout << "Ilosc organizmow: " << lista_organizmow.size() << endl;
	cout << "KONIEC TURY" << this->world_time << endl;
	Sleep(2500);
	this->world_time++;
}
void Swiat::rysuj_swiat()
{
	system("CLS");
	cout << "Michal Turek"<< " S184645" << endl;
	for (int y = 0; y < 22; y++)
	{
		
		for (int x = 0; x < 22; x++)
		{	
			bool printed = false;
			if (x == 0 && y == 0)
			{
				cout << char(201);
				printed = true;
			}
			else if (x == 21 && y == 0)
			{
				cout << char(187);
				printed = true;
			}
			else if (x == 0 && y == 21)
			{
				cout << char(200);
				printed = true;
			}
			else if (x == 21 && y == 21)
			{
				cout << char(188);
				printed = true;
			}
			else if (x == 0 || x == 21)
			{
				cout << char(186);
				printed = true;
			}
			else if (y == 0 || y == 21) 
			{
				cout << char(205);
				printed = true;
			}
			else for (Organizm* organizm : this->lista_organizmow)
			{
				if (organizm->getX() == x-1 && organizm->getY() == y-1)
				{
					organizm->rysowanie();
					printed = true;
				}
			}
			if (printed == false) cout << " ";
		}

		cout << endl;
		
	}
	int i = 0;
}
int Swiat::get_tura()
{
	return world_time;
}
std::list<Organizm*>::iterator Swiat::delete_organism(Organizm* do_usuniecia)
{
	std::list<Organizm*>::iterator usun_element;
	usun_element = lista_organizmow.begin();
	while(true)
	{
		advance(usun_element, 1);
		if (*usun_element == do_usuniecia) break;
	}
	usun_element=lista_organizmow.erase(usun_element);
	delete do_usuniecia;
	return usun_element;
}
void Swiat::wyczysc_liste()
{
	while (lista_organizmow.size() != 0)
	{
		Organizm* poczatkowy_organizm = *this->lista_organizmow.begin();
		lista_organizmow.pop_front();
		delete poczatkowy_organizm;
	}
}
void Swiat::dodaj_organizm(Organizm* do_dodania)
{
	lista_organizmow.push_back(do_dodania);
}
void Swiat::dodaj_poczatkowe_organizmy()
{
	Barszcz_sosnowskiego* new_barszcz = new Barszcz_sosnowskiego(this, 8, 4, this->world_time);
	Barszcz_sosnowskiego* new_barszcz1 = new Barszcz_sosnowskiego(this, 16, 4, this->world_time);
	Trawa* new_trawa = new Trawa(this, 9, 9, this->world_time);
	Trawa* new_trawa1 = new Trawa(this, 8, 6, this->world_time);
	Trawa* new_trawa2 = new Trawa(this, 8, 12, this->world_time);
	Trawa* new_trawa3 = new Trawa(this, 8, 19, this->world_time);
	Trawa* new_trawa4 = new Trawa(this,12, 15, this->world_time);
	Owca* new_owca = new Owca(this, 19, 19, this->world_time);
	Owca* new_owca1 = new Owca(this, 2, 2, this->world_time);
	Owca* new_owca2 = new Owca(this, 6, 7, this->world_time);
	Owca* new_owca3 = new Owca(this, 17, 19, this->world_time);
	Owca* new_owca4 = new Owca(this, 4, 2, this->world_time);
	Owca* new_owca5 = new Owca(this, 8, 7, this->world_time);
	Owca* new_owca6 = new Owca(this, 13, 7, this->world_time);
	Owca* new_owca7 = new Owca(this, 16, 5, this->world_time);
	Owca* new_owca8 = new Owca(this, 6, 9, this->world_time);
	Owca* new_owca9 = new Owca(this, 19, 2, this->world_time);
	Owca* new_owca10 = new Owca(this, 9, 4, this->world_time);
	Owca* new_owca11 = new Owca(this, 1, 9, this->world_time);
	Wilk* new_wilk = new Wilk(this, 1, 1, this->world_time);
	Wilk* new_wilk2 = new Wilk(this, 1, 2, this->world_time);
	Wilk* new_wilk3 = new Wilk(this, 1, 3, this->world_time);
	Wilk* new_wilk4 = new Wilk(this, 2, 3, this->world_time);
	Wilk* new_wilk5 = new Wilk(this, 4, 4, this->world_time);
	Wilk* new_wilk6 = new Wilk(this, 5, 5, this->world_time);
	Wilk* new_wilk7 = new Wilk(this, 0, 0, this->world_time);
	Czlowiek* new_czlowiek = new Czlowiek(this, 17, 3, this->world_time);
	Lis* new_lis = new  Lis(this, 1, 0, this->world_time);
	Lis* new_lis1 = new  Lis(this, 1, 5, this->world_time);
	Lis* new_lis2 = new  Lis(this, 1, 6, this->world_time);
	Lis* new_lis3 = new  Lis(this, 13, 5, this->world_time);
	Lis* new_lis4 = new  Lis(this, 15, 0, this->world_time);
	Lis* new_lis5 = new  Lis(this, 17, 0, this->world_time);
	Lis* new_lis6 = new  Lis(this, 1, 19, this->world_time);
	Lis* new_lis7 = new  Lis(this, 8, 15, this->world_time);
	Zolw* new_zolw = new  Zolw(this, 7, 3, this->world_time);
	Zolw* new_zolw1 = new  Zolw(this, 8, 9, this->world_time);
	Zolw* new_zolw2 = new  Zolw(this, 7, 4, this->world_time);
	Zolw* new_zolw3 = new  Zolw(this, 15, 14, this->world_time);
	Mlecz* new_mlecz = new Mlecz(this, 12, 6, this->world_time);
	Mlecz* new_mlecz1 = new Mlecz(this, 12, 16, this->world_time);
	Mlecz* new_mlecz2 = new Mlecz(this, 12, 17, this->world_time);
	Guarana* new_guarana = new Guarana(this, 12, 14, this->world_time);
	Guarana* new_guarana1 = new Guarana(this, 13, 18, this->world_time);
	Guarana* new_guarana3 = new Guarana(this, 13, 3, this->world_time);
	Wilcze_jagody* new_jagody = new Wilcze_jagody(this, 1, 17, this->world_time);
	Wilcze_jagody* new_jagody1 = new Wilcze_jagody(this, 6, 18, this->world_time);
	Wilcze_jagody* new_jagody2 = new Wilcze_jagody(this, 14, 14, this->world_time);
	Wilcze_jagody* new_jagody3 = new Wilcze_jagody(this, 5, 17, this->world_time);
	Antylopa* new_antylopa = new Antylopa(this, 18, 17, this->world_time);
	Antylopa* new_antylopa1 = new Antylopa(this, 16, 9, this->world_time);
	Antylopa* new_antylopa2 = new Antylopa(this, 17, 2, this->world_time);
	Antylopa* new_antylopa3 = new Antylopa(this,1, 8, this->world_time);
	Barszcz_sosnowskiego* new_barszcz2 = new Barszcz_sosnowskiego(this, 19, 7, this->world_time);
	
	lista_organizmow.push_back(new_barszcz);
	lista_organizmow.push_back(new_barszcz1);
	lista_organizmow.push_back(new_wilk);
	lista_organizmow.push_back(new_wilk2);
	lista_organizmow.push_back(new_wilk3);
	lista_organizmow.push_back(new_wilk4);
	lista_organizmow.push_back(new_wilk5);
	lista_organizmow.push_back(new_czlowiek);
	lista_organizmow.push_back(new_wilk6);
	lista_organizmow.push_back(new_trawa);
	lista_organizmow.push_back(new_trawa1);
	lista_organizmow.push_back(new_trawa2);
	lista_organizmow.push_back(new_trawa3);
	lista_organizmow.push_back(new_owca);
	lista_organizmow.push_back(new_owca1);
	lista_organizmow.push_back(new_owca2);
	lista_organizmow.push_back(new_owca3);
	lista_organizmow.push_back(new_owca4);
	lista_organizmow.push_back(new_owca5);
	lista_organizmow.push_back(new_owca6);
	lista_organizmow.push_back(new_owca7);
	lista_organizmow.push_back(new_owca8);
	lista_organizmow.push_back(new_owca9);
	lista_organizmow.push_back(new_owca10);
	lista_organizmow.push_back(new_owca11);
	lista_organizmow.push_back(new_lis);
	lista_organizmow.push_back(new_lis1);
	lista_organizmow.push_back(new_lis2);
	lista_organizmow.push_back(new_lis3);
	lista_organizmow.push_back(new_lis4);
	lista_organizmow.push_back(new_lis5);
	lista_organizmow.push_back(new_lis6);
	lista_organizmow.push_back(new_lis7);
	lista_organizmow.push_back(new_zolw);
	lista_organizmow.push_back(new_zolw1);
	lista_organizmow.push_back(new_zolw2);
	lista_organizmow.push_back(new_zolw3);
	lista_organizmow.push_back(new_mlecz);
	lista_organizmow.push_back(new_mlecz1);
	lista_organizmow.push_back(new_mlecz2);
	lista_organizmow.push_back(new_guarana);
	lista_organizmow.push_back(new_guarana1);
	lista_organizmow.push_back(new_guarana3);
	lista_organizmow.push_back(new_wilk7);
	lista_organizmow.push_back(new_antylopa);
	lista_organizmow.push_back(new_antylopa1);
	lista_organizmow.push_back(new_antylopa2);
	lista_organizmow.push_back(new_antylopa3);
	lista_organizmow.push_back(new_jagody);
	lista_organizmow.push_back(new_jagody1);
	lista_organizmow.push_back(new_jagody2);
	lista_organizmow.push_back(new_jagody3);
	
}