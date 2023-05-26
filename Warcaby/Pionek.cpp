#include "Pionek.hpp"
using namespace std;


Pionek::Pionek(int wlasciciel, bool damka) : wlasciciel_(wlasciciel), damka_(damka) {}


int Pionek::PobierzWlasciciela() const {
    return wlasciciel_;
}


void Pionek::AwansujNaDamke() {
    if (wlasciciel_ == GRACZ1) {
        wlasciciel_ = DAMKA_GRACZ1;
    }
    else if (wlasciciel_ == GRACZ2) {
        wlasciciel_ = DAMKA_GRACZ2;
    }
}

bool Pionek::CzyDamka() const {
    return damka_;
}