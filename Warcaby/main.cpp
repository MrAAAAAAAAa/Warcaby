#include <iostream>
#include "Plansza.hpp"

using namespace std;

int main() {

    Plansza plansza;
    int aktualnyGracz = GRACZ1;

    cout << "WYBIERZ TRYB GRY\n" << "1.GRACZ VS GRACZ\n" << "2.GRACZ VS KOMPUTER" << endl;
    int wybor;
    cin >> wybor;
    cout << "\n\n";

    switch (wybor) {

    case 1:

        while (true) {
            plansza.Wyswietl();
            if (plansza.CzyKoniecGry()) {
                if (plansza.CzyRemis()) {
                    cout << "Remis! Brak mo¿liwoœci wykonania dalszych ruchów." << endl;
                }
                else {
                    cout << "Koniec gry! Wygral gracz " << (aktualnyGracz == GRACZ1 ? 2 : 1) << "!\n";
                }
                break;
            }
            int staryX, staryY, nowyX, nowyY;
            cout << "\nGracz " << (aktualnyGracz == GRACZ1 ? 1 : 2) << ", wprowadz swoj ruch\n";
            int sprawdzanko;
            do {
                sprawdzanko = 1;
                cout << "Podaj aktualne pozycje pionka (y x): ";
                cin >> staryX >> staryY;

                if (staryX < 0 || staryX >= 8 || staryY < 0 || staryY >= 8 || (plansza.CzyIstniejeMozliweBicie() && !plansza.CzyMozliweBicie(staryX, staryY))) {
                    cout << "Niepoprawne wspolrzedne. " << endl;
                    sprawdzanko = 2;
                }
            } while (sprawdzanko == 2);

            cout << "Podaj nowe pozycje pionka (y x): ";
            while (!(cin >> nowyX >> nowyY) || nowyX < 0 || nowyX >= 8 || nowyY < 0 || nowyY >= 8) {
                cout << "Niepoprawne wspolrzedne." << endl;
                cout << "Podaj nowe pozycje pionka (y x): ";
            }
            cout << endl;
            if (plansza.PobierzPionek(staryX, staryY).PobierzWlasciciela() == aktualnyGracz) {
                if (plansza.PrzesunPionek(staryX, staryY, nowyX, nowyY,aktualnyGracz)) {
                    if (!plansza.CzyMozliweBicie(nowyX, nowyY)) {
                        aktualnyGracz = (aktualnyGracz == GRACZ1 ? GRACZ2 : GRACZ1);
                    }
                }
            }
        }
        break;
    case 2:
        cout << "PRACA W TOKU" << endl;
        break;
    }
        return 0;
}
