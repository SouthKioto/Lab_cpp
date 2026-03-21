#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// --- FUNKCJE POMOCNICZE ---

void wyswietlSkladniki(const vector<string>& skladniki) {
    cout << "\n--- Dostepne skladniki ---\n";
    for (size_t i = 0; i < skladniki.size(); ++i) {
        cout << i + 1 << ". " << skladniki[i] << endl;
    }
}

void print_pascals_triangle(int n) {
    cout << "\n--- Trojkat Pascala (do wiersza n = " << n << ") ---\n";
    vector<vector<unsigned long long>> pt(n + 1, vector<unsigned long long>(n + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int spaces = 0; spaces < (n - i); spaces++) {
            cout << "   ";
        }
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                pt[i][j] = 1;
            }
            else {
                pt[i][j] = pt[i - 1][j - 1] + pt[i - 1][j];
            }
            cout << left << setw(6) << pt[i][j];
        }
        cout << "\n";
    }
}

// --- FUNKCJE DO KOMBINACJI ---
string stworzWynikKombinacji(const vector<int>& idx, const vector<string>& skladniki) {
    string wynik = "(";
    for (size_t i = 0; i < idx.size(); ++i) {
        wynik += to_string(idx[i] + 1);
        if (i < idx.size() - 1) {
            wynik += " ";
        }
    }
    wynik += ") ";

    for (size_t i = 0; i < idx.size(); ++i) {
        wynik += skladniki[idx[i]] + " ";
    }
    return wynik;
}

void wypiszKombinacje(const vector<string>& wyniki) {
    for (const string& wynik : wyniki) {
        cout << wynik << endl;
    }
}

// --- ALGORYTM KLASYCZNY - DOKŁADNY PSEUDOKOD ---
vector<string> generujKlasyczne(const vector<string>& skladniki, int k) {
    auto start = high_resolution_clock::now();
    int n = static_cast<int>(skladniki.size());
    vector<string> wyniki;
    vector<int> c(k + 1);  // 1-indeksowanie: c[1..k]

    // Inicjalizacja: DLA i := 1 DO k: c[i] := i
    for (int i = 1; i <= k; i++) {
        c[i] = i - 1;  // 0-indeksowanie
    }

    while (true) {
        // WYPISZ(c[1], c[2], ..., c[k])
        vector<int> kombinacja;
        for (int i = 1; i <= k; i++) {
            kombinacja.push_back(c[i]);
        }
        wyniki.push_back(stworzWynikKombinacji(kombinacja, skladniki));

        // Szukanie pozycji do zwiększenia (od prawej)
        int i = k;
        while (i > 0 && c[i] == n - k + i - 1) {  // n-k+i (dostosowane do 0-indeks)
            i--;
        }

        // JEŚLI i == 0: ZAKOŃCZ
        if (i == 0) {
            break;
        }

        // Zwiększenie elementu na pozycji i
        c[i] = c[i] + 1;

        // Ustawienie kolejnych elementów: DLA j := i+1 DO k: c[j] := c[j-1] + 1
        for (int j = i + 1; j <= k; j++) {
            c[j] = c[j - 1] + 1;
        }
    }

    auto stop = high_resolution_clock::now();
    cout << "\nCzas klasycznego: " << duration_cast<microseconds>(stop - start).count() << " us\n";
    return wyniki;
}

// --- ALGORYTM SEMBY - DOKŁADNY PSEUDOKOD ---
vector<string> generujSemby(const vector<string>& skladniki, int k) {
    auto start = high_resolution_clock::now();
    int n = static_cast<int>(skladniki.size());
    vector<string> wyniki;
    vector<int> c(k + 2);  // 1-indeksowanie: c[1..k+1]

    // Inicjalizacja: DLA i := 1 DO k: c[i] := i
    for (int i = 1; i <= k; i++) {
        c[i] = i - 1;  // 0-indeksowanie
    }
    c[k + 1] = n;  // c[k+1] := n+1 (dostosowane)

    while (true) {
        // WYPISZ(c[1], c[2], ..., c[k])
        vector<int> kombinacja;
        for (int i = 1; i <= k; i++) {
            kombinacja.push_back(c[i]);
        }
        wyniki.push_back(stworzWynikKombinacji(kombinacja, skladniki));

        // Szukanie pozycji do zwiększenia (od lewej)
        int j = 1;
        while (j <= k && c[j] + 1 == c[j + 1]) {
            c[j] = j - 1;  // Reset: c[j] := j
            j++;
        }

        // JEŻELI j <= k: c[j] := c[j] + 1
        if (j <= k) {
            c[j]++;
        }
        else {
            break;
        }
    }

    auto stop = high_resolution_clock::now();
    cout << "\nCzas Semby: " << duration_cast<microseconds>(stop - start).count() << " us\n";
    return wyniki;
}

// --- PORÓWNANIE ---
void porownajAlgorytmy(const vector<string>& skladniki, int k) {
    auto startS = high_resolution_clock::now();
    vector<string> wynikiSemby = generujSemby(skladniki, k);
    auto stopS = high_resolution_clock::now();

    auto startK = high_resolution_clock::now();
    vector<string> wynikiKlasyk = generujKlasyczne(skladniki, k);
    auto stopK = high_resolution_clock::now();

    // TABELA PORÓWNANIA
    const int kol = 45;
    cout << "\n" << left << setw(kol) << "ALGORYTM SEMBY"
        << setw(kol) << "ALGORYTM KLASYCZNY" << endl;
    cout << string(kol * 2, '-') << endl;

    size_t rows = max(wynikiSemby.size(), wynikiKlasyk.size());
    for (size_t i = 0; i < rows; i++) {
        string semby;
        string klasyk;

        if (i < wynikiSemby.size()) {
            semby = wynikiSemby[i];
        }
        if (i < wynikiKlasyk.size()) {
            klasyk = wynikiKlasyk[i];
        }

        cout << left << setw(kol) << semby << setw(kol) << klasyk << endl;
    }

    cout << "\n" << string(kol * 2, '-') << endl;
    cout << left << setw(kol) << "Czas Semby:     " << duration_cast<microseconds>(stopS - startS).count() << " us" << endl;
    cout << left << setw(kol) << "Czas Klasyczny: " << duration_cast<microseconds>(stopK - startK).count() << " us" << endl;
}

int main() {
    vector<string> skladniki = { "Ser", "Szynka", "Papryka", "Pieczarki", "Kukurydza" };
    int wybor;

    while (true) {
        cout << "\n| Pizzeria Mamma Mia |\n";
        cout << "[1] Wyswietl skladniki\n";
        cout << "[2] Kombinacje klasyczne\n";
        cout << "[3] Kombinacje Semby\n";
        cout << "[4] Porownanie algorytmow\n";
        cout << "[5] Trojkat Pascala\n";
        cout << "[0] Wyjscie\n";
        cout << "Wybor: ";
        cin >> wybor;

        if (wybor == 0) {
            break;
        }

        switch (wybor) {
        case 1:
            wyswietlSkladniki(skladniki);
            break;

        case 2:
        case 3: {
            int k;
            cout << "Podaj k (1-" << skladniki.size() << "): ";
            cin >> k;
            if (k > 0 && k <= static_cast<int>(skladniki.size())) {
                vector<string> wyniki;
                if (wybor == 2) {
                    wyniki = generujKlasyczne(skladniki, k);
                }
                else {
                    wyniki = generujSemby(skladniki, k);
                }
                wypiszKombinacje(wyniki);
            }
            else {
                cout << "Bledne k! Musi byc od 1 do " << skladniki.size() << endl;
            }
            break;
        }
        case 4: {
            int k;
            cout << "Podaj k (1-" << skladniki.size() << "): ";
            cin >> k;
            if (k > 0 && k <= static_cast<int>(skladniki.size())) {
                porownajAlgorytmy(skladniki, k);
            }
            else {
                cout << "Bledne k! Musi byc od 1 do " << skladniki.size() << endl;
            }
            break;
        }
        case 5: {
            int r;
            cout << "Ile wierszy? (max " << skladniki.size() << "): ";
            cin >> r;
            if (r > 0 && r <= static_cast<int>(skladniki.size())) {
                print_pascals_triangle(r);
            }
            else {
                cout << "Bledna liczba wierszy!\n";
            }
            break;
        }

        default:
            cout << "Nieznana opcja!\n";
            break;
        }
    }
    return 0;
}