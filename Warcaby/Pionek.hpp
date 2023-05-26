#ifndef PIONEK_H
#define PIONEK_H

#include "Header.h"
using namespace std;

class Pionek {
private:

    int wlasciciel_;
    bool damka_;

public:
    Pionek(int wlasciciel = PUSTE, bool damka = false);

    int PobierzWlasciciela() const;

    bool CzyDamka() const;

    void AwansujNaDamke();

};
#endif
