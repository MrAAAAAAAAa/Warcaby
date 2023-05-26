#ifndef PLANSZA_H
#define PLANSZA_H

#include "Pionek.hpp"
#include <iostream>
#include <vector>

class Plansza {

private:
    vector<vector<Pionek>> plansza_;

public:
    Plansza();

    Pionek& PobierzPionek(int x, int y);

    bool PrzesunPionek(int staryX, int staryY, int nowyX, int nowyY, int gracz);

    void Wyswietl();

    bool CzyMoznaWykonacRuchDamka(int staryX, int staryY, int nowyX, int nowyY, int gracz);

    void WyswietlKomunikat(const string& komunikat);

    bool CzyKoniecGry();

    bool CzyRemis();

    bool CzyIstniejeMozliweBicie();

    bool CzyMozliweBicie(int x, int y);


};

#endif
