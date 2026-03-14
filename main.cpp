#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
using namespace std;

int wyb;

int main()
{
    while(true)
    {
        cout<<"|Pizzeria „Mamma Mia”|"<<endl;
        cout<<endl;
        cout<<"[1] Wyświetl dostępne składniki"<<endl;
        cout<<"[2] Generuj kombinacje składników — algorytm klasyczny"<<endl;
        cout<<"[3] Generuj kombinacje składników — algorytm Semby"<<endl;
        cout<<"[4] Porównaj kolejność generacji obu algorytmów"<<endl;
        cout<<"[5] Trójkąt Pascala"<<endl;
        cout<<"[0] Wyjście"<<endl;
        cout<<"Wybierz opcję: ";
        cin>>wyb;
        if(wyb == 0)
        {
            cout<<"Koniec programu."<<endl;
            break;
        }
        if(wyb < 0 || wyb > 5)
        {
            cout<<"Błąd w wyborze z menu."<<endl;
        }
        else
        {
            cout<<"Wybrano opcję: "<<wyb<<endl;
        }
        cout<<endl;
    }
    return 0;
}
