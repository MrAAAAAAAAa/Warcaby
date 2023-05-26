#include "Plansza.hpp"
using namespace std;

Plansza::Plansza() : plansza_(8, vector<Pionek>(8)) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 1 && i < 3) {
                plansza_[i][j] = Pionek(GRACZ1);
            }
            else if ((i + j) % 2 == 1 && i > 4) {
                plansza_[i][j] = Pionek(GRACZ2);
            }
        }
    }
}


void Plansza::Wyswietl() {
    cout << "   0 1 2 3 4 5 6 7 X" << endl;
    cout << "   _______________" << endl;
    int nrwiersza = 0;
    for (const auto& wiersz : plansza_) {
        cout << nrwiersza << " |";
        for (const auto& pionek : wiersz) {
            if (pionek.PobierzWlasciciela() == GRACZ1) {
                cout << '1' << " ";
            }
            else if (pionek.PobierzWlasciciela() == GRACZ2) {
                cout << '2' << " ";
            }
            else if (pionek.PobierzWlasciciela() == DAMKA_GRACZ1) {
                cout << 'D' << " ";
            }
            else if (pionek.PobierzWlasciciela() == DAMKA_GRACZ2) {
                cout << 'K' << " ";
            }
            else {
                cout << '-' << " ";
            }
        }
        cout << endl;
        nrwiersza++;
    }
    cout << "Y";
}


Pionek& Plansza::PobierzPionek(int x, int y) {
    return plansza_[x][y];
}

Pionek* ostatniPionek = nullptr;

bool Plansza::PrzesunPionek(int staryX, int staryY, int nowyX, int nowyY, int gracz) {
    if (staryX < 0 || staryX >= 8 || staryY < 0 || staryY >= 8 || nowyX < 0 || nowyX >= 8 || nowyY < 0 || nowyY >= 8) {
        WyswietlKomunikat("Ruch poza plansza!");
        return false;
    }

    Pionek pionek = plansza_[staryX][staryY];

    if (pionek.PobierzWlasciciela() != gracz) {
        WyswietlKomunikat("Wybrany pionek nie nalezy do ciebie!");
        return false;
    }

    if (plansza_[nowyX][nowyY].PobierzWlasciciela() != PUSTE) {
        WyswietlKomunikat("Pole jest juz zajete!\n");
        return false;
    }
    bool zbicie = false;

    if (abs(staryX - nowyX) == 2 && abs(staryY - nowyY) == 2) {
        int srodkowyX = (staryX + nowyX) / 2;
        int srodkowyY = (staryY + nowyY) / 2;
        Pionek& srodkowy = plansza_[srodkowyX][srodkowyY];
        if ((srodkowy.PobierzWlasciciela() == GRACZ1 && gracz == GRACZ2) ||
            (srodkowy.PobierzWlasciciela() == GRACZ2 && gracz == GRACZ1)) {
            srodkowy = Pionek(PUSTE);

            // Przesuwam pionek na now¹ pozycjê po biciu
            plansza_[nowyX][nowyY] = pionek;
            plansza_[staryX][staryY] = Pionek(PUSTE);
            zbicie = true;
        }
        else {
            WyswietlKomunikat("Nie ma pionka do zbicia!");
            return false;
        }
    }


    if (pionek.CzyDamka()) {
        if (CzyMoznaWykonacRuchDamka(staryX, staryY, nowyX, nowyY, gracz)) {
            plansza_[staryX][staryY] = Pionek(PUSTE);
            plansza_[nowyX][nowyY] = pionek;
            return true;
        }
        else {
            WyswietlKomunikat("Niepoprawny ruch damki!");
            return false;
        }
    }
    else {
        if ((gracz == GRACZ1 && nowyX > staryX && nowyY != staryY) || (gracz == GRACZ2 && nowyX < staryX && nowyY != staryY)) {
            if ((nowyX == staryX + 1 || nowyX == staryX - 1) && (nowyY == staryY + 1 || nowyY == staryY - 1)) {

                plansza_[staryX][staryY] = Pionek(PUSTE);
                plansza_[nowyX][nowyY] = pionek;

                if (gracz == GRACZ1 && nowyX == 7) {
                    pionek.AwansujNaDamke();
                }
                else if (gracz == GRACZ2 && nowyX == 0) {
                    pionek.AwansujNaDamke();
                }
                return true;
            }
            else if (zbicie == false) {
                WyswietlKomunikat("Niepoprawny ruch pionka!");
                return false;
            }
        }
    }

    return false;
}


void Plansza::WyswietlKomunikat(const string& komunikat) {
    cout << "Blad: " << komunikat << endl;
}


bool Plansza::CzyMoznaWykonacRuchDamka(int staryX, int staryY, int nowyX, int nowyY, int gracz) {

    if (plansza_[nowyX][nowyY].PobierzWlasciciela() != PUSTE) {
        return false;
    }

    if (abs(nowyX - staryX) != abs(nowyY - staryY)) {
        return false;
    }

    int dx = (nowyX > staryX) ? 1 : -1;
    int dy = (nowyY > staryY) ? 1 : -1;

    int x = staryX + dx;
    int y = staryY + dy;

    bool bylo_bicie = false;

    while (x != nowyX && y != nowyY) {
        if (plansza_[x][y].PobierzWlasciciela() != PUSTE) {
            if (bylo_bicie || plansza_[x][y].PobierzWlasciciela() == gracz) {
                return false;
            }
            bylo_bicie = true;
            x += dx;
            y += dy;
        }
        x += dx;
        y += dy;
    }
    return true;
}


bool Plansza::CzyKoniecGry() {
    int gracze[2] = { 0, 0 };
    for (const auto& wiersz : plansza_) {
        for (const auto& pionek : wiersz) {
            if (pionek.PobierzWlasciciela() == GRACZ1 || pionek.PobierzWlasciciela() == DAMKA_GRACZ1) {
                gracze[0]++;
            }
            else if (pionek.PobierzWlasciciela() == GRACZ2 || pionek.PobierzWlasciciela() == DAMKA_GRACZ2) {
                gracze[1]++;
            }
        }
    }
    return gracze[0] == 0 || gracze[1] == 0;
}


bool Plansza::CzyRemis() {
    int gracze[2] = { 0, 0 };

    for (const auto& wiersz : plansza_) {
        for (const auto& pionek : wiersz) {
            if (pionek.PobierzWlasciciela() == GRACZ1 || pionek.PobierzWlasciciela() == DAMKA_GRACZ1) {
                gracze[0]++;
            }
            else if (pionek.PobierzWlasciciela() == GRACZ2 || pionek.PobierzWlasciciela() == DAMKA_GRACZ2) {
                gracze[1]++;
            }
        }
    }
    return (gracze[0] == 0 && gracze[1] == 0);
}

bool Plansza::CzyMozliweBicie(int x, int y) {
    int gracz = plansza_[x][y].PobierzWlasciciela();
    if (gracz == PUSTE) {
        return false;
    }
    for (int dx = -1; dx <= 1; dx += 2) {
        for (int dy = -1; dy <= 1; dy += 2) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && plansza_[nx][ny].PobierzWlasciciela() != PUSTE && plansza_[nx][ny].PobierzWlasciciela() != gracz) {
                int nnx = nx + dx;
                int nny = ny + dy;
                if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && plansza_[nnx][nny].PobierzWlasciciela() == PUSTE) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Plansza::CzyIstniejeMozliweBicie() {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (CzyMozliweBicie(x, y)) {
                return true;
            }
        }
    }
    return false;
}